#include "Texture.h"
#include"DXInitialize.h"

Texture::Texture()
{
}

void Texture::Initialize(const wchar_t* str)
{
	TextureImageData(str);

	//ヒープ設定
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	TextureResourceSet();
	TextureBufferTransfer();
	DescriptorHeap();
	CreateSRV();

}

void Texture::TextureImageData(const wchar_t* str)
{
	//WICテクスチャのロード
	result = LoadFromWICFile(
		str,
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);


	//ミニマップ生成
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(), TEX_FILTER_DEFAULT, 0,mipChain
	);
	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャをSRGBとして扱う
	metadata.format = MakeSRGB(metadata.format);
}

void Texture::TextureResourceSet()
{
	HRESULT result;
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;	//幅
	textureResourceDesc.Height = (UINT)metadata.height;	//高さ
	textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//テクスチャバッファの生成
	result = DXInitialize::GetInstance()->Getdevice()->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff)
	);
}

void Texture::CreateSRV()
{
	incrementSize = DXInitialize::GetInstance()->Getdevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	srvHandle.ptr += incrementSize;
	//シェーダーリソースビュー設定
	srvDesc.Format = DXInitialize::GetInstance()->resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = DXInitialize::GetInstance()->resDesc.MipLevels;

	//ハンドルの指す位置にシェーダーリソースビュー作成
	DXInitialize::GetInstance()->Getdevice()->CreateShaderResourceView(texBuff.Get(), &srvDesc, srvHandle);
}

void Texture::CreateSRV2()
{
	//シェーダーリソースビュー設定
	srvDesc.Format = DXInitialize::GetInstance()->resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = DXInitialize::GetInstance()->resDesc.MipLevels;

	//ハンドルの指す位置にシェーダーリソースビュー作成
	DXInitialize::GetInstance()->Getdevice()->CreateShaderResourceView(texBuff.Get(), &srvDesc, srvHandle);
}

void Texture::TextureBufferTransfer()
{
	//全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		//ミップマップレベルを指定してイメージを取得
		const Image* img = scratchImg.GetImage(i, 0, 0);
		//テクスチャバッファにデータ転送
		result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,				//全領域へコピー
			img->pixels,			//元データアドレス
			(UINT)img->rowPitch,	//1ラインサイズ
			(UINT)img->slicePitch	//1枚サイズ
		);
		assert(SUCCEEDED(result));
	}

	////テクスチャバッファにデータ転送
	//result = texBuff->WriteToSubresource(
	//	0,
	//	nullptr,	//全領域へコピー
	//	imageData,	//元データアドレス
	//	sizeof(XMFLOAT4) * textureWidth,	//1ラインサイズ
	//	sizeof(XMFLOAT4) * imageDataCount	//全サイズ
	//);

	//delete[]imageData;
}

void Texture::DescriptorHeap()
{
	
	//デスクリプタヒープの設定
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	//シェーダーから見えるように
	srvHeapDesc.NumDescriptors = kMaxSRVCount;


	//設定を元にSRV用デスクリプタヒープを生成
	result = DXInitialize::GetInstance()->Getdevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	//SRVヒープの先頭ハンドルを取得
	srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

}

Texture* Texture::GetInstance()
{
	static Texture instance;
	return &instance;
}
