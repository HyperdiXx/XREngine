
#include "FPS.h"


FpsStat::FpsStat()
{
}

FpsStat::~FpsStat()
{
}


void FpsStat::Initialize()
{
	mFps = 0;
	mCount = 0;
	mStartTime = timeGetTime();
	return;
}


void FpsStat::Update()
{
	mCount++;

	if (timeGetTime() >= (mStartTime + 1000))
	{
		mFps = mCount;
		mCount = 0;

		mStartTime = timeGetTime();
	}
}


int FpsStat::GetFps()
{
	return mFps;
}