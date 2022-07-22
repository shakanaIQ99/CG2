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

#include"DXWindow.h"

#include"Object3D.h"

#include<wrl.h>

using namespace Microsoft::WRL;

//#include"ViewProjection.h"

//���_�f�[�^�\����

struct Vertex
{
	XMFLOAT3 pos;	//xyz���W
	XMFLOAT3 normal;//�@���x�N�g��
	XMFLOAT2 uv;	//uv���W
};







//���_�f�[�^
static Vertex vertices[] =
{
	////x		 y     z	  u    v
	////�O
	//{{-9.4f,-3.3f,-15.0f},{},{0.0f,1.0f}},	//����
	//{{-9.4f, 3.3f,-15.0f},{},{0.0f,0.0f}},	//����
	//{{ 9.4f,-3.3f,-15.0f},{},{1.0f,1.0f}},	//�E��
	//{{ 9.4f, 3.3f,-15.0f},{},{1.0f,0.0f}},	//�E��
	////��				{}	 ,
	//{{-9.4f,-3.3f, 15.0f},{},{0.0f,1.0f}},	//����
	//{{-9.4f, 3.3f, 15.0f},{},{0.0f,0.0f}},	//����
	//{{ 9.4f,-3.3f, 15.0f},{},{1.0f,1.0f}},	//�E��
	//{{ 9.4f, 3.3f, 15.0f},{},{1.0f,0.0f}},	//�E��
	////��				{}	 ,
	//{{-9.4f,-3.3f,-15.0f},{},{0.0f,1.0f}},	//����
	//{{-9.4f, 3.3f,-15.0f},{},{0.0f,0.0f}},	//����
	//{{-9.4f,-3.3f, 15.0f},{},{1.0f,1.0f}},	//�E��
	//{{-9.4f, 3.3f, 15.0f},{},{1.0f,0.0f}},	//�E��
	////�E				{}	 ,
	//{{ 9.4f,-3.3f, 15.0f},{},{0.0f,1.0f}},	//����
	//{{ 9.4f, 3.3f, 15.0f},{},{0.0f,0.0f}},	//����
	//{{ 9.4f,-3.3f,-15.0f},{},{1.0f,1.0f}},	//�E��
	//{{ 9.4f, 3.3f,-15.0f},{},{1.0f,0.0f}},	//�E��
	////��				{}	 ,
	//{{-9.4f,-3.3f,-15.0f},{},{0.0f,1.0f}},	//����
	//{{ 9.4f,-3.3f,-15.0f},{},{0.0f,0.0f}},	//����
	//{{-9.4f,-3.3f, 15.0f},{},{1.0f,1.0f}},	//�E��
	//{{ 9.4f,-3.3f, 15.0f},{},{1.0f,0.0f}},	//�E��
	////��				{}	 ,
	//{{-9.4f, 3.3f,-15.0f},{},{0.0f,1.0f}},	//����
	//{{ 9.4f, 3.3f,-15.0f},{},{0.0f,0.0f}},	//����
	//{{-9.4f, 3.3f, 15.0f},{},{1.0f,1.0f}},	//�E��
	//{{ 9.4f, 3.3f, 15.0f},{},{1.0f,0.0f}},	//�E��

	//x		 y     z	  u    v
	//�O
	{{-5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f,-5.0f},{},{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f,-5.0f},{},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f,-5.0f},{},{1.0f,0.0f}},	//�E��
	//��	5.90	{}	 ,
	{{-5.0f,-5.0f, 5.0f},{},{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f, 5.0f},{},{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f, 5.0f},{},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{},{1.0f,0.0f}},	//�E��
	//��	5.90	{}	 ,
	{{-5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},	//����
	{{-5.0f, 5.0f,-5.0f},{},{0.0f,0.0f}},	//����
	{{-5.0f,-5.0f, 5.0f},{},{1.0f,1.0f}},	//�E��
	{{-5.0f, 5.0f, 5.0f},{},{1.0f,0.0f}},	//�E��
	//�E	5.90	{}	 ,
	{{ 5.0f,-5.0f, 5.0f},{},{0.0f,1.0f}},	//����
	{{ 5.0f, 5.0f, 5.0f},{},{0.0f,0.0f}},	//����
	{{ 5.0f,-5.0f,-5.0f},{},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f,-5.0f},{},{1.0f,0.0f}},	//�E��
	//��	5.90	{}	 ,
	{{-5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},	//����
	{{ 5.0f,-5.0f,-5.0f},{},{0.0f,0.0f}},	//����
	{{-5.0f,-5.0f, 5.0f},{},{1.0f,1.0f}},	//�E��
	{{ 5.0f,-5.0f, 5.0f},{},{1.0f,0.0f}},	//�E��
	//��	5.90	{}	 ,
	{{-5.0f, 5.0f,-5.0f},{},{0.0f,1.0f}},	//����
	{{ 5.0f, 5.0f,-5.0f},{},{0.0f,0.0f}},	//����
	{{-5.0f, 5.0f, 5.0f},{},{1.0f,1.0f}},	//�E��
	{{ 5.0f, 5.0f, 5.0f},{},{1.0f,0.0f}},	//�E��
};

//�C���f�b�N�X�f�[�^
static unsigned short indices[] =
{
	//�O
	0,1,2,//�O�p�`1��
	2,1,3,//�O�p�`2��
	//��
	6,7,4,//�O�p�`3��  341
	4,7,5,//�O�p�`4��  142
	//��
	10,11,8,//�O�p�`5��
	8,11,9,//�O�p�`6��
	////�E
	14,15,12,
	12,15,13,
	////��
	16,17,18,
	18,17,19,
	////��
	22,23,20,
	20,23,21,
};

