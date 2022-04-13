#include <Windows.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<cassert>
#include<vector>
#include<string>


#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//ƒƒbƒZ[ƒW‚É‰‚¶‚ÄƒQ[ƒ€‚ÌŒÅ—L‚Ìˆ—‚ğs‚¤
	switch (msg)
	{
	case WM_DESTROY:
		//OS‚É‘Î‚µ‚ÄAƒAƒvƒŠ‚ÌI—¹‚ğ“`‚¦‚é
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}



//WindowsƒAƒvƒŠ‚Å‚ÌƒGƒ“ƒgƒŠ[ƒ|ƒCƒ“ƒg(mainŠÖ”)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ƒRƒ“ƒ\[ƒ‹‚Ö‚Ì•¶šo—Í
	//OutputDebugStringA("Heloo,DirectX!!\n");
	
	const int window_width = 1280;	//‰¡•
	const int window_height = 720;	//c•

	//ƒEƒBƒ“ƒhƒEƒNƒ‰ƒX‚Ìİ’è
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);			
	w.lpfnWndProc = (WNDPROC)WindowProc;	//ƒEƒBƒ“ƒhƒEƒvƒƒV[ƒWƒƒ‚ğİ’è
	w.lpszClassName = L"DirecXGame";		//ƒEƒBƒ“ƒhƒEƒNƒ‰ƒX–¼
	w.hInstance = GetModuleHandle(nullptr);	//ƒEƒBƒ“ƒhƒEƒnƒ“ƒhƒ‹
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//ƒJ[ƒ\ƒ‹w’è

	//ƒEƒBƒ“ƒhƒEƒNƒ‰ƒX‚ğOS‚É“o˜^‚·‚é
	RegisterClassEx(&w);
	//ƒEƒBƒ“ƒhƒEƒTƒCƒY{@XÀ•W@YÀ•W@‰¡•@c•@}
	RECT wrc = { 0,0,window_width, window_height };
	//©“®‚ÅƒTƒCƒY‚ğ•â³‚·‚é
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd = CreateWindow
	(
		w.lpszClassName,		//ƒNƒ‰ƒX–¼
		L"DirectXGame",			//ƒ^ƒCƒgƒ‹ƒo[‚Ì•¶š
		WS_OVERLAPPEDWINDOW,	//•W€“I‚ÈƒEƒBƒ“ƒhƒEƒXƒ^ƒCƒ‹
		CW_USEDEFAULT,			//•\¦XÀ•W(OS‚É”C‚¹‚é)
		CW_USEDEFAULT,			//•\¦YÀ•W(OS‚É”C‚¹‚é)
		wrc.right - wrc.left,	//ƒEƒBƒ“ƒhƒE‰¡•
		wrc.bottom - wrc.top,	//ƒEƒBƒ“ƒhƒEc•
		nullptr,				//eƒEƒBƒ“ƒhƒEƒnƒ“ƒhƒ‹
		nullptr,				//ƒƒjƒ…[ƒnƒ“ƒhƒ‹
		w.hInstance,			//ŒÄ‚Ño‚µƒAƒvƒŠƒP[ƒVƒ‡ƒ“ƒnƒ“ƒhƒ‹
		nullptr					//ƒIƒvƒVƒ‡ƒ“
	);

	//ƒEƒBƒ“ƒhƒE‚ğ•\¦ó‘Ô‚·‚é
	ShowWindow(hwnd, SW_SHOW);

	MSG msg{};		//ƒƒbƒZ[ƒW

	//DirectX‰Šú‰»ˆ—@‚±‚±‚©‚ç@@[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
