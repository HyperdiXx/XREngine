#pragma once

#ifndef _SETUP_
#define _SETUP_

#define WIN32_LEAN_AND_MEAN

#include "WindowSetup.h"
#include "AppAbst.h"

class SetupCom
{

public:
	SetupCom();
	~SetupCom();

	bool Init();
	void Start();
	void Release();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Update();
	void InitWindow(int32&, int32&);

private:
	HWND hWnd;
	HINSTANCE hInstance;

	//WindowSetup* mWindow;
	AppAbstraction* mApp;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static SetupCom* AppNew = NULL;


#endif // !_SETUP_

