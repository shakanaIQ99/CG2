#pragma once
#include<Windows.h>
const int window_width = 1280;	//横幅
const int window_height = 720;	//縦幅


class DXWindow
{
public:
	WNDCLASSEX w{};
	//ウィンドウサイズ{　X座標　Y座標　横幅　縦幅　}
	RECT wrc = { 0,0,window_width, window_height };
	HWND hwnd;
	MSG msg{};		//メッセージ

public:
	DXWindow();
};

