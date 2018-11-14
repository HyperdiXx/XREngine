#pragma once

#ifndef _INPUT_H
#define _INPUT_H

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "../pch/TypesSetup.h"
#include <dinput.h>

struct Input
{

	Input();
	~Input();

	bool32 Init(HINSTANCE, HWND, int32, int32);
	bool32 Release();
	bool32 Update();

	bool IsEscapePressed();

	bool IsUpPressed();
	bool IsDownPressed();
	bool IsLeftPressed();
	bool IsRightPressed();
	bool IsAPressed();
	bool IsZPressed();
	bool IsPgUpPressed();
	bool IsPgDownPressed();

	bool IsF1Toggled();
	bool IsF2Toggled();

	void GetMouseLocation(int& mX, int& mY);


	bool32 ProcessInput();
	bool32 ReadMouse();
	bool32 ReadKeyboard();

	unsigned char mKeyboardState[256];
	DIMOUSESTATE mMouseState;

	int32 mScreenWidth, mScreenHeight;
	int32 mMouseX, mMouseY;

	bool32 IsF1released;
	bool32 IsF2released;

	IDirectInput8 * mDirectInput;
	IDirectInputDevice8* mKeyboard;
	IDirectInputDevice8* mMouse;
};
#endif // !_INPUT_H

