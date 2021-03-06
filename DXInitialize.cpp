#include "DXInitialize.h"
#include"DXWindow.h"

using namespace DirectX;




ComPtr<ID3D12Device> DXInitialize::Getdevice()
{
	return device;
}

ComPtr<IDXGIFactory7> DXInitialize::GetdxgiFactory()
{
	return dxgiFactory;
}

ComPtr<IDXGISwapChain4> DXInitialize::GetswapChain()
{
	return swapChain;
}

void DXInitialize::Initialize(HWND hwnd)
{
	
	dxgiFactory = nullptr;
	swapChain = nullptr;
	
	rtvHeap = nullptr;



#pragma region	アダプタ
	//DXGIファクトリーの生成
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	tmpAdapter = nullptr;

	//パf−マンスが高いものから順に、全てのアダプターを列挙する
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++)
	{
		//動的に配列を追加する
		adapters.push_back(tmpAdapter.Get());
	}
	for (size_t i = 0; i < adapters.size(); i++)
	{
		//アダプターの情報を取得する
		adapters[i]->GetDesc3(&adapterDesc);

		//ソフトウェアデバイスを回避
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			//デバイスを採用してループを抜ける
			tmpAdapter = adapters[i];
			break;
		}
	}
#pragma endregion アダプタ






#pragma region	スワップチェーン

	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				//色情報の書式
	swapChainDesc.SampleDesc.Count = 1;								//マルチサンプルをしない
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;				//バックバッファ用
	swapChainDesc.BufferCount = 2;									//バッファ数を2つに設定
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		//フリップ後は破棄
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	//スワップチェーンの生成

	ComPtr<IDXGISwapChain1> swapchain1;

	result = dxgiFactory->CreateSwapChainForHwnd(commandQueue.Get(), hwnd, &swapChainDesc, nullptr, nullptr,&swapchain1);
	assert(SUCCEEDED(result));
	swapchain1.As(&swapChain);
#pragma endregion	スワップチェーン

#pragma region	デスクリプタヒープ
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;			//レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;		//裏表の２つ

	//デスクリプタヒープの生成
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

#pragma endregion	デスクリプタヒープ

	backBuffers.resize(swapChainDesc.BufferCount);

#pragma region	レンダーターゲットビュー
	//スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//スワップチェーンからバッファを取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//デスクリプタヒープのハンドルを取得
		rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//裏か表かでアドレスがずれる
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);

		//シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//レンダーターゲットビューの生成
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
#pragma endregion	レンダーターゲットビュー

	DepthInitilize();

	fence = nullptr;
	fenceVal = 0;

	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

}

XMMATRIX DXInitialize::GetmatProjection()
{
	return matProjection;
}

ComPtr<ID3D12CommandAllocator> DXInitialize::GetcommandAllocator()
{
	return  commandAllocator;
}

ComPtr<ID3D12GraphicsCommandList> DXInitialize::GetcommandList()
{
	return commandList;
}

DXInitialize::DXInitialize()
{
	device = nullptr;
	commandAllocator = nullptr;
	commandList = nullptr;
	commandQueue = nullptr;
#pragma region	デバイス
	//対応レベルの配列
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	for (size_t i = 0; i < _countof(levels); i++)
	{
		//採用したアダプターでデバイスを生成
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&device));
		if (result == S_OK)
		{
			featureLevel = levels[i];
			break;
		}
	}
#pragma endregion	デバイス
#pragma region コマンド

	//コマンドアロケーターを生成
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(result));

	//コマンドリストを生成
	result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(result));

	//コマンドキューを生成
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));

#pragma endregion	コマンド
}


void DXInitialize::DxDrawIni()
{
	VertexBufferInitialize();
	IndexBufferInitialize();
	housenn();
	VBufferTransfer();
	IBufferTransfer();
	VBView();
	IBView();
	VSFileReadCompile();
	PSFileReadCompile();
	GraphicsPipeLine();
	ResouceConstBfferM();
	ConstBufferMaterial();
	ConstBufferTransform();
	/*TextureImageData(L"Resources/genba_hako_320x320.png");
	TextureBuffer();
	TBufferTransfer();*/
	/*DescriptorHeap();
	ShaderResourceView();*/
}


