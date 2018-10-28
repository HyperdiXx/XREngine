
#include "WindowSetup.h"

WindowSetup::WindowSetup()
{
	mhInstance = 0;
	mHwnd = 0;
}

WindowSetup::~WindowSetup()
{
}

LRESULT CALLBACK WindowSetup::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void WindowSetup::InitWindow(HINSTANCE hinst, HWND hwnd, int32& W, int32& H)
{
	App = this;

	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;
		

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinst;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Engine";
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	W = GetSystemMetrics(SM_CXSCREEN);
	H = GetSystemMetrics(SM_CYSCREEN);

	/*if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)W;
		dmScreenSettings.dmPelsHeight = (unsigned long)H;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;
	}
	else*/
	{
		W = 1280;
		H = 720;

		posX = (GetSystemMetrics(SM_CXSCREEN) - W) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - H) / 2;
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, L"Engine", L"Engine", WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, W, H, NULL, NULL, hinst, NULL);

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	
	ShowCursor(false);

	return;


}


void WindowSetup::Release()
{
	ShowCursor(true);

	/*if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}*/

	DestroyWindow(GetHwnd());
	GetHwnd() = NULL;

	UnregisterClass(L"Engine", GetHINSTANCE());
	GetHINSTANCE() = NULL;

	App = NULL;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return App->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	
	}
}