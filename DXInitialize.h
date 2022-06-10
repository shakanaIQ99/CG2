#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>
#include<DirectXMath.h>
using namespace DirectX;

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
	
#include <DirectXTex.h>

//#include"ViewProjection.h"

//頂点データ構造体

struct Vertex
{
	XMFLOAT3 pos;	//xyz座標
	XMFLOAT3 normal;//法線ベクトル
	XMFLOAT2 uv;	//uv座標
};







//頂点データ
static Vertex vertices[] =
{
	//x		 y     z	  u    v
	//前
	{{-9.4f,-3.3f,-15.0f},{},{0.0f,1.0f}},	//左下
	{{-9.4f, 3.3f,-15.0f},{},{0.0f,0.0f}},	//左上
	{{ 9.4f,-3.3f,-15.0f},{},{1.0f,1.0f}},	//右下
	{{ 9.4f, 3.3f,-15.0f},{},{1.0f,0.0f}},	//右上
	//後				{}	 ,
	{{-9.4f,-3.3f, 15.0f},{},{0.0f,1.0f}},	//左下
	{{-9.4f, 3.3f, 15.0f},{},{0.0f,0.0f}},	//左上
	{{ 9.4f,-3.3f, 15.0f},{},{1.0f,1.0f}},	//右下
	{{ 9.4f, 3.3f, 15.0f},{},{1.0f,0.0f}},	//右上
	//左				{}	 ,
	{{-9.4f,-3.3f,-15.0f},{},{0.0f,1.0f}},	//左下
	{{-9.4f, 3.3f,-15.0f},{},{0.0f,0.0f}},	//左上
	{{-9.4f,-3.3f, 15.0f},{},{1.0f,1.0f}},	//右下
	{{-9.4f, 3.3f, 15.0f},{},{1.0f,0.0f}},	//右上
	//右				{}	 ,
	{{ 9.4f,-3.3f, 15.0f},{},{0.0f,1.0f}},	//左下
	{{ 9.4f, 3.3f, 15.0f},{},{0.0f,0.0f}},	//左上
	{{ 9.4f,-3.3f,-15.0f},{},{1.0f,1.0f}},	//右下
	{{ 9.4f, 3.3f,-15.0f},{},{1.0f,0.0f}},	//右上
	//下				{}	 ,
	{{-9.4f,-3.3f,-15.0f},{},{0.0f,1.0f}},	//左下
	{{ 9.4f,-3.3f,-15.0f},{},{0.0f,0.0f}},	//左上
	{{-9.4f,-3.3f, 15.0f},{},{1.0f,1.0f}},	//右下
	{{ 9.4f,-3.3f, 15.0f},{},{1.0f,0.0f}},	//右上
	//上				{}	 ,
	{{-9.4f, 3.3f,-15.0f},{},{0.0f,1.0f}},	//左下
	{{ 9.4f, 3.3f,-15.0f},{},{0.0f,0.0f}},	//左上
	{{-9.4f, 3.3f, 15.0f},{},{1.0f,1.0f}},	//右下
	{{ 9.4f, 3.3f, 15.0f},{},{1.0f,0.0f}},	//右上
};

//インデックスデータ
static unsigned short indices[] =
{
	//前
	0,1,2,//三角形1つ目
	2,1,3,//三角形2つ目
	//後
	6,7,4,//三角形3つ目  341
	4,7,5,//三角形4つ目  142
	//左
	10,11,8,//三角形5つ目
	8,11,9,//三角形6つ目
	////右
	14,15,12,
	12,15,13,
	////下
	16,17,18,
	18,17,19,
	////上
	22,23,20,
	20,23,21,
};

