

#include"DXInitialize.h"
#include"Input.h"
#include"DXWindow.h"

#include <DirectXTex.h>



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
	DXInitialize dxInitialize(_window.hwnd);
	//���͊֐�
	Input _input(_window.w, _window.hwnd);

	dxInitialize.DxDrawIni();



	//�ϐ��������ꏊ
	bool color_Red = false;
	bool color_Green =false;
	bool color_Blue = false;

	int color_lv = 0;

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

		if (color_Red)
		{
			dxInitialize.constMapMaterial->color.x += 0.04f;
			dxInitialize.constMapMaterial->color.z -= 0.04f;
			if (dxInitialize.constMapMaterial->color.x > 1.0f)
			{
				color_lv = 1;
			}
		}
		if (color_Green)
		{
			dxInitialize.constMapMaterial->color.y += 0.04f;
			dxInitialize.constMapMaterial->color.x -= 0.04f;
			if (dxInitialize.constMapMaterial->color.y > 1.0f)
			{
				color_lv = 2;
			}
		}
		if (color_Blue)
		{
			dxInitialize.constMapMaterial->color.z += 0.04f;
			dxInitialize.constMapMaterial->color.y -= 0.04f;
			if (dxInitialize.constMapMaterial->color.z > 1.0f)
			{
				color_lv = 0;
			}
		}


		//�o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
		UINT bbIndex = dxInitialize.swapChain->GetCurrentBackBufferIndex();

		//1.���\�[�X�o���A�ŏ������݉\�ɕύX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = dxInitialize.backBuffers[bbIndex];				//�o�b�N�o�b�t�@���w��
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//�\����Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ�
		dxInitialize.commandList->ResourceBarrier(1, &barrierDesc);

		//2. �`���̕ύX
		//�����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = dxInitialize.rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * dxInitialize.device->GetDescriptorHandleIncrementSize(dxInitialize.rtvHeapDesc.Type);
		dxInitialize.commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

		//3. ��ʃN���A
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//�F�̎w���RGBA��0.0f�`1.0f
		
		dxInitialize.commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
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
		dxInitialize.commandList->RSSetViewports(1, &viewport);

		//�V�U�[��`
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//�؂蔲�����W��
		scissorRect.right = scissorRect.left + window_width;		//�؂蔲�����W�E
		scissorRect.top = 0;										//�؂蔲�����W��
		scissorRect.bottom = scissorRect.top + window_height;		//�؂蔲�����W��
		
		//�V�U�[��`�ݒ�R�}���h���A�R�}���h���X�g�ɐς�
		dxInitialize.commandList->RSSetScissorRects(1, &scissorRect);

		//�p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
		dxInitialize.commandList->SetPipelineState(dxInitialize.pipelineState);
		dxInitialize.commandList->SetGraphicsRootSignature(dxInitialize.rootSignature);
		
		//�v���~�e�B�u�`��̐ݒ�R�}���h
		dxInitialize.commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//�O�p�`���X�g

		//���_�o�b�t�@�r���[�̐ݒ�R�}���h
		dxInitialize.commandList->IASetVertexBuffers(0, 1, &dxInitialize.vbView);

		//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		dxInitialize.commandList->SetGraphicsRootConstantBufferView(0, dxInitialize.constBuffMaterial->GetGPUVirtualAddress());

		//SRV�q�[�v�̐ݒ�R�}���h
		dxInitialize.commandList->SetDescriptorHeaps(1, &dxInitialize.srvHeap);

		//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = dxInitialize.srvHeap->GetGPUDescriptorHandleForHeapStart();
		
		//SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
		dxInitialize.commandList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		dxInitialize.commandList->SetGraphicsRootConstantBufferView(2, dxInitialize.constBuffTransform->GetGPUVirtualAddress());

		//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
		dxInitialize.commandList->IASetIndexBuffer(&dxInitialize.ibView);

		//�`��R�}���h
		dxInitialize.commandList->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);	//�S�Ă̒��_���g���ĕ`��

		//--------------4.�`��R�}���h�@�����܂�---------------//
	#pragma endregion �`��R�}���h
		//5. ���\�[�X�o���A��߂�
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ���
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//�\����Ԃ�
		dxInitialize.commandList->ResourceBarrier(1, &barrierDesc);

		//���߂̃N���[�Y
		result = dxInitialize.commandList->Close();
		assert(SUCCEEDED(result));
		//�R�}���h���X�g�̎��s
		ID3D12CommandList* commandLists[] = { dxInitialize.commandList };
		dxInitialize.commandQueue->ExecuteCommandLists(1, commandLists);

		//��ʂɕ\������o�b�t�@���t���b�v(���\�̓���ւ�)
		result = dxInitialize.swapChain->Present(1, 0);
		assert(SUCCEEDED(result));

		//�R�}���h�̎��s������҂�
		dxInitialize.commandQueue->Signal(dxInitialize.fence, ++dxInitialize.fenceVal);
		if (dxInitialize.fence->GetCompletedValue() != dxInitialize.fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			dxInitialize.fence->SetEventOnCompletion(dxInitialize.fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//�L���[���N���A
		result = dxInitialize.commandAllocator->Reset();
		assert(SUCCEEDED(result));
		//�ĂуR�}���h���X�g�����߂鏀��
		result = dxInitialize.commandList->Reset(dxInitialize.commandAllocator, nullptr);
		assert(SUCCEEDED(result));


		//DirecX���t���[���@�����܂Ł@�@�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�[�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
		#pragma endregion	DirectX���t���[��
	}
	
	
	

	return 0;
}