void DXInitialize::VertexBufferInitialize()
{
	sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPUへの転送用
	
	//リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;	//インデックス情報が入るサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	vertBuff = nullptr;
	result = device->CreateCommittedResource(
		&heapProp,	//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
}

void DXInitialize::IndexBufferInitialize()
{
	sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));

	//リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;	//インデックス情報が入るサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	indexBuff = nullptr;
	result = device->CreateCommittedResource(
		&heapProp,	//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff)
	);
}

void DXInitialize::housenn()
{
	for (int i = 0; i < _countof(indices) / 3; i++)
	{
		unsigned short index_zero = indices[i * 3 + 0];
		unsigned short index_one = indices[i * 3 + 1];
		unsigned short index_two = indices[i * 3 + 2];

		XMVECTOR p0 = XMLoadFloat3(&vertices[index_zero].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[index_one].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[index_two].pos);

		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);

		XMVECTOR normal = XMVector3Cross(v1, v2);

		normal = XMVector3Normalize(normal);

		XMStoreFloat3(&vertices[index_zero].normal, normal);
		XMStoreFloat3(&vertices[index_one].normal, normal);
		XMStoreFloat3(&vertices[index_two].normal, normal);
	}

}

ComPtr<ID3D12CommandQueue> DXInitialize::GetcommandQueue()
{
	return commandQueue;
}

ComPtr<ID3D12DescriptorHeap> DXInitialize::GetrtvHeap()
{
	return rtvHeap;
}

XMMATRIX DXInitialize::Getmatview()
{
	return matview;
}



DXInitialize* DXInitialize::GetInstance()
{
	static DXInitialize instance;
	return &instance;
}

void DXInitialize::VBufferTransfer()
{
	
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//全頂点に対して
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i]; //座標をコピー
	}
	//繋がりを解除
	vertBuff->Unmap(0, nullptr);
}

void DXInitialize::IBufferTransfer()
{
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//全インデックスに対して
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];	//インデックスをコピー
	}
	//マッピング解除

	indexBuff->Unmap(0, nullptr);

}

void DXInitialize::VBView()
{
	//GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	//頂点1つ分のデータサイズ
	vbView.StrideInBytes = sizeof(vertices[0]);
}

void DXInitialize::IBView()
{
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

void DXInitialize::VSFileReadCompile()
{
	//頂点シェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"BasicVS.hlsl", //シェーダーファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, //インクルード可能にする
		"main", "vs_5_0", //エントリーポイント名,シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	//エラーなら
	if (FAILED(result))
	{
		//errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), error.begin());

		error += "\n";
		//エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}
}

void DXInitialize::PSFileReadCompile()
{
	//ピクセルシェーダファイルの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"BasicPS.hlsl", //シェーダーファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, //インクルード可能にする
		"main", "ps_5_0", //エントリーポイント名,シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //デバッグ用設定
		0,
		&psBlob, &errorBlob);

	//エラーなら
	if (FAILED(result))
	{
		//errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), error.begin());

		error += "\n";
		//エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}
}

void DXInitialize::GraphicsPipeLine()
{

	//シェーダーの設定
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	//サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; //標準設定

	//ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; 
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; //ポリゴン内塗りつぶし
	//pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; //ワイヤーフレーム(どちらか片方)
	pipelineDesc.RasterizerState.DepthClipEnable = true;	//深度クリッピングを有効に

	//ブレンドステート
	//pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; //RGBA全てのチャンネルを描画

	//レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;		//RGBA全てのチャンネルを描画

	//共通設定
	blenddesc.BlendEnable = true;					//ブレンドを有効にする
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;	//加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;		//ソースの値を100%使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;	//デストの値を0%使う


	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;			//加算合成
	////blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;//減算合成
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;
	//blenddesc.DestBlend = D3D12_BLEND_ONE;

	//色反転
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;	//1.0fデストカラーの値
	//blenddesc.DestBlend = D3D12_BLEND_ZERO;

	//半透明合成
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;			//ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;	//1.0f-ソースのa値



	//頂点レイアウトの設定
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	//図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	//0〜255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1;	//1ピクセルにつき1回サンプリング

	//デスクリプタレンジの設定
	descriptorRange.NumDescriptors = 1;		//一度の描画に使うテクスチャが1枚なので1
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0;	//テクスチャレジスタ0番
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//定数バッファ0番
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;		//定数バッファビュー
	rootParams[0].Descriptor.ShaderRegister = 0;						//定数バッファ番号
	rootParams[0].Descriptor.RegisterSpace = 0;							//デフォルト値
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;		//全てのシェーダーから見える
	//テクスチャレジスタ0番
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;	//種類
	rootParams[1].DescriptorTable.pDescriptorRanges = &descriptorRange;			//デスクリプタレンジ
	rootParams[1].DescriptorTable.NumDescriptorRanges = 1;						//デスクリプタレンジ数
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;				//全てのシェーダーから見える
	//定数バッファ1番
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;		//種類
	rootParams[2].Descriptor.ShaderRegister = 1;						//定数バッファ番号
	rootParams[2].Descriptor.RegisterSpace = 0;							//デフォルト値
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;		//全てのシェーダーから見える

	//テクスチャサンプラーの設定
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					//横繰り返し(タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					//縦繰り返し(タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;					//奥行繰り返し(タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;	//ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;					//全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;									//ミップマップ最大値
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;			//ピクセルシェーダーからのみ使用可能

	//ルートシグネチャの設定
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams;		//ルートパラメータの先頭アドレス
	rootSignatureDesc.NumParameters = _countof(rootParams);			//ルートパラメータ数
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	//ルートシグネチャのシリアライズ
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));
	

	//パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = rootSignature.Get();

	//パイプラインステートの生成
	result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
}



