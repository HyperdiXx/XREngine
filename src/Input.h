#pragma once

#ifndef _INPUT_H
#define _INPUT_H

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "Setup.h"
#include <dinput.h>

class Input
{
public:
	Input();
	~Input();

	bool32 Init(HINSTANCE, HWND, int32, int32);
	bool32 Release();
	bool32 Update();

	bool IsEscapePressed();

	bool IsUpPressed();

	void GetMouseLocation(int& mX, int& mY);


private:
	bool32 ProcessInput();
	bool32 ReadMouse();
	bool32 ReadKeyboard();
private:
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

