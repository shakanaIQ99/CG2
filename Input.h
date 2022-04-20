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
	Input();
};

