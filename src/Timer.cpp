#include "Timer.h"

GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

void GameTimer::Init()
{
	int64 Freq;

	QueryPerformanceFrequency((LARGE_INTEGER*)&Freq);

	real32 mFreq = (real32)Freq;

	QueryPerformanceCounter((LARGE_INTEGER*)&mStartTime);
}

void GameTimer::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mStartTime);
}

void GameTimer::Reset()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mEndTime);
}

void GameTimer::Tick()
{
	int64 currTime;
	int64 elapsedTime;

	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	elapsedTime = currTime - mStartTime;

	mTickTime = (real32)elapsedTime / mFreq;

	mStartTime = currTime;

}

real32 GameTimer::GetRuntime()
{
	real32 elapsedTicks;
	INT64 frequency;
	real32 milliseconds;

	elapsedTicks = (real32)(mEndTime - mStartTime);

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	milliseconds = (elapsedTicks / (real32)frequency) * 1000.0f;

	return real32(milliseconds);
}

real32 GameTimer::GetTime()
{
	return real32(mTickTime);
}
