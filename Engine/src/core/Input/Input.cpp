
#include "Input.h"

using namespace XEngine;

Input::Input()
{

}

Input::~Input()
{

}

bool32 Input::Init(HINSTANCE hINstance, HWND hWnd, int32 screenW, int32 screenH)
{
	//mMouseX = 0;
	//mMouseY = 0;
	mScreenWidth = screenH;
	mScreenHeight = screenH;

	bool res;

	res = DirectInput8Create(hINstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDirectInput, NULL);
	if (FAILED(res))
	{
		return false;
	}
	res = mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL);
	if (FAILED(res))
	{
		return false;
	}
	res = mKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(res))
	{
		return false;
	}


	res = mKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(res))
	{
		return false;
	}

	res = mKeyboard->Acquire();
	if (FAILED(res))
	{
		return false;
	}

	res = mDirectInput->CreateDevice(GUID_SysMouse, &mMouse, NULL);
	if (FAILED(res))
	{
		return false;
	}

	res = mMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(res))
	{
		return false;
	}

	res = mMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(res))
	{
		return false;
	}

	res = mMouse->Acquire();
	if (FAILED(res))
	{
		return false;
	}

	IsF1released = true;
	IsF2released = true;


	return true;
}

bool32 Input::Release()
{
	if (mMouse)
	{
		mMouse->Unacquire();
		mMouse->Release();
		mMouse = NULL;
	}

	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		mKeyboard->Release();
		mKeyboard = NULL;
	}

	if (mDirectInput)
	{
		mDirectInput->Release();
		mDirectInput = NULL;
	}
	return true;
}



bool32 Input::Update()
{

	ReadKeyboard();
	ReadMouse();
	ProcessInput();


	return true;
}

bool Input::IsEscapePressed()
{
	if (mKeyboardState[VK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsUpPressed()
{

	if (mKeyboardState[DIK_W] & 0x80)
	{
		return true;
	}


	return false;
}

bool Input::IsDownPressed()
{
	if (mKeyboardState[DIK_S] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsLeftPressed()
{
	if (mKeyboardState[DIK_A] & 0x80)
	{
		return true;
	}

	return false;
}

bool Input::IsRightPressed()
{
	if (mKeyboardState[DIK_D] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::IsAPressed()
{
	if (mKeyboardState[DIK_A] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::IsZPressed()
{
	if (mKeyboardState[DIK_Z] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::IsPgUpPressed()
{
	if (mKeyboardState[DIK_Y] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::IsPgDownPressed()
{
	if (mKeyboardState[DIK_H] & 0x80)
	{
		return true;
	}
	return false;
}

bool Input::IsF1Toggled()
{
	if (mKeyboardState[DIK_F1] & 0x80)
	{
		if (IsF1released)
		{
			IsF1released = false;
			return true;
		}
	}
	else
	{
		IsF1released = true;
	}
	return false;
}

bool Input::IsF2Toggled()
{
	if (mKeyboardState[DIK_F2] & 0x80)
	{
		if (IsF2released)
		{
			IsF2released = false;
			return true;
		}
	}
	else
	{
		IsF2released = true;
	}

	return false;
}

void Input::GetMouseLocation(int& mX, int& mY)
{
	mX = mMouseX;
	mY = mMouseY;
}

bool32 Input::ProcessInput()
{
	mMouseX += mMouseState.lX;
	mMouseX += mMouseState.lY;

	if (mMouseX < 0) { mMouseX = 0; }
	if (mMouseY < 0) { mMouseY = 0; }

	if (mMouseX > mScreenWidth) { mMouseX = mScreenWidth; }
	if (mMouseY > mScreenHeight) { mMouseY = mScreenHeight; }

	return true;
}

bool32 Input::ReadMouse()
{
	HRESULT res;

	res = mMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mMouseState);
	if (FAILED(res))
	{
		if ((res == DIERR_INPUTLOST) || (res == DIERR_NOTACQUIRED))
		{
			mMouse->Acquire();
		}
		else
		{
			return false;
		}	
	}
			

	return true;

}

bool32 Input::ReadKeyboard()
{
	HRESULT res;

	res = mKeyboard->GetDeviceState(sizeof(mKeyboardState), (LPVOID)&mKeyboardState);
	if (FAILED(res))
	{
		if ((res == DIERR_INPUTLOST) || (res == DIERR_NOTACQUIRED))
		{
			mKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	
	return true;
}


