

#include"DXInitialize.h"
#include"Input.h"
#include"DXWindow.h"
#include"WorldTransform.h"
#include <DirectXTex.h>

#include"Vector3.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウ作成コンストラクタ
	DXWindow _window;
#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
	
#endif	
	HRESULT result;
	//DirectX初期化処理
	DXInitialize dxInitialize;
	dxInitialize.Initialize(_window.hwnd);
	//入力関数
	Input _input(_window.w, _window.hwnd);

	dxInitialize.DxDrawIni();



	//変数初期化場所
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
		//DirecX毎フレーム　ここから　　ー−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−ー−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
		
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

		//バックバッファの番号を取得(2つなので0番か1番)
		UINT bbIndex = dxInitialize.GetswapChain()->GetCurrentBackBufferIndex();

		//1.リソースバリアで書き込み可能に変更
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = dxInitialize.backBuffers[bbIndex];				//バックバッファを指定
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//表示状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//描画状態へ
		dxInitialize.GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//2. 描画先の変更
		//レンダーターゲットビューのハンドルを取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = dxInitialize.GetrtvHeap()->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * dxInitialize.Getdevice()->GetDescriptorHandleIncrementSize(dxInitialize.rtvHeapDesc.Type);
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dxInitialize.dsvHeap->GetCPUDescriptorHandleForHeapStart();
		dxInitialize.GetcommandList()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		//3. 画面クリア
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//色の指定はRGBAの0.0f〜1.0f
		
		dxInitialize.GetcommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		dxInitialize.GetcommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
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
		dxInitialize.GetcommandList()->RSSetViewports(1, &viewport);

		//シザー矩形
		D3D12_RECT scissorRect{};
		scissorRect.left = 0;										//切り抜き座標左
		scissorRect.right = scissorRect.left + window_width;		//切り抜き座標右
		scissorRect.top = 0;										//切り抜き座標上
		scissorRect.bottom = scissorRect.top + window_height;		//切り抜き座標下
		
		//シザー矩形設定コマンドを、コマンドリストに積む
		dxInitialize.GetcommandList()->RSSetScissorRects(1, &scissorRect);

		//パイプラインステートとルートシグネチャの設定コマンド
		dxInitialize.GetcommandList()->SetPipelineState(dxInitialize.pipelineState);
		dxInitialize.GetcommandList()->SetGraphicsRootSignature(dxInitialize.rootSignature);
		
		//プリミティブ形状の設定コマンド
		dxInitialize.GetcommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	//三角形リスト

		//頂点バッファビューの設定コマンド
		dxInitialize.GetcommandList()->IASetVertexBuffers(0, 1, &dxInitialize.vbView);

		//定数バッファビュー(CBV)の設定コマンド
		dxInitialize.GetcommandList()->SetGraphicsRootConstantBufferView(0, dxInitialize.constBuffMaterial->GetGPUVirtualAddress());

		//SRVヒープの設定コマンド
		dxInitialize.GetcommandList()->SetDescriptorHeaps(1, &dxInitialize.srvHeap);

		//SRVヒープの先頭ハンドルを取得(SRVを指しているはず)
		D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = dxInitialize.srvHeap->GetGPUDescriptorHandleForHeapStart();
		
		//SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
		dxInitialize.GetcommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);

		//定数バッファビュー(CBV)の設定コマンド
		dxInitialize.GetcommandList()->SetGraphicsRootConstantBufferView(2, box.constBuffTransform->GetGPUVirtualAddress());

		//インデックスバッファビューの設定コマンド
		dxInitialize.GetcommandList()->IASetIndexBuffer(&dxInitialize.ibView);

		//描画コマンド
		dxInitialize.GetcommandList()->DrawIndexedInstanced(_countof(indices), 1, 0, 0,0);	//全ての頂点を使って描画

		//--------------4.描画コマンド　ここまで---------------//
	#pragma endregion 描画コマンド
		//5. リソースバリアを戻す
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//描画状態から
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//表示状態へ
		dxInitialize.GetcommandList()->ResourceBarrier(1, &barrierDesc);

		//命令のクローズ
		result = dxInitialize.GetcommandList()->Close();
		assert(SUCCEEDED(result));
		//コマンドリストの実行
		ID3D12CommandList* commandLists[] = { dxInitialize.GetcommandList() };
		dxInitialize.GetcommandQueue()->ExecuteCommandLists(1, commandLists);

		//画面に表示するバッファをフリップ(裏表の入れ替え)
		result = dxInitialize.GetswapChain()->Present(1, 0);
		assert(SUCCEEDED(result));

		//コマンドの実行完了を待つ
		dxInitialize.GetcommandQueue()->Signal(dxInitialize.fence, ++dxInitialize.fenceVal);
		if (dxInitialize.fence->GetCompletedValue() != dxInitialize.fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			dxInitialize.fence->SetEventOnCompletion(dxInitialize.fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//キューをクリア
		result = dxInitialize.GetcommandAllocator()->Reset();
		assert(SUCCEEDED(result));
		//再びコマンドリストをためる準備
		result = dxInitialize.GetcommandList()->Reset(dxInitialize.GetcommandAllocator(), nullptr);
		assert(SUCCEEDED(result));


		//DirecX毎フレーム　ここまで　　ー−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−ー−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
		#pragma endregion	DirectX毎フレーム
	}
	
	
	

	return 0;
}
