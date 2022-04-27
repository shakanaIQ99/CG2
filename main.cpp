#include<DirectXMath.h>
using namespace DirectX;

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")


#include"DXInitialize.h"
#include"Input.h"
#include"DXWindow.h"





//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E�쐬�R���X�g���N�^
	DXWindow _window;
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
	
#endif	
	HRESULT result;
	//DirectX����������
	DXInitialize* dxInitialize=new DXInitialize(_window.hwnd);
	//���͊֐�
	Input* _input=new Input(_window.w,_window.hwnd);
#pragma region	�`�揉��������


#pragma region ���_�o�b�t�@�̊m��
	//���_�f�[�^
	XMFLOAT3 vertices[] =
	{
		{-0.5f,-0.5f,0.0f},
		{-0.5f,+0.5f,0.0f},
		{+0.5f,-0.5f,0.0f},
	};

	//���_�f�[�^�S�̂̃T�C�Y=���_�f�[�^����̃T�C�Y*���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};		//�q�[�v�ݒ�
	heapProp.Type =D3D12_HEAP_TYPE_UPLOAD;	//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC	resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;					//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//���_�o�b�t�@�̐���
	ID3D12Resource* vertBuff = nullptr;
	result = dxInitialize->device->CreateCommittedResource
	(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));
#pragma endregion ���_�o�b�t�@�̊m��

#pragma region ���_�o�b�t�@�ւ̃f�[�^�]��
	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	XMFLOAT3* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//�S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i]; //���W���R�s�[
	}
	//�q���������
	vertBuff->Unmap(0, nullptr);
#pragma endregion ���_�o�b�t�@�ւ̃f�[�^�]��


#pragma region ���_�o�b�t�@�r���[
	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	//���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(XMFLOAT3);

#pragma endregion ���_�o�b�t�@�r���[

#pragma region	���_�V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��

	ID3DBlob* vsBlob = nullptr; //���_�V�F�[�_�[�I�u�W�F�N�g
	ID3DBlob* psBlob = nullptr; //�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr; //�G���[�I�u�W�F�N�g

	//���_�V�F�[�_�[�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"BasicVS.hlsl", //�V�F�[�_�[�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, //�C���N���[�h�\�ɂ���
		"main", "vs_5_0", //�G���g���[�|�C���g��,�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //�f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);

	//�G���[�Ȃ�
	if (FAILED(result))
	{
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),errorBlob->GetBufferSize(), error.begin());

		error += "\n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

#pragma endregion	���_�V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��

#pragma region	�s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��

	//�s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"BasicPS.hlsl", //�V�F�[�_�[�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, //�C���N���[�h�\�ɂ���
		"main", "ps_5_0", //�G���g���[�|�C���g��,�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //�f�o�b�O�p�ݒ�
		0,
		&psBlob, &errorBlob);

	//�G���[�Ȃ�
	if (FAILED(result))
	{
		//errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize(), error.begin());

		error += "\n";
		//�G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}



#pragma endregion	�s�N�Z���V�F�[�_�t�@�C���̓ǂݍ��݂ƃR���p�C��


	//���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = { {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0}, };


#pragma region �O���t�B�b�N�X�p�C�v���C��

	//�O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//�V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	//�T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; //�W���ݒ�

	//���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; //�J�����O���Ȃ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; //�|���S�����h��Ԃ�
	
	pipelineDesc.RasterizerState.DepthClipEnable = true;	//�[�x�N���b�s���O��L����

	//�u�����h�X�e�[�g
	pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; //RGBA�S�Ẵ`�����l����`��

	//���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);

	//�}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	//0�`255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1;	//1�s�N�Z���ɂ�1��T���v�����O

	//���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
	
	//���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	
	//���[�g�V�O�l�`���̃V���A���C�Y
	ID3DBlob* rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	result = dxInitialize->device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	assert(SUCCEEDED(result));
	rootSigBlob->Release();
	
	//�p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootSignature;

	//�p�C�v���C���X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;
	result = dxInitialize->device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));

#pragma endregion	�O���t�B�b�N�X�p�C�v���C��

