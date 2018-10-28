
#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::SetPosition(float x, float y, float z)
{
	mPosX = x;
	mPosY = y;
	mPosZ = z;
}

void Controller::SetRotation(float x,  float y,  float z)
{
	mRotX = x;
	mRotY = y;
	mRotZ = z;
}

void Controller::GetPosition(real32 & x, real32 & y, real32 & z)
{
	x = mPosX;
	y = mPosY;
	z = mPosZ;
}

void Controller::GetRotation(real32 & x, real32 & y, real32 & z)
{
	x = mRotX;
	y = mRotY;
	z = mRotZ;
}

void Controller::SetFrameTime(real32 time)
{
	mFrameTime = time;
}

void Controller::MoveForward(bool key)
{

	if (key)
	{
		speed += mFrameTime * 1.0f;
		if (speed > (mFrameTime * 50.0f))
		{
			speed = mFrameTime * 50.0f;
		}
	}
	else
	{
		speed -= mFrameTime * 0.5f;

		if (speed < 0.0f)
		{
			speed = 0.0f;
		}
	}

	real32 radians = mRotY * 0.0174532925f;

	mPosX += sinf(radians) * speed;
	mPosZ += cosf(radians) * speed;
}

void Controller::MoveBackward(bool key)
{
	if (key)
	{
		speed += mFrameTime * 1.0f;
		if (speed > (mFrameTime * 50.0f))
		{
			speed = mFrameTime * 50.0f;
		}
	}
	else
	{
		speed -= mFrameTime * 0.5f;

		if (speed < 0.0f)
		{
			speed = 0.0f;
		}
	}

	real32 radians = mRotY * 0.0174532925f;

	mPosX += sinf(radians) * speed;
	mPosZ += cosf(radians) * speed;
}

void Controller::MoveUpward(bool)
{
}

void Controller::MoveDownward(bool)
{
}

void Controller::TurnLeft(bool)
{
}

void Controller::TurnRight(bool)
{
}

void Controller::LookUpward(bool)
{
}

void Controller::LookDownward(bool)
{
}