//頂点レイアウト
static D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	{/*xyZ座標*/"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{/*法線ベクトル*/"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{/*座標uv*/"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
};

//定数バッファ用データ構造体(マテリアル)
static struct ConstBufferDataMaterial
{
	XMFLOAT4 color;
};

static struct ConstBufferDataTransform
{
	XMMATRIX mat;
};


static HRESULT result;

class DXInitialize
{
public:

	ID3D12Device* device;
	IDXGIFactory7* dxgiFactory;
	IDXGISwapChain4* swapChain;
	ID3D12CommandAllocator* commandAllocator;
	ID3D12GraphicsCommandList* commandList;
	ID3D12CommandQueue* commandQueue;
	ID3D12DescriptorHeap* rtvHeap;
	
	DXGI_ADAPTER_DESC3 adapterDesc;

	//アダプターの列挙用
	std::vector <IDXGIAdapter4*>adapters;
	//ここに特定の名前を持つアダプターオブジェクトが入る
	IDXGIAdapter4* tmpAdapter;

	D3D_FEATURE_LEVEL featureLevel;

	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	//スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	//バックバッファ
	std::vector<ID3D12Resource*> backBuffers;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	//レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	//深度バッファリソース
	D3D12_RESOURCE_DESC depthResourceDesc{};
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	D3D12_CLEAR_VALUE depthClearValue{};
	ID3D12Resource* depthBuff = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ID3D12DescriptorHeap* dsvHeap = nullptr;
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

	//フェンスの生成
	ID3D12Fence* fence;
	UINT64 fenceVal;

	//頂点データ全体のサイズ=頂点データ一つ分のサイズ*頂点データの要素数
	UINT sizeVB;

	//インデックスデータ全体のサイズ
	UINT sizeIB;

	//頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};		//ヒープ設定
	
	//リソース設定
	D3D12_RESOURCE_DESC	resDesc{};

	//頂点バッファの生成
	ID3D12Resource* vertBuff;

	//インデックスバッファの生成
	ID3D12Resource* indexBuff;

	//GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	Vertex* vertMap = nullptr;

	uint16_t* indexMap = nullptr;

	//頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};

	ID3DBlob* vsBlob = nullptr; //頂点シェーダーオブジェクト
	ID3DBlob* psBlob = nullptr; //ピクセルシェーダーオブジェクト
	ID3DBlob* errorBlob = nullptr; //エラーオブジェクト

	//グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[3] = {};

	//テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};

	//ルートシグネチャ
	ID3D12RootSignature* rootSignature;

	//ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};

	//ルートシグネチャのシリアライズ
	ID3DBlob* rootSigBlob = nullptr;

	//パイプラインステートの生成
	ID3D12PipelineState* pipelineState = nullptr;

#pragma region 定数バッファ
	//ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};

	ID3D12Resource* constBuffMaterial = nullptr;
	//定数バッファのマッピング
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	ID3D12Resource* constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;

#pragma endregion 定数バッファ

#pragma region 画像イメージデータ
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};
#pragma endregion 画像イメージデータ

#pragma region テクスチャバッファ設定
	//ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	//テクスチャバッファの生成
	ID3D12Resource* texBuff = nullptr;
#pragma endregion テクスチャバッファ設定

#pragma region デスクリプタヒープ設定

	//SRVの最大数
	const size_t kMaxSRVCount = 2056;

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	//設定を元にSRV用デスクリプタヒープを生成
	ID3D12DescriptorHeap* srvHeap = nullptr;
	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

#pragma endregion デスクリプタヒープ設定

	//シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	//設定構造体
	XMMATRIX matProjection;
	XMMATRIX matview;
	XMFLOAT3 eye;
	XMFLOAT3 target;
	XMFLOAT3 up;


public:
	DXInitialize(HWND hwnd);



	void DxDrawIni();

private:

	void DepthInitilize();


	void VertexBufferInitialize();
	void IndexBufferInitialize();

	void housenn();

	void VBufferTransfer();
	void IBufferTransfer();

	void VBView();
	void IBView();

	void VSFileReadCompile();
	void PSFileReadCompile();

	void GraphicsPipeLine();

	void ConstBufferMaterial();

	void ConstBufferTransform();

	void TextureImageData();

	void TextureBuffer();

	void TBufferTransfer();

	void DescriptorHeap();

	void ShaderResourceView();
};

