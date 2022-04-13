#include <Windows.h>

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//メッセージに応じてゲームの固有の処理を行う
	switch (msg)
	{
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}



//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//コンソールへの文字出力
	//OutputDebugStringA("Heloo,DirectX!!\n");
	
	const int window_width = 1280;	//横幅
	const int window_height = 720;	//縦幅

	//ウィンドウクラスの設定
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);			
	w.lpfnWndProc = (WNDPROC)WindowProc;	//ウィンドウプロシージャを設定
	w.lpszClassName = L"DirecXGame";		//ウィンドウクラス名
	w.hInstance = GetModuleHandle(nullptr);	//ウィンドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル指定

	//ウィンドウクラスをOSに登録する
	RegisterClassEx(&w);
	//ウィンドウサイズ{　X座標　Y座標　横幅　縦幅　}
	RECT wrc = { 0,0,window_width, window_height };
	//自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd= CreateWindow
	(
		w.lpszClassName,		//クラス名
		L"DirectXGame",			//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	//標準的なウィンドウスタイル
		CW_USEDEFAULT,			//表示X座標(OSに任せる)
		CW_USEDEFAULT,			//表示Y座標(OSに任せる)
		wrc.right-wrc.left,

	)

	return 0;
}