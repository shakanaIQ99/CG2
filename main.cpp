
#include"DXInitialize.h"
#include"Texture.h"
#include"Input.h"
#include"DXWindow.h"
//#include"WorldTransform.h"
#include <DirectXTex.h>

#include"Vector3.h"

void ConvertCont(int num);

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウ作成コンストラクタ
	DXWindow _window;
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr<ID3D12Debug1> debugController;
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}

	
	
#endif	
	HRESULT result;
	//DirectX初期化処理
	DXInitialize::GetInstance()->Initialize(_window.hwnd);

	
	//入力関数
	Input _input(_window.w, _window.hwnd);

	DXInitialize::GetInstance()->DxDrawIni();
//#ifdef _DEBUG
//	//デバッグレイヤーをオンに
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


	//変数初期化場所

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

	//ゲームループ
	while (true)
	{
		//メッセージある？
		if (PeekMessage(&_window.msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_window.msg);	//キー入力メッセージの処理
			DispatchMessage(&_window.msg);	//プロシージャにメッセージを送る
		}

		//×ボタンで終了メッセージが来たらゲームループを抜ける
		if (_window.msg.message == WM_QUIT)
		{
			break;
		}
		#pragma region DirectX毎フレーム
		//DirecX毎フレーム　ここから　　ー－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－ー－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
		
		//キーボード情報の取得開始
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

		//バックバッファの番号を取得(2つなので0番か1番)
		UINT bbIndex = DXInitialize::GetInstance()->GetswapChain()->GetCurrentBackBufferIndex();

		//1.リソースバリアで書き込み可能に変更
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = DXInitialize::GetInstance()->backBuffers[bbIndex].Get();				//バックバッファを指定
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//表示状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//描画状態へ
		DXInitialize::GetInstance()->GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//2. 描画先の変更
		//レンダーターゲットビューのハンドルを取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = DXInitialize::GetInstance()->GetrtvHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * DXInitialize::GetInstance()->Getdevice()->GetDescriptorHandleIncrementSize(DXInitialize::GetInstance()->GetrtvHeapDesc().Type);
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DXInitialize::GetInstance()->GetdsvHeap()->GetCPUDescriptorHandleForHeapStart();
		DXInitialize::GetInstance()->GetcommandList()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		//3. 画面クリア
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//色の指定はRGBAの0.0f～1.0f
		
		DXInitialize::GetInstance()->GetcommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		DXInitialize::GetInstance()->GetcommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	#pragma region 描画コマンド
		//--------------4.描画コマンド　ここから---------------//
		
		 //ビューポート設定コマンド
		D3D12_VIEWPORT viewport{};
		viewport.Width = window_width;
		viewport.Height = window_height;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		//ビューポート設定コマンドを、コマンドリストに積む
		DXInitialize::GetInstance()->GetcommandList()->RSSetViewports(1, &viewport);

		//シザー矩形
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//切り抜き座標左
		scissorRect.right = scissorRect.left + window_width;		//切り抜き座標右
		scissorRect.top = 0;										//切り抜き座標上
		scissorRect.bottom = scissorRect.top + window_height;		//切り抜き座標下
		
		//シザー矩形設定コマンドを、コマンドリストに積む
		DXInitialize::GetInstance()->GetcommandList()->RSSetScissorRects(1, &scissorRect);

		//パイプラインステートとルートシグネチャの設定コマンド
		DXInitialize::GetInstance()->GetcommandList()->SetPipelineState(DXInitialize::GetInstance()->GetpipelineState().Get());
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootSignature(DXInitialize::GetInstance()->GetrootSignature().Get());
		
		//プリミティブ形状の設定コマンド
		DXInitialize::GetInstance()->GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//三角形リスト

		//頂点バッファビューの設定コマンド
		//dxInitialize.GetcommandList()->IASetVertexBuffers(0, 1, &dxInitialize.vbView);

		//定数バッファビュー(CBV)の設定コマンド
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootConstantBufferView(0, DXInitialize::GetInstance()->GetconstBuffMaterial()->GetGPUVirtualAddress());

		//SRVヒープの設定コマンド
		DXInitialize::GetInstance()->GetcommandList()->SetDescriptorHeaps(1, Texture::GetInstance()->srvHeap.GetAddressOf());

		//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = Texture::GetInstance()->srvHeap->GetGPUDescriptorHandleForHeapStart();
		
		srvGpuHandle.ptr += Texture::GetInstance()->incrementSize;

		//SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
		DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		////定数バッファビュー(CBV)の設定コマンド
		//dxInitialize.GetcommandList()->SetGraphicsRootConstantBufferView(2,dxInitialize.obj->constBuffTransform->GetGPUVirtualAddress());

		//インデックスバッファビューの設定コマンド
		//dxInitialize.GetcommandList()->IASetIndexBuffer(&dxInitialize.ibView);

		////描画コマンド
		//dxInitialize.GetcommandList()->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);	//全ての頂点を使って描画
		DXInitialize::GetInstance()->obj[1].DrawOBJ(3);
		DXInitialize::GetInstance()->obj[0].DrawOBJ(_countof(indices));
		/*for (int i = 0; i < _countof(DXInitialize::GetInstance()->obj); i++)
		{
			DXInitialize::GetInstance()->obj[i].DrawOBJ(_countof(indices));
		}*/

		//--------------4.描画コマンド　ここまで---------------//
	#pragma endregion 描画コマンド
		//5. リソースバリアを戻す
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//描画状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//表示状態へ
		DXInitialize::GetInstance()->GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//命令のクローズ
		result = DXInitialize::GetInstance()->GetcommandList()->Close();
		assert(SUCCEEDED(result));
		//コマンドリストの実行
		ID3D12CommandList* commandLists[] = { DXInitialize::GetInstance()->GetcommandList().Get()};
		DXInitialize::GetInstance()->GetcommandQueue()->ExecuteCommandLists(1, commandLists);

		//画面に表示するバッファをフリップ(裏表の入れ替え)
		result = DXInitialize::GetInstance()->GetswapChain()->Present(1, 0);
		assert(SUCCEEDED(result));

		//コマンドの実行完了を待つ
		DXInitialize::GetInstance()->GetcommandQueue()->Signal(DXInitialize::GetInstance()->Getfence().Get(), ++DXInitialize::GetInstance()->fenceVal);
		if (DXInitialize::GetInstance()->Getfence()->GetCompletedValue() != DXInitialize::GetInstance()->fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			DXInitialize::GetInstance()->Getfence()->SetEventOnCompletion(DXInitialize::GetInstance()->fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//キューをクリア
		result = DXInitialize::GetInstance()->GetcommandAllocator()->Reset();
		assert(SUCCEEDED(result));
		//再びコマンドリストをためる準備
		result = DXInitialize::GetInstance()->GetcommandList()->Reset(DXInitialize::GetInstance()->GetcommandAllocator().Get(), nullptr);
		assert(SUCCEEDED(result));


		//DirecX毎フレーム　ここまで　　ー－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－ー－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
		#pragma endregion	DirectX毎フレーム
	}
	
	
	

	return 0;
}
