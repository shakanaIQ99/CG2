#pragma once
#include<d3d12.h>
#include<cassert>
#include <DirectXTex.h>

#include<wrl.h>

using namespace Microsoft::WRL;


class Texture
{
private:
#pragma region �摜�C���[�W�f�[�^
	
	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};

	DirectX::ScratchImage mipChain{};
#pragma endregion �摜�C���[�W�f�[�^

#pragma region �e�N�X�`���o�b�t�@�ݒ�
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
#pragma endregion �e�N�X�`���o�b�t�@�ݒ�

	//SRV�̍ő吔
	const size_t kMaxSRVCount = 2056;

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

#pragma endregion �f�X�N���v�^�q�[�v�ݒ�

	//�V�F�[�_�[���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	//�ݒ�\����



public:
	//�e�N�X�`���o�b�t�@�̐���
	ComPtr<ID3D12Resource> texBuff = nullptr;
	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ComPtr<ID3D12DescriptorHeap> srvHeap = nullptr;

	UINT incrementSize;

	Texture();

	void Initialize(const wchar_t* str);

	void TextureImageData(const wchar_t* str);

	void TextureResourceSet();

	void CreateSRV();

	void CreateSRV2();

	void TextureBufferTransfer();

	void DescriptorHeap();

	static Texture* GetInstance();


};

