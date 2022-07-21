#include "Texture.h"
#include"DXInitialize.h"

Texture::Texture()
{
}

void Texture::Initialize(const wchar_t* str)
{
	TextureImageData(str);

	//�q�[�v�ݒ�
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
	//WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		str,
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);


	//�~�j�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(), TEX_FILTER_DEFAULT, 0,mipChain
	);
	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);
}

void Texture::TextureResourceSet()
{
	HRESULT result;
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;	//��
	textureResourceDesc.Height = (UINT)metadata.height;	//����
	textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//�e�N�X�`���o�b�t�@�̐���
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
	//�V�F�[�_�[���\�[�X�r���[�ݒ�
	srvDesc.Format = DXInitialize::GetInstance()->resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = DXInitialize::GetInstance()->resDesc.MipLevels;

	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	DXInitialize::GetInstance()->Getdevice()->CreateShaderResourceView(texBuff.Get(), &srvDesc, srvHandle);
}

void Texture::TextureBufferTransfer()
{
	//�S�~�b�v�}�b�v�ɂ���
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		//�~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
		const Image* img = scratchImg.GetImage(i, 0, 0);
		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,				//�S�̈�փR�s�[
			img->pixels,			//���f�[�^�A�h���X
			(UINT)img->rowPitch,	//1���C���T�C�Y
			(UINT)img->slicePitch	//1���T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	////�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	//result = texBuff->WriteToSubresource(
	//	0,
	//	nullptr,	//�S�̈�փR�s�[
	//	imageData,	//���f�[�^�A�h���X
	//	sizeof(XMFLOAT4) * textureWidth,	//1���C���T�C�Y
	//	sizeof(XMFLOAT4) * imageDataCount	//�S�T�C�Y
	//);

	//delete[]imageData;
}

void Texture::DescriptorHeap()
{
	
	//�f�X�N���v�^�q�[�v�̐ݒ�
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;	//�V�F�[�_�[���猩����悤��
	srvHeapDesc.NumDescriptors = kMaxSRVCount;


	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = DXInitialize::GetInstance()->Getdevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	//SRV�q�[�v�̐擪�n���h�����擾
	srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

}

Texture* Texture::GetInstance()
{
	static Texture instance;
	return &instance;
}
