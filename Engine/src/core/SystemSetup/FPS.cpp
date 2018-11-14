
#include "FPS.h"


XEngine::FpsStat::FpsStat()
{
}

XEngine::FpsStat::~FpsStat()
{
}


void XEngine::FpsStat::Initialize()
{
	mFps = 0;
	mCount = 0;
	mStartTime = timeGetTime();
	return;
}


void XEngine::FpsStat::Update()
{
	mCount++;

	if (timeGetTime() >= (mStartTime + 1000))
	{
		mFps = mCount;
		mCount = 0;

		mStartTime = timeGetTime();
	}
}


int XEngine::FpsStat::GetFps()
{
	return mFps;
}