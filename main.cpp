

#include"DXInitialize.h"
#include"Input.h"
#include"DXWindow.h"

#include <DirectXTex.h>



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
	DXInitialize dxInitialize(_window.hwnd);
	//ì¸óÕä÷êî
	Input _input(_window.w, _window.hwnd);

	dxInitialize.DxDrawIni();



	//ïœêîèâä˙âªèÍèä
	bool color_Red = false;
	bool color_Green =false;
	bool color_Blue = false;

	int color_lv = 0;

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


		//ÉoÉbÉNÉoÉbÉtÉ@ÇÃî‘çÜÇéÊìæ(2Ç¬Ç»ÇÃÇ≈0î‘Ç©1î‘)
		UINT bbIndex = dxInitialize.swapChain->GetCurrentBackBufferIndex();

		//1.ÉäÉ\Å[ÉXÉoÉäÉAÇ≈èëÇ´çûÇ›â¬î\Ç…ïœçX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = dxInitialize.backBuffers[bbIndex];				//ÉoÉbÉNÉoÉbÉtÉ@ÇéwíË
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//ï\é¶èÛë‘Ç©ÇÁ
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//ï`âÊèÛë‘Ç÷
		dxInitialize.commandList->ResourceBarrier(1, &barrierDesc);

		//2. ï`âÊêÊÇÃïœçX
		//ÉåÉìÉ_Å[É^Å[ÉQÉbÉgÉrÉÖÅ[ÇÃÉnÉìÉhÉãÇéÊìæ
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = dxInitialize.rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * dxInitialize.device->GetDescriptorHandleIncrementSize(dxInitialize.rtvHeapDesc.Type);
		dxInitialize.commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

		//3. âÊñ ÉNÉäÉA
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//êFÇÃéwíËÇÕRGBAÇÃ0.0fÅ`1.0f
		
		dxInitialize.commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
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
		dxInitialize.commandList->RSSetViewports(1, &viewport);

		//ÉVÉUÅ[ãÈå`
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//êÿÇËî≤Ç´ç¿ïWç∂
		scissorRect.right = scissorRect.left + window_width;		//êÿÇËî≤Ç´ç¿ïWâE
		scissorRect.top = 0;										//êÿÇËî≤Ç´ç¿ïWè„
		scissorRect.bottom = scissorRect.top + window_height;		//êÿÇËî≤Ç´ç¿ïWâ∫
		
		//ÉVÉUÅ[ãÈå`ê›íËÉRÉ}ÉìÉhÇÅAÉRÉ}ÉìÉhÉäÉXÉgÇ…êœÇﬁ
		dxInitialize.commandList->RSSetScissorRects(1, &scissorRect);

		//ÉpÉCÉvÉâÉCÉìÉXÉeÅ[ÉgÇ∆ÉãÅ[ÉgÉVÉOÉlÉ`ÉÉÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.commandList->SetPipelineState(dxInitialize.pipelineState);
		dxInitialize.commandList->SetGraphicsRootSignature(dxInitialize.rootSignature);
		
		//ÉvÉäÉ~ÉeÉBÉuå`èÛÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//éOäpå`ÉäÉXÉg

		//í∏ì_ÉoÉbÉtÉ@ÉrÉÖÅ[ÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.commandList->IASetVertexBuffers(0, 1, &dxInitialize.vbView);

		//íËêîÉoÉbÉtÉ@ÉrÉÖÅ[(CBV)ÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.commandList->SetGraphicsRootConstantBufferView(0, dxInitialize.constBuffMaterial->GetGPUVirtualAddress());

		//SRVÉqÅ[ÉvÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.commandList->SetDescriptorHeaps(1, &dxInitialize.srvHeap);

		//SRVÉqÅ[ÉvÇÃêÊì™ÉnÉìÉhÉãÇéÊìæ(SRVÇéwÇµÇƒÇ¢ÇÈÇÕÇ∏)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = dxInitialize.srvHeap->GetGPUDescriptorHandleForHeapStart();
		
		//SRVÉqÅ[ÉvÇÃêÊì™Ç…Ç†ÇÈSRVÇÉãÅ[ÉgÉpÉâÉÅÅ[É^1î‘Ç…ê›íË
		dxInitialize.commandList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		//ÉCÉìÉfÉbÉNÉXÉoÉbÉtÉ@ÉrÉÖÅ[ÇÃê›íËÉRÉ}ÉìÉh
		dxInitialize.commandList->IASetIndexBuffer(&dxInitialize.ibView);

		//ï`âÊÉRÉ}ÉìÉh
		dxInitialize.commandList->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);	//ëSÇƒÇÃí∏ì_ÇégÇ¡Çƒï`âÊ

		//--------------4.ï`âÊÉRÉ}ÉìÉhÅ@Ç±Ç±Ç‹Ç≈---------------//
	#pragma endregion ï`âÊÉRÉ}ÉìÉh
		//5. ÉäÉ\Å[ÉXÉoÉäÉAÇñﬂÇ∑
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//ï`âÊèÛë‘Ç©ÇÁ
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//ï\é¶èÛë‘Ç÷
		dxInitialize.commandList->ResourceBarrier(1, &barrierDesc);

		//ñΩóﬂÇÃÉNÉçÅ[ÉY
		result = dxInitialize.commandList->Close();
		assert(SUCCEEDED(result));
		//ÉRÉ}ÉìÉhÉäÉXÉgÇÃé¿çs
		ID3D12CommandList* commandLists[] = { dxInitialize.commandList };
		dxInitialize.commandQueue->ExecuteCommandLists(1, commandLists);

		//âÊñ Ç…ï\é¶Ç∑ÇÈÉoÉbÉtÉ@ÇÉtÉäÉbÉv(ó†ï\ÇÃì¸ÇÍë÷Ç¶)
		result = dxInitialize.swapChain->Present(1, 0);
		assert(SUCCEEDED(result));

		//ÉRÉ}ÉìÉhÇÃé¿çsäÆóπÇë“Ç¬
		dxInitialize.commandQueue->Signal(dxInitialize.fence, ++dxInitialize.fenceVal);
		if (dxInitialize.fence->GetCompletedValue() != dxInitialize.fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			dxInitialize.fence->SetEventOnCompletion(dxInitialize.fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//ÉLÉÖÅ[ÇÉNÉäÉA
		result = dxInitialize.commandAllocator->Reset();
		assert(SUCCEEDED(result));
		//çƒÇ—ÉRÉ}ÉìÉhÉäÉXÉgÇÇΩÇﬂÇÈèÄîı
		result = dxInitialize.commandList->Reset(dxInitialize.commandAllocator, nullptr);
		assert(SUCCEEDED(result));


		//DirecXñàÉtÉåÅ[ÉÄÅ@Ç±Ç±Ç‹Ç≈Å@Å@Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|
		#pragma endregion	DirectXñàÉtÉåÅ[ÉÄ
	}
	
	
	

	return 0;
}
