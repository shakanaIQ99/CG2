#include "Input.h"
#include"DXInitialize.h"

BYTE key[256] = { 0 };
BYTE oldkey[256] = { 0 };

Input::Input(WNDCLASSEX w, HWND hwnd)
{
#pragma region	キーボード周り
	HRESULT result;

	//DirectInputの初期化
	directInput = nullptr;
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

#pragma endregion	キーボード周り初期化

}

void Input::InputUpdate()
{
	//キーボード情報の取得開始
	keyboard->Acquire();

	//全キーの入力状態を取得する
	
	for (int i = 0; i < 256; i++)
	{
		oldkey[i] = key[i];
	}
	keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::GetKey(BYTE _key) const
{
	if (key[_key])
	{
		return true;
	}

	return false;
}

bool Input::GetPressKey(BYTE _key) const
{
	if (key[_key] && !oldkey[_key])
	{
		return true;
	}
	return false;
}

bool Input::GetReleaseKey(BYTE _key) const
{
	if (key[_key] && !oldkey[_key])
	{
		return true;
	}
	return false;
}



