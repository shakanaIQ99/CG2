
#include"DXInitialize.h"
#include"Texture.h"
#include"Input.h"
#include"DXWindow.h"
//#include"WorldTransform.h"
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
	DXInitialize::GetInstance()->Initialize(_window.hwnd);
	
	//ì¸óÕä÷êî
	Input _input(_window.w, _window.hwnd);

	DXInitialize::GetInstance()->DxDrawIni();



	//ïœêîèâä˙âªèÍèä

	Texture::GetInstance()->Initialize(L"Resources/genba.jpg");

	bool color_Red = false;
	bool color_Green =false;
	bool color_Blue = false;

	int color_lv = 0;

	float CC = 0.02f;

	float angle = 0.0f;

	//WorldTransform box;

	//box.Initialize();

	//box.scale = { 1,1,1 };

	XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
	Vector3 scale = Vector3(1, 1, 1);
	Vector3 rotation = Vector3(0, 0, 0);

	XMMATRIX matTrans;

	/*Matrix4 matWorld;
	Matrix4 matScale;
	Matrix4 matRot;
	Matrix4 matTrans;*/

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

		//box.scale = { 1,1,1 };
		if (_input.GetKey(DIK_Z)) {  }
		if (_input.GetKey(DIK_X)) { rotation.x += 1.0f; }
		if (_input.GetKey(DIK_Y)) { rotation.y += 1.0f; }
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

		
		
		if (_input.GetKey(DIK_UP)) { DXInitialize::GetInstance()->obj[0].translation.y += 1.0f; }
		if (_input.GetKey(DIK_DOWN)) { DXInitialize::GetInstance()->obj[0].translation.y -= 1.0f; }
		if (_input.GetKey(DIK_RIGHT)) { DXInitialize::GetInstance()->obj[0].translation.x += 1.0f; }
		if (_input.GetKey(DIK_LEFT)) { DXInitialize::GetInstance()->obj[0].translation.x -= 1.0f; }


		if (_input.GetKey(DIK_D) || _input.GetKey(DIK_A))
		{
			if (_input.GetKey(DIK_D)) { angle += XMConvertToRadians(1.0f); }
			if (_input.GetKey(DIK_A)) { angle -= XMConvertToRadians(1.0f); }

			DXInitialize::GetInstance()->eye.x = -50 * sinf(angle);
			DXInitialize::GetInstance()->eye.z = -50 * cosf(angle);
			DXInitialize::GetInstance()->matview = XMMatrixLookAtLH(XMLoadFloat3(&DXInitialize::GetInstance()->eye), XMLoadFloat3(&DXInitialize::GetInstance()->target), XMLoadFloat3(&DXInitialize::GetInstance()->up));

		}

		
		DXInitialize::GetInstance()->obj[0].UpdateMatrix(DXInitialize::GetInstance()->matview, DXInitialize::GetInstance()->matProjection);
		/*for (size_t i = 0; i < _countof(DXInitialize::GetInstance()->obj); i++)
		{
			DXInitialize::GetInstance()->obj[i].UpdateMatrix(DXInitialize::GetInstance()->matview , DXInitialize::GetInstance()->matProjection);
		}*/

		//ÉoÉbÉNÉoÉbÉtÉ@ÇÃî‘çÜÇéÊìæ(2Ç¬Ç»ÇÃÇ≈0î‘Ç©1î‘)
		UINT bbIndex = DXInitialize::GetInstance()->GetswapChain()->GetCurrentBackBufferIndex();

		//1.ÉäÉ\Å[ÉXÉoÉäÉAÇ≈èëÇ´çûÇ›â¬î\Ç…ïœçX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = DXInitialize::GetInstance()->backBuffers[bbIndex];				//ÉoÉbÉNÉoÉbÉtÉ@ÇéwíË
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//ï\é¶èÛë‘Ç©ÇÁ
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//ï`âÊèÛë‘Ç÷
		DXInitialize::GetInstance()->GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//2. ï`âÊêÊÇÃïœçX
		//ÉåÉìÉ_Å[É^Å[ÉQÉbÉgÉrÉÖÅ[ÇÃÉnÉìÉhÉãÇéÊìæ
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = DXInitialize::GetInstance()->GetrtvHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * DXInitialize::GetInstance()->Getdevice()->GetDescriptorHandleIncrementSize(DXInitialize::GetInstance()->GetrtvHeapDesc().Type);
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DXInitialize::GetInstance()->GetdsvHeap()->GetCPUDescriptorHandleForHeapStart();
		DXInitialize::GetInstance()->GetcommandList()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		//3. âÊñ ÉNÉäÉA
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//êFÇÃéwíËÇÕRGBAÇÃ0.0fÅ`1.0f
		
		DXInitialize::GetInstance()->GetcommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		DXInitialize::GetInstance()->GetcommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
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
		DXInitialize::GetInstance()->GetcommandList()->RSSetViewports(1, &viewport);

		//ÉVÉUÅ[ãÈå`
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//êÿÇËî≤Ç´ç¿ïWç∂
		scissorRect.right = scissorRect.left + window_width;		//êÿÇËî≤Ç´ç¿ïWâE
		scissorRect.top = 0;										//êÿÇËî≤Ç´ç¿ïWè„
		scissorRect.bottom = scissorRect.top + window_height;		//êÿÇËî≤Ç´ç¿ïWâ∫
		
		//ÉVÉUÅ[ãÈå`ê›íËÉRÉ}ÉìÉhÇÅAÉRÉ}ÉìÉhÉäÉXÉgÇ…êœÇﬁ
		DXInitialize::GetInstance()->GetcommandList()->RSSetScissorRects(1, &scissorRect);

		//ÉpÉCÉvÉâÉCÉìÉXÉeÅ[ÉgÇ∆ÉãÅ[ÉgÉVÉOÉlÉ`ÉÉÇÃê›íËÉRÉ}ÉìÉh
		DXInitialize::GetInstance()->GetcommandList()->SetPipelineState(DXInitialize::GetInstance()->GetpipelineState());
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootSignature(DXInitialize::GetInstance()->GetrootSignature());
		
		//ÉvÉäÉ~ÉeÉBÉuå`èÛÇÃê›íËÉRÉ}ÉìÉh
		DXInitialize::GetInstance()->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//éOäpå`ÉäÉXÉg

		//í∏ì_ÉoÉbÉtÉ@ÉrÉÖÅ[ÇÃê›íËÉRÉ}ÉìÉh
		//dxInitialize.GetcommandList()->IASetVertexBuffers(0, 1, &dxInitialize.vbView);

		//íËêîÉoÉbÉtÉ@ÉrÉÖÅ[(CBV)ÇÃê›íËÉRÉ}ÉìÉh
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootConstantBufferView(0, DXInitialize::GetInstance()->GetconstBuffMaterial()->GetGPUVirtualAddress());

		//SRVÉqÅ[ÉvÇÃê›íËÉRÉ}ÉìÉh
		DXInitialize::GetInstance()->GetcommandList()->SetDescriptorHeaps(1, &Texture::GetInstance()->srvHeap);

		//SRVÉqÅ[ÉvÇÃêÊì™ÉnÉìÉhÉãÇéÊìæ(SRVÇéwÇµÇƒÇ¢ÇÈÇÕÇ∏)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = Texture::GetInstance()->srvHeap->GetGPUDescriptorHandleForHeapStart();
		
		srvGpuHandle.ptr += Texture::GetInstance()->incrementSize;

		//SRVÉqÅ[ÉvÇÃêÊì™Ç…Ç†ÇÈSRVÇÉãÅ[ÉgÉpÉâÉÅÅ[É^1î‘Ç…ê›íË
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		////íËêîÉoÉbÉtÉ@ÉrÉÖÅ[(CBV)ÇÃê›íËÉRÉ}ÉìÉh
		//dxInitialize.GetcommandList()->SetGraphicsRootConstantBufferView(2,dxInitialize.obj->constBuffTransform->GetGPUVirtualAddress());

		//ÉCÉìÉfÉbÉNÉXÉoÉbÉtÉ@ÉrÉÖÅ[ÇÃê›íËÉRÉ}ÉìÉh
		//dxInitialize.GetcommandList()->IASetIndexBuffer(&dxInitialize.ibView);

		////ï`âÊÉRÉ}ÉìÉh
		//dxInitialize.GetcommandList()->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);	//ëSÇƒÇÃí∏ì_ÇégÇ¡Çƒï`âÊ

		DXInitialize::GetInstance()->obj[0].DrawOBJ(_countof(indices));
		/*for (int i = 0; i < _countof(DXInitialize::GetInstance()->obj); i++)
		{
			DXInitialize::GetInstance()->obj[i].DrawOBJ(_countof(indices));
		}*/

		//--------------4.ï`âÊÉRÉ}ÉìÉhÅ@Ç±Ç±Ç‹Ç≈---------------//
	#pragma endregion ï`âÊÉRÉ}ÉìÉh
		//5. ÉäÉ\Å[ÉXÉoÉäÉAÇñﬂÇ∑
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//ï`âÊèÛë‘Ç©ÇÁ
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//ï\é¶èÛë‘Ç÷
		DXInitialize::GetInstance()->GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//ñΩóﬂÇÃÉNÉçÅ[ÉY
		result = DXInitialize::GetInstance()->GetcommandList()->Close();
		assert(SUCCEEDED(result));
		//ÉRÉ}ÉìÉhÉäÉXÉgÇÃé¿çs
		ID3D12CommandList* commandLists[] = { DXInitialize::GetInstance()->GetcommandList() };
		DXInitialize::GetInstance()->GetcommandQueue()->ExecuteCommandLists(1, commandLists);

		//âÊñ Ç…ï\é¶Ç∑ÇÈÉoÉbÉtÉ@ÇÉtÉäÉbÉv(ó†ï\ÇÃì¸ÇÍë÷Ç¶)
		result = DXInitialize::GetInstance()->GetswapChain()->Present(1, 0);
		assert(SUCCEEDED(result));

		//ÉRÉ}ÉìÉhÇÃé¿çsäÆóπÇë“Ç¬
		DXInitialize::GetInstance()->GetcommandQueue()->Signal(DXInitialize::GetInstance()->Getfence(), ++DXInitialize::GetInstance()->fenceVal);
		if (DXInitialize::GetInstance()->Getfence()->GetCompletedValue() != DXInitialize::GetInstance()->fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			DXInitialize::GetInstance()->Getfence()->SetEventOnCompletion(DXInitialize::GetInstance()->fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//ÉLÉÖÅ[ÇÉNÉäÉA
		result = DXInitialize::GetInstance()->GetcommandAllocator()->Reset();
		assert(SUCCEEDED(result));
		//çƒÇ—ÉRÉ}ÉìÉhÉäÉXÉgÇÇΩÇﬂÇÈèÄîı
		result = DXInitialize::GetInstance()->GetcommandList()->Reset(DXInitialize::GetInstance()->GetcommandAllocator(), nullptr);
		assert(SUCCEEDED(result));


		//DirecXñàÉtÉåÅ[ÉÄÅ@Ç±Ç±Ç‹Ç≈Å@Å@Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å[Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|Å|
		#pragma endregion	DirectXñàÉtÉåÅ[ÉÄ
	}
	
	
	

	return 0;
}
