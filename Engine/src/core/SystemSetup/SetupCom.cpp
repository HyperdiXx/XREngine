
#include "SetupCom.h"
#include <consoleapi.h>

SetupCom::SetupCom()
{
	//mWindow = 0;
	mApp = 0;
}

SetupCom::~SetupCom()
{

}

bool SetupCom::Init()
{
	int32 screenW = 0, screenH = 0;
	
	//mWindow->InitWindow(mhInstanc, hwnD, screenW, screenH);
	InitWindow(screenW, screenH);

	
	//mApp = (AppAbstraction*)malloc(sizeof(AppAbstraction));

	mApp = new AppAbstraction;
	if (!mApp)
		return false;

	if (!mApp->Init(hInstance, hWnd, screenW, screenH))
	{
		return false;
	}
		

	return true;
}

void SetupCom::Start()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Update();
			if (!result)
			{
				done = true;
			}
		}

	}

}

void SetupCom::Release()
{
	//mWindow->Release();
	ShowCursor(true);

	/*if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
*/
	
	DestroyWindow(hWnd);
	hWnd = NULL;

	UnregisterClass("Engine", hInstance);
	hInstance = NULL;

	if (FreeConsole())
		MessageBox(NULL, "Failed to free the console!", NULL, MB_ICONEXCLAMATION);

	AppNew = NULL;

	

}

bool SetupCom::Update()
{

	if (!mApp->Update())
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK SetupCom::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		
	case WM_DESTROY:
	{	
		PostQuitMessage(0);
		return 0;
	}

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return AppNew->MessageHandler(hwnd, umessage, wparam, lparam);
	}

	}
}

bool SetupCom::InitWindow(int32 &w, int32 &h)
{
	AppNew = this;

	if (InitConsoleWindow())
	{
		LOG("Console init\n");
	}
	
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Engine";
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	w = GetSystemMetrics(SM_CXSCREEN);
	h = GetSystemMetrics(SM_CYSCREEN);

	//if (FULL_SCREEN)
	//{
	//	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	//	dmScreenSettings.dmSize = sizeof(dmScreenSettings);
	//	dmScreenSettings.dmPelsWidth = (unsigned long)w;
	//	dmScreenSettings.dmPelsHeight = (unsigned long)h;
	//	dmScreenSettings.dmBitsPerPel = 32;
	//	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	//	ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

	//	posX = posY = 0;
	//}
	//else
	//{
	//	
	//}

	w = 1280;
	h = 720;

	posX = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

	//WS_CLIPSIBLINGS WS_CLIPCHILDREN 

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, "Engine", "Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, w, h, NULL, NULL, hInstance, NULL);


	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	ShowCursor(true);


	return true;
	
}

bool SetupCom::InitConsoleWindow()
{
	AllocConsole();

	/*HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;*/

	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	return true;
}