//���_���C�A�E�g
static D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
	{/*xyZ���W*/"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{/*�@���x�N�g��*/"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
	{/*���Wuv*/"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
};

//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDataMaterial
{
	XMFLOAT4 color;
};

//struct ConstBufferDataTransform
//{
//	XMMATRIX mat;
//};


static HRESULT result;

class DXInitialize
{
private:

	DXInitialize();


	
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	

	DXGI_ADAPTER_DESC3 adapterDesc;
	//�A�_�v�^�[�̗񋓗p
	std::vector <ComPtr<IDXGIAdapter4>>adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter;

	D3D_FEATURE_LEVEL featureLevel;

	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};


	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	//�[�x�o�b�t�@���\�[�X
	D3D12_RESOURCE_DESC depthResourceDesc{};
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	D3D12_CLEAR_VALUE depthClearValue{};
	ComPtr<ID3D12Resource> depthBuff = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap> dsvHeap = nullptr;
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

	//�t�F���X�̐���
	ComPtr<ID3D12Fence> fence;

	//���_�f�[�^�S�̂̃T�C�Y=���_�f�[�^����̃T�C�Y*���_�f�[�^�̗v�f��
	UINT sizeVB;

	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB;

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};		//�q�[�v�ݒ�
	

	//���_�o�b�t�@�̐���
	ComPtr<ID3D12Resource> vertBuff;

	//�C���f�b�N�X�o�b�t�@�̐���
	ComPtr<ID3D12Resource> indexBuff;

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	Vertex* vertMap = nullptr;

	uint16_t* indexMap = nullptr;





	ComPtr<ID3DBlob> vsBlob = nullptr; //���_�V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob = nullptr; //�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob = nullptr; //�G���[�I�u�W�F�N�g

	//�O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//�f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[3] = {};

	//�e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};

	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;

	//���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};

	//���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob = nullptr;

	//�p�C�v���C���X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState = nullptr;

#pragma region �萔�o�b�t�@
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc{};

	//�萔�o�b�t�@�̃}�b�s���O
	ComPtr<ID3D12Resource> constBuffMaterial = nullptr;
	ConstBufferDataMaterial* constMapMaterial = nullptr;


	/*ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	ConstBufferDataTransform* constMapTransform = nullptr;*/


#pragma endregion �萔�o�b�t�@

#pragma region �摜�C���[�W�f�[�^
//	TexMetadata metadata{};
//	ScratchImage scratchImg{};
//
//	TexMetadata metadata2{};
//	ScratchImage scratchImg2{};
//
//	ScratchImage mipChain{};
//#pragma endregion �摜�C���[�W�f�[�^
//
//#pragma region �e�N�X�`���o�b�t�@�ݒ�
//	//�q�[�v�ݒ�
//	D3D12_HEAP_PROPERTIES textureHeapProp{};
//	//���\�[�X�ݒ�
//	D3D12_RESOURCE_DESC textureResourceDesc{};
//	//�e�N�X�`���o�b�t�@�̐���
//	ID3D12Resource* texBuff = nullptr;
//
//	//�e�N�X�`���o�b�t�@�̐���
//	ID3D12Resource* texBuff2 = nullptr;
#pragma endregion �e�N�X�`���o�b�t�@�ݒ�

#pragma region �f�X�N���v�^�q�[�v�ݒ�

	//SRV�̍ő吔
//	const size_t kMaxSRVCount = 2056;
//
//	//�f�X�N���v�^�q�[�v�̐ݒ�
//	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
//	//SRV�q�[�v�̐擪�n���h�����擾
//	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;
//
//#pragma endregion �f�X�N���v�^�q�[�v�ݒ�
//
//	//�V�F�[�_�[���\�[�X�r���[�ݒ�
//	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	//�ݒ�\����

	

	



public:
	XMMATRIX matProjection;

	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC	resDesc{};

	XMMATRIX matview;
	////�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	//ID3D12DescriptorHeap* srvHeap = nullptr;
	//�o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers;

	XMFLOAT3 eye;
	XMFLOAT3 target;
	XMFLOAT3 up;

	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	

	XMMATRIX GetmatProjection();
	XMMATRIX Getmatview();

	
	static const size_t objnum = 50;

	Object3D obj[objnum];
	
	void Initialize(HWND hwnd);

	void DxDrawIni();

	ComPtr<ID3D12Device> Getdevice();
	ComPtr<IDXGIFactory7> GetdxgiFactory();
	ComPtr<IDXGISwapChain4> GetswapChain();
	ComPtr<ID3D12CommandAllocator> GetcommandAllocator();
	ComPtr<ID3D12GraphicsCommandList> GetcommandList();
	ComPtr<ID3D12CommandQueue> GetcommandQueue();
	ComPtr<ID3D12DescriptorHeap> GetrtvHeap();

	static DXInitialize* GetInstance();

	ConstBufferDataMaterial* GetconstMapMaterial();
	ComPtr<ID3D12DescriptorHeap> GetdsvHeap();
	D3D12_DESCRIPTOR_HEAP_DESC GetrtvHeapDesc();

	ComPtr<ID3D12PipelineState> GetpipelineState();
	ComPtr<ID3D12RootSignature> GetrootSignature();

	ComPtr<ID3D12Resource> GetconstBuffMaterial();

	ComPtr<ID3D12Fence> Getfence();
	
	UINT64 fenceVal;

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

	void ResouceConstBfferM();

	void ResouceConstBfferT();

	void CreateConstBufferT();

	void ConstBufferMaterial();

	void ConstBufferTransform();

	//void TextureImageData(const wchar_t *str);
	//

	//void TextureBuffer();

	//void TBufferTransfer();

};

