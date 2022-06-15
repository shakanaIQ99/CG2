

#include"DXInitialize.h"
#include"Input.h"
#include"DXWindow.h"
#include"WorldTransform.h"
#include <DirectXTex.h>

#include"Vector3.h"

//WindowsÉAÉvÉäÇ≈ÇÃÉGÉìÉgÉäÅ[É|ÉCÉìÉg(mainä÷êî)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ÉEÉBÉìÉhÉEçÏê¨ÉRÉìÉXÉgÉâÉNÉ^
	DXWindow _window;
#ifdef _DEBUG
	//ÉfÉoÉbÉOÉåÉCÉÑÅ[ÇÉIÉìÇ…
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
	
#endif	
	HRESULT result;
	//DirectXèâä˙âªèàóù
	DXInitialize dxInitialize;
	dxInitialize.Initialize(_window.hwnd);
	//ì¸óÕä÷êî
	Input _input(_window.w, _window.hwnd);

	dxInitialize.DxDrawIni();



	//ïœêîèâä˙âªèÍèä
	bool color_Red = false;
	bool color_Green =false;
	bool color_Blue = false;

	int color_lv = 0;

	float CC = 0.02f;

	float angle = 0.0f;

	WorldTransform box;

	box.Initialize();

	Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(1, 1, 1);
	Vector3 rotation = Vector3(0, 0, 0);

	Matrix4 matWorld;
	Matrix4 matScale;
	Matrix4 matRot;
	Matrix4 matTrans;

	//ÉQÅ[ÉÄÉãÅ[Év
	while (true)
	{
		//ÉÅÉbÉZÅ[ÉWÇ†ÇÈÅH
		if (PeekMessage(&_window.msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_window.msg);	//ÉLÅ[ì¸óÕÉÅÉbÉZÅ[ÉWÇÃèàóù
			DispatchMessage(&_window.msg);	//ÉvÉçÉVÅ[ÉWÉÉÇ…ÉÅÉbÉZÅ[ÉWÇëóÇÈ
		}

		//Å~É{É^ÉìÇ≈èIóπÉÅÉbÉZÅ[ÉWÇ™óàÇΩÇÁÉQÅ[ÉÄÉãÅ[ÉvÇî≤ÇØÇÈ
		if (_window.msg.message == WM_QUIT)
		{
			break;
		}
		#pragma region DirectXñàÉtÉåÅ[ÉÄ
		//DirecXñàÉtÉåÅ[ÉÄÅ@Ç±Ç±Ç©ÇÁÅ@Å@Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|
		
		//ÉLÅ[É{Å[ÉhèÓïÒÇÃéÊìæäJén
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

		
		if (_input.GetKey(DIK_UP)) { position.z += 1.0f; }
		if (_input.GetKey(DIK_DOWN)) { position.z -= 1.0f; }
		if (_input.GetKey(DIK_RIGHT)) { position.x += 1.0f; }
		if (_input.GetKey(DIK_LEFT)) { position.x -= 1.0f; }
		if (_input.GetKey(DIK_Z)) {  }
		if (_input.GetKey(DIK_X)) { rotation.x += 1.0f; }
		if (_input.GetKey(DIK_Y)) { rotation.y += 1.0f; }
		if (!_input.GetKey(DIK_SPACE))
		{
			if (color_Red)
			{
				dxInitialize.constMapMaterial->color.x += CC;
				dxInitialize.constMapMaterial->color.z -= CC;
				if (dxInitialize.constMapMaterial->color.x > 1.0f)
				{
					color_lv = 1;
				}
			}
			if (color_Green)
			{
				dxInitialize.constMapMaterial->color.y += CC;
				dxInitialize.constMapMaterial->color.x -= CC;
				if (dxInitialize.constMapMaterial->color.y > 1.0f)
				{
					color_lv = 2;
				}
			}
			if (color_Blue)
			{
				dxInitialize.constMapMaterial->color.z += CC;
				dxInitialize.constMapMaterial->color.y -= CC;
				if (dxInitialize.constMapMaterial->color.z > 1.0f)
				{
					color_lv = 0;
				}
			}
			rotation.z += 4.0f;
			
			
		}

		
		
		


		if (_input.GetKey(DIK_D) || _input.GetKey(DIK_A))
		{
			if (_input.GetKey(DIK_D)) { angle += XMConvertToRadians(1.0f); }
			if (_input.GetKey(DIK_A)) { angle -= XMConvertToRadians(1.0f); }

			dxInitialize.eye.x = -50 * sinf(angle);
			dxInitialize.eye.z = -50 * cosf(angle);
			dxInitialize.matview = XMMatrixLookAtLH(XMLoadFloat3(&dxInitialize.eye), XMLoadFloat3(&dxInitialize.target), XMLoadFloat3(&dxInitialize.up));

		}
		box.UpdateMatrix();

		//ÉoÉbÉNÉoÉbÉtÉ@ÇÃî‘çÜÇéÊìæ(2Ç¬Ç»ÇÃÇ≈0î‘Ç©1î‘)
		UINT bbIndex = dxInitialize.GetswapChain()->GetCurrentBackBufferIndex();

		//1.ÉäÉ\Å[ÉXÉoÉäÉAÇ≈èëÇ´çûÇ›â¬î\Ç…ïœçX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = dxInitialize.backBuffers[bbIndex];				//ÉoÉbÉNÉoÉbÉtÉ@ÇéwíË
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//ï\é¶èÛë‘Ç©ÇÁ
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//ï`âÊèÛë‘Ç÷
		dxInitialize.GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//2. ï`âÊêÊÇÃïœçX
		//ÉåÉìÉ_Å[É^Å[ÉQÉbÉgÉrÉÖÅ[ÇÃÉnÉìÉhÉãÇéÊìæ
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = dxInitialize.GetrtvHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * dxInitialize.Getdevice()->GetDescriptorHandleIncrementSize(dxInitialize.rtvHeapDesc.Type);
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dxInitialize.dsvHeap->GetCPUDescriptorHandleForHeapStart();
		dxInitialize.GetcommandList()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		//3. âÊñ ÉNÉäÉA
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//êFÇÃéwíËÇÕRGBAÇÃ0.0fÅ`1.0f
		
		dxInitialize.GetcommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		dxInitialize.GetcommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	#pragma region ï`âÊÉRÉ}ÉìÉh
		//--------------4.ï`âÊÉRÉ}ÉìÉhÅ@Ç±Ç±Ç©ÇÁ---------------//
		
		 //ÉrÉÖÅ[É|Å[Égê›íËÉRÉ}ÉìÉh
		D3D12_VIEWPORT viewport{};
		viewport.Width = window_width;
		viewport.Height = window_height;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		//ÉrÉÖÅ[É|Å[Égê›íËÉRÉ}ÉìÉhÇÅAÉRÉ}ÉìÉhÉäÉXÉgÇ…êœÇﬁ
		dxInitialize.GetcommandList()->RSSetViewports(1, &viewport);

		//ÉVÉUÅ[ãÈå`
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//êÿÇËî≤Ç´ç¿ïWç∂
		scissorRect.right = scissorRect.left + window_width;		//êÿÇËî≤Ç´ç¿ïWâE
		scissorRect.top = 0;										//êÿÇËî≤Ç´ç¿ïWè„
		scissorRect.bottom = scissorRect.top + window_height;		//êÿÇËî≤Ç´ç¿ïWâ∫
		
		//ÉVÉUÅ[ãÈå`ê›íËÉRÉ}ÉìÉhÇÅAÉRÉ}ÉìÉhÉäÉXÉgÇ…êœÇﬁ
		dxInitialize.GetcommandList()->RSSetScissorRects(1, &scissorRect);

		//ÉpÉCÉvÉâÉCÉìÉXÉeÅ[ÉgÇ∆ÉãÅ[ÉgÉVÉOÉlÉ`ÉÉÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->SetPipelineState(dxInitialize.pipelineState);
		dxInitialize.GetcommandList()->SetGraphicsRootSignature(dxInitialize.rootSignature);
		
		//ÉvÉäÉ~ÉeÉBÉuå`èÛÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//éOäpå`ÉäÉXÉg

		//í∏ì_ÉoÉbÉtÉ@ÉrÉÖÅ[ÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->IASetVertexBuffers(0, 1, &dxInitialize.vbView);

		//íËêîÉoÉbÉtÉ@ÉrÉÖÅ[(CBV)ÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->SetGraphicsRootConstantBufferView(0, dxInitialize.constBuffMaterial->GetGPUVirtualAddress());

		//SRVÉqÅ[ÉvÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->SetDescriptorHeaps(1, &dxInitialize.srvHeap);

		//SRVÉqÅ[ÉvÇÃêÊì™ÉnÉìÉhÉãÇéÊìæ(SRVÇéwÇµÇƒÇ¢ÇÈÇÕÇ∏)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = dxInitialize.srvHeap->GetGPUDescriptorHandleForHeapStart();
		
		//SRVÉqÅ[ÉvÇÃêÊì™Ç…Ç†ÇÈSRVÇÉãÅ[ÉgÉpÉâÉÅÅ[É^1î‘Ç…ê›íË
		dxInitialize.GetcommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		//íËêîÉoÉbÉtÉ@ÉrÉÖÅ[(CBV)ÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->SetGraphicsRootConstantBufferView(2, box.constBuffTransform->GetGPUVirtualAddress());

		//ÉCÉìÉfÉbÉNÉXÉoÉbÉtÉ@ÉrÉÖÅ[ÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->IASetIndexBuffer(&dxInitialize.ibView);

		//ï`âÊÉRÉ}ÉìÉh
		dxInitialize.GetcommandList()->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);	//ëSÇƒÇÃí∏ì_ÇégÇ¡Çƒï`âÊ

		//--------------4.ï`âÊÉRÉ}ÉìÉhÅ@Ç±Ç±Ç‹Ç≈---------------//
	#pragma endregion ï`âÊÉRÉ}ÉìÉh
		//5. ÉäÉ\Å[ÉXÉoÉäÉAÇñﬂÇ∑
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//ï`âÊèÛë‘Ç©ÇÁ
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//ï\é¶èÛë‘Ç÷
		dxInitialize.GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//ñΩóﬂÇÃÉNÉçÅ[ÉY
		result = dxInitialize.GetcommandList()->Close();
		assert(SUCCEEDED(result));
		//ÉRÉ}ÉìÉhÉäÉXÉgÇÃé¿çs
		ID3D12CommandList* commandLists[] = { dxInitialize.GetcommandList() };
		dxInitialize.GetcommandQueue()->ExecuteCommandLists(1, commandLists);

		//âÊñ Ç…ï\é¶Ç∑ÇÈÉoÉbÉtÉ@ÇÉtÉäÉbÉv(ó†ï\ÇÃì¸ÇÍë÷Ç¶)
		result = dxInitialize.GetswapChain()->Present(1, 0);
		assert(SUCCEEDED(result));

		//ÉRÉ}ÉìÉhÇÃé¿çsäÆóπÇë“Ç¬
		dxInitialize.GetcommandQueue()->Signal(dxInitialize.fence, ++dxInitialize.fenceVal);
		if (dxInitialize.fence->GetCompletedValue() != dxInitialize.fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			dxInitialize.fence->SetEventOnCompletion(dxInitialize.fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//ÉLÉÖÅ[ÇÉNÉäÉA
		result = dxInitialize.GetcommandAllocator()->Reset();
		assert(SUCCEEDED(result));
		//çƒÇ—ÉRÉ}ÉìÉhÉäÉXÉgÇÇΩÇﬂÇÈèÄîı
		result = dxInitialize.GetcommandList()->Reset(dxInitialize.GetcommandAllocator(), nullptr);
		assert(SUCCEEDED(result));


		//DirecXñàÉtÉåÅ[ÉÄÅ@Ç±Ç±Ç‹Ç≈Å@Å@Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|
		#pragma endregion	DirectXñàÉtÉåÅ[ÉÄ
	}
	
	
	

	return 0;
}
