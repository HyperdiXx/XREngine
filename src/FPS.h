#ifndef _FPSCLASS_H_
#define _FPSCLASS_H_

#pragma comment(lib, "winmm.lib")

#include "Setup.h"

#include <windows.h>
#include <mmsystem.h>

class FpsStat
{
public:
	FpsStat();
	~FpsStat();

	void Initialize();
	void Update();
	int GetFps();

private:
	int32 mFps, mCount;
	unsigned long mStartTime;
};

#endif