#ifdef _DEBUG
	//ƒfƒoƒbƒOƒŒƒCƒ„[‚ğƒIƒ“‚É
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
	
	
#endif
	
	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* commandAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;

	//DXGIƒtƒ@ƒNƒgƒŠ[‚Ì¶¬
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	//ƒAƒ_ƒvƒ^[‚Ì—ñ‹“—p
	std::vector <IDXGIAdapter4*>adapters;
	//‚±‚±‚É“Á’è‚Ì–¼‘O‚ğ‚ÂƒAƒ_ƒvƒ^[ƒIƒuƒWƒFƒNƒg‚ª“ü‚é
	IDXGIAdapter4* tmpAdapter = nullptr;

	//ƒpf|ƒ}ƒ“ƒX‚ª‚‚¢‚à‚Ì‚©‚ç‡‚ÉA‘S‚Ä‚ÌƒAƒ_ƒvƒ^[‚ğ—ñ‹“‚·‚é
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++)
	{
		//“®“I‚É”z—ñ‚ğ’Ç‰Á‚·‚é
		adapters.push_back(tmpAdapter);
	}
	for (size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3 adapterDesc;
		//ƒAƒ_ƒvƒ^[‚Ìî•ñ‚ğæ“¾‚·‚é
		adapters[i]->GetDesc3(&adapterDesc);

		//ƒ\ƒtƒgƒEƒFƒAƒfƒoƒCƒX‚ğ‰ñ”ğ
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
		{
			//ƒfƒoƒCƒX‚ğÌ—p‚µ‚Äƒ‹[ƒv‚ğ”²‚¯‚é
			tmpAdapter = adapters[i];
			break;
		}
	}

	//‘Î‰ƒŒƒxƒ‹‚Ì”z—ñ
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++)
	{
		//Ì—p‚µ‚½ƒAƒ_ƒvƒ^[‚ÅƒfƒoƒCƒX‚ğ¶¬
		result = D3D12CreateDevice(tmpAdapter, levels[i], IID_PPV_ARGS(&device));
		if (result == S_OK)
		{
			featureLevel = levels[i];
			break;
		}
	}

	//ƒRƒ}ƒ“ƒhƒAƒƒP[ƒ^[‚ğ¶¬
	result = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(result));
	
	//ƒRƒ}ƒ“ƒhƒŠƒXƒg‚ğ¶¬
	result = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, nullptr, IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(result));

	//ƒRƒ}ƒ“ƒhƒLƒ…[‚Ìİ’è
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//ƒRƒ}ƒ“ƒhƒLƒ…[‚ğ¶¬
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));

	//ƒXƒƒbƒvƒ`ƒF[ƒ“‚Ìİ’è
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;				//Fî•ñ‚Ì‘®
	swapChainDesc.SampleDesc.Count = 1;								//ƒ}ƒ‹ƒ`ƒTƒ“ƒvƒ‹‚ğ‚µ‚È‚¢
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;				//ƒoƒbƒNƒoƒbƒtƒ@—p
	swapChainDesc.BufferCount = 2;									//ƒoƒbƒtƒ@”‚ğ2‚Â‚Éİ’è
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;		//ƒtƒŠƒbƒvŒã‚Í”jŠü
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	//ƒXƒƒbƒvƒ`ƒF[ƒ“‚Ì¶¬

	result = dxgiFactory->CreateSwapChainForHwnd(commandQueue, hwnd, &swapChainDesc, nullptr, nullptr, (IDXGISwapChain1**)&swapChain);
	assert(SUCCEEDED(result));

	//ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv‚Ìİ’è
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;			//ƒŒƒ“ƒ_[ƒ^[ƒQƒbƒgƒrƒ…[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;		//— •\‚Ì‚Q‚Â

	//ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv‚Ì¶¬
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//ƒoƒbƒNƒoƒbƒtƒ@
	std::vector<ID3D12Resource*> backBuffers;
	backBuffers.resize(swapChainDesc.BufferCount);

	//ƒXƒƒbƒvƒ`ƒF[ƒ“‚Ì‘S‚Ä‚Ìƒoƒbƒtƒ@‚É‚Â‚¢‚Äˆ—‚·‚é
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//ƒXƒƒbƒvƒ`ƒF[ƒ“‚©‚çƒoƒbƒtƒ@‚ğæ“¾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//ƒfƒXƒNƒŠƒvƒ^ƒq[ƒv‚Ìƒnƒ“ƒhƒ‹‚ğæ“¾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//— ‚©•\‚©‚ÅƒAƒhƒŒƒX‚ª‚¸‚ê‚é
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//ƒŒƒ“ƒ_[ƒ^[ƒQƒbƒgƒrƒ…[‚Ìİ’è
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//ƒVƒF[ƒ_[‚ÌŒvZŒ‹‰Ê‚ğSRGB‚É•ÏŠ·‚µ‚Ä‘‚«‚Ş
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//ƒŒƒ“ƒ_[ƒ^[ƒQƒbƒgƒrƒ…[‚Ì¶¬
		device->CreateRenderTargetView(backBuffers[i], &rtvDesc, rtvHandle);
	}

	//ƒtƒFƒ“ƒX‚Ì¶¬
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;

	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));


	//DirectX‰Šú‰»ˆ—@‚±‚±‚Ü‚Å@@[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

	//ƒQ[ƒ€ƒ‹[ƒv
	while (true)
	{
		//ƒƒbƒZ[ƒW‚ ‚éH
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);	//ƒL[“ü—ÍƒƒbƒZ[ƒW‚Ìˆ—
			DispatchMessage(&msg);	//ƒvƒƒV[ƒWƒƒ‚ÉƒƒbƒZ[ƒW‚ğ‘—‚é
		}

		//~ƒ{ƒ^ƒ“‚ÅI—¹ƒƒbƒZ[ƒW‚ª—ˆ‚½‚çƒQ[ƒ€ƒ‹[ƒv‚ğ”²‚¯‚é
		if (msg.message == WM_QUIT)
		{
			break;
		}

		//DirecX–ˆƒtƒŒ[ƒ€@‚±‚±‚©‚ç@@[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
		
		//ƒoƒbƒNƒoƒbƒtƒ@‚Ì”Ô†‚ğæ“¾(2‚Â‚È‚Ì‚Å0”Ô‚©1”Ô)
		UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

		//1.ƒŠƒ\[ƒXƒoƒŠƒA‚Å‘‚«‚İ‰Â”\‚É•ÏX
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Transition.pResource = backBuffers[bbIndex];				//ƒoƒbƒNƒoƒbƒtƒ@‚ğw’è
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;		//•\¦ó‘Ô‚©‚ç
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//•`‰æó‘Ô‚Ö
		commandList->ResourceBarrier(1, &barrierDesc);

		//2. •`‰ææ‚Ì•ÏX
		//ƒŒƒ“ƒ_[ƒ^[ƒQƒbƒgƒrƒ…[‚Ìƒnƒ“ƒhƒ‹‚ğæ“¾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

		//3. ‰æ–ÊƒNƒŠƒA
		FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };	//F‚Ìw’è‚ÍRGBA‚Ì0.0f`1.0f
		commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

		//--------------4.•`‰æƒRƒ}ƒ“ƒh@‚±‚±‚©‚ç---------------//
		 
		



		//--------------4.•`‰æƒRƒ}ƒ“ƒh@‚±‚±‚Ü‚Å---------------//

		//5. ƒŠƒ\[ƒXƒoƒŠƒA‚ğ–ß‚·
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//•`‰æó‘Ô‚©‚ç
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//•\¦ó‘Ô‚Ö
		commandList->ResourceBarrier(1, &barrierDesc);

		//–½—ß‚ÌƒNƒ[ƒY
		result = commandList->Close();
		assert(SUCCEEDED(result));
		//ƒRƒ}ƒ“ƒhƒŠƒXƒg‚ÌÀs
		ID3D12CommandList* commandLists[] = { commandList };
		commandQueue->ExecuteCommandLists(1, commandLists);

		//‰æ–Ê‚É•\¦‚·‚éƒoƒbƒtƒ@‚ğƒtƒŠƒbƒv(— •\‚Ì“ü‚ê‘Ö‚¦)
		result = swapChain->Present(1, 0);
		assert(SUCCEEDED(result));

		//ƒRƒ}ƒ“ƒh‚ÌÀsŠ®—¹‚ğ‘Ò‚Â
		commandQueue->Signal(fence, ++fenceVal);
		if (fence->GetCompletedValue() != fenceVal)
		{
			HANDLE event = CreateEvent(nullptr, false, false, nullptr);
			fence->SetEventOnCompletion(fenceVal, event);
			WaitForSingleObject(event, INFINITE);
			CloseHandle(event);
		}

		//ƒLƒ…[‚ğƒNƒŠƒA
		result = commandAllocator->Reset();
		assert(SUCCEEDED(result));
		//Ä‚ÑƒRƒ}ƒ“ƒhƒŠƒXƒg‚ğ‚½‚ß‚é€”õ
		result = commandList->Reset(commandAllocator, nullptr);
		assert(SUCCEEDED(result));


		//DirecX–ˆƒtƒŒ[ƒ€@‚±‚±‚Ü‚Å@@[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||[|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

	}
	
	return 0;
}
