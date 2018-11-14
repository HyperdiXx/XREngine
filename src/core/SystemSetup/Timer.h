#pragma once

#ifndef _TIMER_H
#define _TIZMER_H

#include <windows.h>
#include "../pch/TypesSetup.h"
#include "../../Core.h"


namespace XEngine
{
	struct XENGINE_API GameTimer
	{
		GameTimer();
		~GameTimer();

		void Init();
		void Start();
		void Reset();
		void Tick();

		real32 GetRuntime();
		real32 GetTime();

		real32 mFreq;
		real32 mStartTime;
		real32 mTickTime;
		real32 mEndTime;
	};
}

#endif // !_TIMER_H

