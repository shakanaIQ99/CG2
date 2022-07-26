
#include"DXInitialize.h"
#include"Texture.h"
#include"Input.h"
#include"DXWindow.h"
//#include"WorldTransform.h"
#include <DirectXTex.h>

#include"Vector3.h"

void ConvertCont(int num);

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E�쐬�R���X�g���N�^
	DXWindow _window;
#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ComPtr<ID3D12Debug1> debugController;
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}

	
	
#endif	
	HRESULT result;
	//DirectX����������
	DXInitialize::GetInstance()->Initialize(_window.hwnd);

	
	//���͊֐�
	Input _input(_window.w, _window.hwnd);

	DXInitialize::GetInstance()->DxDrawIni();
//#ifdef _DEBUG
//	//�f�o�b�O���C���[���I����
//	ID3D12InfoQueue* infoQueue;
//	if (SUCCEEDED(DXInitialize::GetInstance()->Getdevice().Get()->QueryInterface(IID_PPV_ARGS(&infoQueue))))
//	{
//		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
//		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
//		infoQueue->Release();
//	}
//
//#endif	
//


	//�ϐ��������ꏊ

	Texture::GetInstance()->Initialize(L"Resources/genba.jpg");

	bool color_Red = false;
	bool color_Green =false;
	bool color_Blue = false;

	int color_lv = 0;

	float CC = 0.02f;

	float angle = 0.0f;

	int num = 0;

	XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
	Vector3 scale = Vector3(1, 1, 1);
	Vector3 rotation = Vector3(0, 0, 0);

	//XMMATRIX matTrans;

	/*Matrix4 matWorld;
	Matrix4 matScale;
	Matrix4 matRot;
	Matrix4 matTrans;*/

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
		
		//�L�[�{�[�h���̎擾�J�n
		_input.InputUpdate();

		switch (color_lv)
		{
		case 0:
			color_Red = true;
			color_Green = false;
			color_Blue = false;
			break;
		case 1:
			color_Red = false;
			color_Green =true;
			color_Blue = false;
			break;
		case 2:
			color_Red = false;
			color_Green = false;
			color_Blue = true;
			break;
		}

		


		if (_input.GetKey(DIK_UP))
		{
			CC += 0.0002f;
		}
		if (_input.GetKey(DIK_DOWN))
		{
			CC -= 0.0002f;
		}

		//box.scale = { 1,1,1 };
		if (_input.GetPressKey(DIK_C))
		{
			switch (num)
			{
				case 0:
					num = 1;
					break;
				case 1:
					num = 0;
					break;
			}
		}

		if (num == 0)
		{
			if (_input.GetKey(DIK_UP)) { DXInitialize::GetInstance()->obj[0].translation.y += 1.0f; }
			if (_input.GetKey(DIK_DOWN)) { DXInitialize::GetInstance()->obj[0].translation.y -= 1.0f; }
			if (_input.GetKey(DIK_RIGHT)) { DXInitialize::GetInstance()->obj[0].translation.x += 1.0f; }
			if (_input.GetKey(DIK_LEFT)) { DXInitialize::GetInstance()->obj[0].translation.x -= 1.0f; }
			if (_input.GetKey(DIK_W)) { DXInitialize::GetInstance()->obj[0].translation.z += 1.0f; }
			if (_input.GetKey(DIK_S)) { DXInitialize::GetInstance()->obj[0].translation.z -= 1.0f; }
			if (_input.GetKey(DIK_Z)) { DXInitialize::GetInstance()->obj[0].rotation.z += 0.02f; }
			if (_input.GetKey(DIK_X)) { DXInitialize::GetInstance()->obj[0].rotation.x += 0.02f; }
			if (_input.GetKey(DIK_Y)) { DXInitialize::GetInstance()->obj[0].rotation.y += 0.02f; }
		}
		if (num == 1)
		{
			if (_input.GetKey(DIK_UP)) { DXInitialize::GetInstance()->obj[1].translation.y += 1.0f; }
			if (_input.GetKey(DIK_DOWN)) { DXInitialize::GetInstance()->obj[1].translation.y -= 1.0f; }
			if (_input.GetKey(DIK_RIGHT)) { DXInitialize::GetInstance()->obj[1].translation.x += 1.0f; }
			if (_input.GetKey(DIK_LEFT)) { DXInitialize::GetInstance()->obj[1].translation.x -= 1.0f; }
			if (_input.GetKey(DIK_W)) { DXInitialize::GetInstance()->obj[1].translation.z += 1.0f; }
			if (_input.GetKey(DIK_S)) { DXInitialize::GetInstance()->obj[1].translation.z -= 1.0f; }
			if (_input.GetKey(DIK_Z)) { DXInitialize::GetInstance()->obj[1].rotation.z += 0.02f; }
			if (_input.GetKey(DIK_X)) { DXInitialize::GetInstance()->obj[1].rotation.x += 0.02f; }
			if (_input.GetKey(DIK_Y)) { DXInitialize::GetInstance()->obj[1].rotation.y += 0.02f; }
		}
		
		

		if (!_input.GetKey(DIK_SPACE))
		{
			if (color_Red)
			{
				DXInitialize::GetInstance()->GetconstMapMaterial()->color.x += CC;
				DXInitialize::GetInstance()->GetconstMapMaterial()->color.z -= CC;
				if (DXInitialize::GetInstance()->GetconstMapMaterial()->color.x > 1.0f)
				{
					color_lv = 1;
				}
			}
			if (color_Green)
			{
				DXInitialize::GetInstance()->GetconstMapMaterial()->color.y += CC;
				DXInitialize::GetInstance()->GetconstMapMaterial()->color.x -= CC;
				if (DXInitialize::GetInstance()->GetconstMapMaterial()->color.y > 1.0f)
				{
					color_lv = 2;
				}
			}
			if (color_Blue)
			{
				DXInitialize::GetInstance()->GetconstMapMaterial()->color.z += CC;
				DXInitialize::GetInstance()->GetconstMapMaterial()->color.y -= CC;
				if (DXInitialize::GetInstance()->GetconstMapMaterial()->color.z > 1.0f)
				{
					color_lv = 0;
				}
			}
			rotation.z += 4.0f;
			
			
		}
		if(DXInitialize::GetInstance()->GetconstMapMaterial()->color.w>=0|| DXInitialize::GetInstance()->GetconstMapMaterial()->color.w <= 1)
		if (_input.GetKey(DIK_Q)) { DXInitialize::GetInstance()->GetconstMapMaterial()->color.w += CC; }
		if (_input.GetKey(DIK_E)) { DXInitialize::GetInstance()->GetconstMapMaterial()->color.w -= CC; }
		
		

		if (_input.GetKey(DIK_D) || _input.GetKey(DIK_A))
		{
			if (_input.GetKey(DIK_D)) { angle += XMConvertToRadians(1.0f); }
			if (_input.GetKey(DIK_A)) { angle -= XMConvertToRadians(1.0f); }

			DXInitialize::GetInstance()->eye.x = -50 * sinf(angle);
			DXInitialize::GetInstance()->eye.z = -50 * cosf(angle);
			DXInitialize::GetInstance()->matview = XMMatrixLookAtLH(XMLoadFloat3(&DXInitialize::GetInstance()->eye), XMLoadFloat3(&DXInitialize::GetInstance()->target), XMLoadFloat3(&DXInitialize::GetInstance()->up));

		}

		
		DXInitialize::GetInstance()->obj[0].UpdateMatrix(DXInitialize::GetInstance()->matview, DXInitialize::GetInstance()->matProjection);
		DXInitialize::GetInstance()->obj[1].UpdateMatrix(DXInitialize::GetInstance()->matview, DXInitialize::GetInstance()->matProjection);
		/*for (size_t i = 0; i < _countof(DXInitialize::GetInstance()->obj); i++)
		{
			DXInitialize::GetInstance()->obj[i].UpdateMatrix(DXInitialize::GetInstance()->matview , DXInitialize::GetInstance()->matProjection);
		}*/

		//�o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
		UINT bbIndex = DXInitialize::GetInstance()->GetswapChain()->GetCurrentBackBufferIndex();

		//1.���\�[�X�o���A�ŏ������݉\�ɕύX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = DXInitialize::GetInstance()->backBuffers[bbIndex].Get();				//�o�b�N�o�b�t�@���w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//�\����Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ�
		DXInitialize::GetInstance()->GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//2. �`���̕ύX
		//�����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = DXInitialize::GetInstance()->GetrtvHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * DXInitialize::GetInstance()->Getdevice()->GetDescriptorHandleIncrementSize(DXInitialize::GetInstance()->GetrtvHeapDesc().Type);
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DXInitialize::GetInstance()->GetdsvHeap()->GetCPUDescriptorHandleForHeapStart();
		DXInitialize::GetInstance()->GetcommandList()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		//3. ��ʃN���A
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//�F�̎w���RGBA��0.0f�`1.0f
		
		DXInitialize::GetInstance()->GetcommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		DXInitialize::GetInstance()->GetcommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	#pragma region �`��R�}���h
		//--------------4.�`��R�}���h�@��������---------------//
		
		 //�r���[�|�[�g�ݒ�R�}���h
		D3D12_VIEWPORT viewport{};
		viewport.Width = window_width;
		viewport.Height = window_height;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		//�r���[�|�[�g�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		DXInitialize::GetInstance()->GetcommandList()->RSSetViewports(1, &viewport);

		//�V�U�[��`
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//�؂蔲�����W��
		scissorRect.right = scissorRect.left + window_width;		//�؂蔲�����W�E
		scissorRect.top = 0;										//�؂蔲�����W��
		scissorRect.bottom = scissorRect.top + window_height;		//�؂蔲�����W��
		
		//�V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		DXInitialize::GetInstance()->GetcommandList()->RSSetScissorRects(1, &scissorRect);

		//�p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		DXInitialize::GetInstance()->GetcommandList()->SetPipelineState(DXInitialize::GetInstance()->GetpipelineState().Get());
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootSignature(DXInitialize::GetInstance()->GetrootSignature().Get());
		
		//�v���~�e�B�u�`��̐ݒ�R�}���h
		DXInitialize::GetInstance()->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//�O�p�`���X�g

		//���_�o�b�t�@�r���[�̐ݒ�R�}���h
		//dxInitialize.GetcommandList()->IASetVertexBuffers(0, 1, &dxInitialize.vbView);

		//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootConstantBufferView(0, DXInitialize::GetInstance()->GetconstBuffMaterial()->GetGPUVirtualAddress());

		//SRV�q�[�v�̐ݒ�R�}���h
		DXInitialize::GetInstance()->GetcommandList()->SetDescriptorHeaps(1, Texture::GetInstance()->srvHeap.GetAddressOf());

		//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = Texture::GetInstance()->srvHeap->GetGPUDescriptorHandleForHeapStart();
		
		srvGpuHandle.ptr += Texture::GetInstance()->incrementSize;

		//SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		////�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		//dxInitialize.GetcommandList()->SetGraphicsRootConstantBufferView(2,dxInitialize.obj->constBuffTransform->GetGPUVirtualAddress());

		//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
		//dxInitialize.GetcommandList()->IASetIndexBuffer(&dxInitialize.ibView);

		////�`��R�}���h
		//dxInitialize.GetcommandList()->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);	//�S�Ă̒��_���g���ĕ`��
		DXInitialize::GetInstance()->obj[1].DrawOBJ(3);
		DXInitialize::GetInstance()->obj[0].DrawOBJ(_countof(indices));
		/*for (int i = 0; i < _countof(DXInitialize::GetInstance()->obj); i++)
		{
			DXInitialize::GetInstance()->obj[i].DrawOBJ(_countof(indices));
		}*/

		//--------------4.�`��R�}���h�@�����܂�---------------//
	#pragma endregion �`��R�}���h
		//5. ���\�[�X�o���A��߂�
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//�\����Ԃ�
		DXInitialize::GetInstance()->GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//���߂̃N���[�Y
		result = DXInitialize::GetInstance()->GetcommandList()->Close();
		assert(SUCCEEDED(result));
		//�R�}���h���X�g�̎��s
		ID3D12CommandList* commandLists[] = { DXInitialize::GetInstance()->GetcommandList().Get()};
		DXInitialize::GetInstance()->GetcommandQueue()->ExecuteCommandLists(1, commandLists);

		//��ʂɕ\������o�b�t�@���t���b�v(���\�̓���ւ�)
		result = DXInitialize::GetInstance()->GetswapChain()->Present(1, 0);
		assert(SUCCEEDED(result));

		//�R�}���h�̎��s������҂�
		DXInitialize::GetInstance()->GetcommandQueue()->Signal(DXInitialize::GetInstance()->Getfence().Get(), ++DXInitialize::GetInstance()->fenceVal);
		if (DXInitialize::GetInstance()->Getfence()->GetCompletedValue() != DXInitialize::GetInstance()->fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			DXInitialize::GetInstance()->Getfence()->SetEventOnCompletion(DXInitialize::GetInstance()->fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//�L���[���N���A
		result = DXInitialize::GetInstance()->GetcommandAllocator()->Reset();
		assert(SUCCEEDED(result));
		//�ĂуR�}���h���X�g�����߂鏀��
		result = DXInitialize::GetInstance()->GetcommandList()->Reset(DXInitialize::GetInstance()->GetcommandAllocator().Get(), nullptr);
		assert(SUCCEEDED(result));


		//DirecX���t���[���@�����܂Ł@�@�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
		#pragma endregion	DirectX���t���[��
	}
	
	
	

	return 0;
}
