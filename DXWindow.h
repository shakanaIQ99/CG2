#pragma once
#include<Windows.h>
const int window_width = 1280;	//����
const int window_height = 720;	//�c��


class DXWindow
{
public:
	WNDCLASSEX w{};
	//�E�B���h�E�T�C�Y{�@X���W�@Y���W�@�����@�c���@}
	RECT wrc = { 0,0,window_width, window_height };
	HWND hwnd;
	MSG msg{};		//���b�Z�[�W

public:
	DXWindow();
};

