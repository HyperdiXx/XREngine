#pragma once


#ifdef X_PLATFORM_WINDOWS
	#ifdef  X_BUILD_DLL
		#define XENGINE_API __declspec(dllexport)
	#else
		#define XENGINE_API __declspec(dllimport)
	#endif // DEBUG
#else
	#error WINDOWS_SUPPORT
#endif // X_PLATFORM_WINDOWS

