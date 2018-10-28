#pragma once

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "Setup.h"

#include <math.h>


class Controller
{
public:
	Controller();
	~Controller();

	void SetPosition(real32, real32, real32);
	void SetRotation(real32, real32, real32);

	void GetPosition(real32&, real32&, real32&);
	void GetRotation(real32&, real32&, real32&);

	void SetFrameTime(real32);

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);

private:
	real32 mPosX, mPosY, mPosZ;
	real32 mRotX, mRotY, mRotZ;

	real32 mFrameTime;

	real32 speed;
	
private:

};
#endif // !_CONTROLLER_H