#pragma region �O���t�B�b�N�X�p�C�v���C��2

	//�O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc2{};

	//�V�F�[�_�[�̐ݒ�
	pipelineDesc2.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc2.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc2.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc2.PS.BytecodeLength = psBlob->GetBufferSize();

	//�T���v���}�X�N�̐ݒ�
	pipelineDesc2.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; //�W���ݒ�

	//���X�^���C�U�̐ݒ�
	pipelineDesc2.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; //�J�����O���Ȃ�
	
	pipelineDesc2.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME; //���C���[�t���[��(�ǂ��炩�Е�)
	pipelineDesc2.RasterizerState.DepthClipEnable = true;	//�[�x�N���b�s���O��L����

	//�u�����h�X�e�[�g
	pipelineDesc2.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; //RGBA�S�Ẵ`�����l����`��

	//���_���C�A�E�g�̐ݒ�
	pipelineDesc2.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc2.InputLayout.NumElements = _countof(inputLayout);

	//�}�`�̌`��ݒ�
	pipelineDesc2.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//���̑��̐ݒ�
	pipelineDesc2.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc2.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	//0�`255�w���RGBA
	pipelineDesc2.SampleDesc.Count = 1;	//1�s�N�Z���ɂ�1��T���v�����O

	//���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature2;

	//���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc2{};
	rootSignatureDesc2.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//���[�g�V�O�l�`���̃V���A���C�Y
	ID3DBlob* rootSigBlob2 = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc2, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob2, &errorBlob);
	assert(SUCCEEDED(result));
	result = dxInitialize->device->CreateRootSignature(0, rootSigBlob2->GetBufferPointer(), rootSigBlob2->GetBufferSize(), IID_PPV_ARGS(&rootSignature2));
	assert(SUCCEEDED(result));
	rootSigBlob2->Release();

	//�p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc2.pRootSignature = rootSignature2;

	//�p�C�v���C���X�e�[�g�̐���
	ID3D12PipelineState* pipelineState2 = nullptr;
	result = dxInitialize->device->CreateGraphicsPipelineState(&pipelineDesc2, IID_PPV_ARGS(&pipelineState2));
	assert(SUCCEEDED(result));

#pragma endregion	�O���t�B�b�N�X�p�C�v���C��2

