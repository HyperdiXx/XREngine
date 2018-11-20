#pragma once

#ifndef _TIMER_H
#define _TIZMER_H

#include <windows.h>
#include "../pch/TypesSetup.h"
#include "../../Core.h"


namespace XEngine
{
	class XENGINE_API GameTimer
	{
	public:
		GameTimer();
		~GameTimer();

		void Init();
		void Start();
		void Reset();
		void Tick();


		real32 GetRuntime();
		real32 GetTime();

	private:
		real32 mFreq;
		real32 mStartTime;
		real32 mTickTime;
		real32 mEndTime;
	};
}

#endif // !_TIMER_H

