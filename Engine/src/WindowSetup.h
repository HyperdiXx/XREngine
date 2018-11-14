#pragma once

#ifndef _WINDOW_SETUP
#define _WINDOW_SETUP_



#include <windows.h>
#include "core\pch\TypesSetup.h"

class WindowSetup
{
public:


	WindowSetup();
	~WindowSetup();

	void InitWindow(HINSTANCE, HWND, int32&, int32&);
	void Release();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	HWND & GetHwnd() { return mHwnd; }
	HINSTANCE & GetHINSTANCE() { return mhInstance; }

private:
	LPCWSTR mApplicationName;
	HINSTANCE mhInstance;
	HWND mHwnd;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static WindowSetup* App = NULL;


#endif // !_WINDOW_SETUP

