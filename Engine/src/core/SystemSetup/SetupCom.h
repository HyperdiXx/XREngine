#pragma once

#ifndef _SETUP_
#define _SETUP_

#define WIN32_LEAN_AND_MEAN

#define LOG(...) printf(__VA_ARGS__)


#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "AppAbst.h"

	struct XENGINE_API SetupCom
	{
		SetupCom();
		~SetupCom();

		bool Init();
		void Start();
		void Release();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

		bool Update();
		bool InitWindow(int32&, int32&);
		bool InitConsoleWindow();

		HWND hWnd;
		HINSTANCE hInstance;

		//WindowSetup* mWindow;
		AppAbstraction* mApp;
	};

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	static SetupCom* AppNew = NULL;
#endif // !_SETUP_

