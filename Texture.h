#pragma once
#include<d3d12.h>
#include<cassert>
#include <DirectXTex.h>

#include<wrl.h>

using namespace Microsoft::WRL;


class Texture
{
private:
#pragma region 画像イメージデータ
	
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};

	DirectX::ScratchImage mipChain{};
#pragma endregion 画像イメージデータ

#pragma region テクスチャバッファ設定
	//ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
#pragma endregion テクスチャバッファ設定

	//SRVの最大数
	const size_t kMaxSRVCount = 2056;

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

#pragma endregion デスクリプタヒープ設定

	//シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	//設定構造体



public:
	//テクスチャバッファの生成
	ComPtr<ID3D12Resource> texBuff = nullptr;
	//設定を元にSRV用デスクリプタヒープを生成
	ComPtr<ID3D12DescriptorHeap> srvHeap = nullptr;

	UINT incrementSize;

	Texture();

	void Initialize(const wchar_t* str);

	void TextureImageData(const wchar_t* str);

	void TextureResourceSet();

	void CreateSRV();

	void TextureBufferTransfer();

	void DescriptorHeap();

	static Texture* GetInstance();


};

