#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
	

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

	//�A�_�v�^�[�̗񋓗p
	std::vector <IDXGIAdapter4*>adapters;
	//�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	IDXGIAdapter4* tmpAdapter;

	D3D_FEATURE_LEVEL featureLevel;

	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	//�o�b�N�o�b�t�@
	std::vector<ID3D12Resource*> backBuffers;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	//�t�F���X�̐���
	ID3D12Fence* fence;
	UINT64 fenceVal;

	

public:
	DXInitialize(HWND hwnd);

	
};

