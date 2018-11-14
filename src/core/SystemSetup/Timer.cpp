#include "Timer.h"

XEngine::GameTimer::GameTimer()
{
}

XEngine::GameTimer::~GameTimer()
{
}

void XEngine::GameTimer::Init()
{
	int64 Freq;

	QueryPerformanceFrequency((LARGE_INTEGER*)&Freq);

	real32 mFreq = (real32)Freq;

	QueryPerformanceCounter((LARGE_INTEGER*)&mStartTime);
}

void XEngine::GameTimer::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mStartTime);
}

void XEngine::GameTimer::Reset()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mEndTime);
}

void XEngine::GameTimer::Tick()
{
	int64 currTime;
	int64 elapsedTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	elapsedTime = currTime - mStartTime;

	mTickTime = (real32)elapsedTime / mFreq;

	mStartTime = currTime;

}

real32 XEngine::GameTimer::GetRuntime()
{
	real32 elapsedTicks;
	INT64 frequency;
	real32 milliseconds;

	elapsedTicks = (real32)(mEndTime - mStartTime);

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	milliseconds = (elapsedTicks / (real32)frequency) * 1000.0f;

	return real32(milliseconds);
}

real32 XEngine::GameTimer::GetTime()
{
	return real32(mTickTime);
}