void DXInitialize::ResouceConstBfferM()
{
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;			//GPUへの転送用
	//リソース設定
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0Xff;	//256バイトアライメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

}


void DXInitialize::ConstBufferMaterial()
{
	
	//定数バッファの生成
	result = device->CreateCommittedResource(
		&cbHeapProp,		//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial)
	);
	assert(SUCCEEDED(result));

	//定数バッファのマッピング
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);	//マッピング
	assert(SUCCEEDED(result));

	//値を書き込むと自動的に転送される
	constMapMaterial->color = XMFLOAT4(1, 0, 0, 1);			//RGBAで半透明

}
void DXInitialize::ResouceConstBfferT()
{
}


void DXInitialize::CreateConstBufferT()
{

	for (int i = 0; i < _countof(obj); i++)
	{

		obj[i].Initialize();
		/*if (i > 0)
		{
			obj[i].parent = &obj[i - 1];

			obj[i].scale = { 0.9f,0.9f,0.9f };
			obj[i].rotation = { 0,0,XMConvertToRadians(30.0f) };
			obj[i].translation = { 0,0,-8.0f };
		}*/

	}
	obj[1].translation = {0,0,0 };
	obj[0].translation = { 4.0f,2.0f,5.0f };

}


void DXInitialize::ConstBufferTransform()
{
	CreateConstBufferT();
	
	matProjection = XMMatrixPerspectiveFovLH
	(XMConvertToRadians(45.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f

	);

	eye={ 0, 0, -50 };
	target={ 0, 0, 0 };
	up = { 0, 1, 0 };
	matview = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
	
	/*for (size_t i = 0; i < _countof(obj); i++)
	{
		obj[i].UpdateMatrix(matview, matProjection);
	}*/
}

ConstBufferDataMaterial* DXInitialize::GetconstMapMaterial()
{
	return constMapMaterial;
}



D3D12_DESCRIPTOR_HEAP_DESC DXInitialize::GetrtvHeapDesc()
{
	return rtvHeapDesc;
}

ComPtr<ID3D12PipelineState> DXInitialize::GetpipelineState()
{
	return pipelineState;
}

ComPtr<ID3D12RootSignature> DXInitialize::GetrootSignature()
{
	return rootSignature;
}

ComPtr<ID3D12Resource> DXInitialize::GetconstBuffMaterial()
{
	return constBuffMaterial;
}

ComPtr<ID3D12Fence> DXInitialize::Getfence()
{
	return fence;
}





ComPtr<ID3D12DescriptorHeap> DXInitialize::GetdsvHeap()
{
	return dsvHeap;
}



void DXInitialize::DepthInitilize()
{
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = window_width;
	depthResourceDesc.Height = window_height;
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	//ヒーププロパティ
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;

	//深度値のクリア設定
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff)
	);

	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuff.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart()
	);
	pipelineDesc.DepthStencilState.DepthEnable = true;
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
}



