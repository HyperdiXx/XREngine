#ifndef _FPSCLASS_H_
#define _FPSCLASS_H_

#pragma comment(lib, "winmm.lib")

#include "../pch/TypesSetup.h"
#include "../../Core.h"

#include <windows.h>
#include <mmsystem.h>

namespace XEngine
{
	struct XENGINE_API FpsStat
	{
		FpsStat();
		~FpsStat();

		void Initialize();
		void Update();
		int GetFps();

		int32 mFps, mCount;
		unsigned long mStartTime;
	};
}

#endif