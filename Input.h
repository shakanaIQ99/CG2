#pragma once
#define DIRECTINPUT_VERSION	0x0800
#include<dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class Input
{
public:
	IDirectInput8* directInput;
	IDirectInputDevice8* keyboard;
public:
	Input(WNDCLASSEX w, HWND hwnd);

	void InputUpdate();

	bool GetKey(BYTE _key) const;

	bool GetPressKey(BYTE _key) const;

	bool GetReleaseKey(BYTE _key) const;
};