#pragma endregion	�`�揉��������


	//�ϐ��������ꏊ
	float color_Blue = 0.5f;
	float color_Red = 0.1f;
	float color_Green = 0.25f;

	bool S = false;

	//�Q�[�����[�v
	while (true)
	{
		//���b�Z�[�W����H
		if (PeekMessage(&_window.msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_window.msg);	//�L�[���̓��b�Z�[�W�̏���
			DispatchMessage(&_window.msg);	//�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}

		//�~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (_window.msg.message == WM_QUIT)
		{
			break;
		}
		#pragma region DirectX���t���[��
		//DirecX���t���[���@��������@�@�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
		
		_input->InputUpdate();
		

		if (_input->GetKey(DIK_SPACE))
		{
			color_Red = 1.0f;
		}
		else
		{
			color_Red = 0.1f;
		}
		if (_input->GetPressKey(DIK_2))
		{
			switch (S)
			{
			case 0:
				S = true;

				break;
			case 1:
				S = false;


			}
		}

		//�o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
		UINT bbIndex = dxInitialize->swapChain->GetCurrentBackBufferIndex();

		//1.���\�[�X�o���A�ŏ������݉\�ɕύX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = dxInitialize->backBuffers[bbIndex];				//�o�b�N�o�b�t�@���w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//�\����Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ�
		dxInitialize->commandList->ResourceBarrier(1, &barrierDesc);

		//2. �`���̕ύX
		//�����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = dxInitialize->rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * dxInitialize->device->GetDescriptorHandleIncrementSize(dxInitialize->rtvHeapDesc.Type);
		dxInitialize->commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

		//3. ��ʃN���A
		FLOAT clearColor[] = { color_Red,color_Green,color_Blue,0.0f };	//�F�̎w���RGBA��0.0f�`1.0f
		
		dxInitialize->commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	#pragma region �`��R�}���h
		//--------------4.�`��R�}���h�@��������---------------//
		
		 //�r���[�|�[�g�ݒ�R�}���h
		D3D12_VIEWPORT viewport{};
		viewport.Width = window_width -window_width/3;
		viewport.Height = window_height- window_height/3;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		//�r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		dxInitialize->commandList->RSSetViewports(1, &viewport);

		

		//�V�U�[��`
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//�؂蔲�����W��
		scissorRect.right = scissorRect.left + window_width;		//�؂蔲�����W�E
		scissorRect.top = 0;										//�؂蔲�����W��
		scissorRect.bottom = scissorRect.top + window_height;		//�؂蔲�����W��
		
		//�V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		dxInitialize->commandList->RSSetScissorRects(1, &scissorRect);

		//�p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		
		if (S)
		{
			dxInitialize->commandList->SetPipelineState(pipelineState2);
			dxInitialize->commandList->SetGraphicsRootSignature(rootSignature2);
		}
		else if(!S)
		{
			dxInitialize->commandList->SetPipelineState(pipelineState);
			dxInitialize->commandList->SetGraphicsRootSignature(rootSignature);
		}
		//�v���~�e�B�u�`��̐ݒ�R�}���h
		dxInitialize->commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//�O�p�`���X�g

		//���_�o�b�t�@�r���[�̐ݒ�R�}���h
		dxInitialize->commandList->IASetVertexBuffers(0, 1, &vbView);

		//�`��R�}���h
		dxInitialize->commandList->DrawInstanced(_countof(vertices), 1, 0, 0);	//�S�Ă̒��_���g���ĕ`��

		//�r���[�|�[�g�ݒ�R�}���h
		D3D12_VIEWPORT viewport2{};
		viewport2.Width = window_width / 3;
		viewport2.Height = window_height - window_height / 3;
		viewport2.TopLeftX = window_width - window_width / 3;
		viewport2.TopLeftY = 0;
		viewport2.MinDepth = 0.0f;
		viewport2.MaxDepth = 1.0f;

		//�r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		dxInitialize->commandList->RSSetViewports(1, &viewport2);

		dxInitialize->commandList->DrawInstanced(_countof(vertices), 1, 0, 0);	//�S�Ă̒��_���g���ĕ`��

		//�r���[�|�[�g�ݒ�R�}���h
		D3D12_VIEWPORT viewport3{};
		viewport3.Width = window_width - window_width / 3;
		viewport3.Height = window_height / 3;
		viewport3.TopLeftX =0;
		viewport3.TopLeftY = window_height-window_height/3;
		viewport3.MinDepth = 0.0f;
		viewport3.MaxDepth = 1.0f;

		//�r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		dxInitialize->commandList->RSSetViewports(1, &viewport3);

		dxInitialize->commandList->DrawInstanced(_countof(vertices), 1, 0, 0);	//�S�Ă̒��_���g���ĕ`��

		//�r���[�|�[�g�ݒ�R�}���h
		D3D12_VIEWPORT viewport4{};
		viewport4.Width = window_width / 3;
		viewport4.Height = window_height / 3;
		viewport4.TopLeftX = window_width - window_width / 3;
		viewport4.TopLeftY = window_height - window_height / 3;
		viewport4.MinDepth = 0.0f;
		viewport4.MaxDepth = 1.0f;

		//�r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		dxInitialize->commandList->RSSetViewports(1, &viewport4);

		dxInitialize->commandList->DrawInstanced(_countof(vertices), 1, 0, 0);	//�S�Ă̒��_���g���ĕ`��

		//--------------4.�`��R�}���h�@�����܂�---------------//
	#pragma endregion �`��R�}���h
		//5. ���\�[�X�o���A��߂�
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//�\����Ԃ�
		dxInitialize->commandList->ResourceBarrier(1, &barrierDesc);

		//���߂̃N���[�Y
		result = dxInitialize->commandList->Close();
		assert(SUCCEEDED(result));
		//�R�}���h���X�g�̎��s
		ID3D12CommandList* commandLists[] = { dxInitialize->commandList };
		dxInitialize->commandQueue->ExecuteCommandLists(1, commandLists);

		//��ʂɕ\������o�b�t�@���t���b�v(���\�̓���ւ�)
		result = dxInitialize->swapChain->Present(1, 0);
		assert(SUCCEEDED(result));

		//�R�}���h�̎��s������҂�
		dxInitialize->commandQueue->Signal(dxInitialize->fence, ++dxInitialize->fenceVal);
		if (dxInitialize->fence->GetCompletedValue() != dxInitialize->fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			dxInitialize->fence->SetEventOnCompletion(dxInitialize->fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//�L���[���N���A
		result = dxInitialize->commandAllocator->Reset();
		assert(SUCCEEDED(result));
		//�ĂуR�}���h���X�g�����߂鏀��
		result = dxInitialize->commandList->Reset(dxInitialize->commandAllocator, nullptr);
		assert(SUCCEEDED(result));


		//DirecX���t���[���@�����܂Ł@�@�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
		#pragma endregion	DirectX���t���[��
	}
	
	delete dxInitialize;
	delete _input;

	return 0;
}
