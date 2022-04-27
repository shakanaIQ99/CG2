#include "Input.h"
#include"DXInitialize.h"

BYTE key[256] = { 0 };
BYTE oldkey[256] = { 0 };

Input::Input(WNDCLASSEX w, HWND hwnd)
{
#pragma region	�L�[�{�[�h����
	HRESULT result;

	//DirectInput�̏�����
	directInput = nullptr;
	result = DirectInput8Create(w.hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	keyboard = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);	//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

#pragma endregion	�L�[�{�[�h���菉����

}

void Input::InputUpdate()
{
	//�L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();

	//�S�L�[�̓��͏�Ԃ��擾����

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