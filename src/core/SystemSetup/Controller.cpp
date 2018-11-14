
#include "Controller.h"


XEngine::Controller::Controller()
{
	mForwardSpeed = 0.0f;
	mBackwardSpeed = 0.0f;
	mUpwardSpeed = 0.0f;
	mDownwardSpeed = 0.0f;
	mLeftTurnSpeed = 0.0f;
	mRightTurnSpeed = 0.0f;
	mLookUpSpeed = 0.0f;
	mLookDownSpeed = 0.0f;
}

XEngine::Controller::~Controller()
{
}

void XEngine::Controller::SetPosition(float x, float y, float z)
{
	mPosX = x;
	mPosY = y;
	mPosZ = z;
}

void XEngine::Controller::SetRotation(float x,  float y,  float z)
{
	mRotX = x;
	mRotY = y;
	mRotZ = z;
}

void XEngine::Controller::GetPosition(float & x, float & y, float & z)
{
	x = mPosX;
	y = mPosY;
	z = mPosZ;
}

void XEngine::Controller::GetRotation(float & x, float & y, float & z)
{
	x = mRotX;
	y = mRotY;
	z = mRotZ;
}

void XEngine::Controller::SetFrameTime(float time)
{
	mFrameTime = time;
}

void XEngine::Controller::MoveForward(bool key)
{
	float radians;

	if (key)
	{
		mForwardSpeed += mFrameTime * 10.001f;

		if (mForwardSpeed > (mFrameTime * 0.03f))
		{
			mForwardSpeed = mFrameTime * 0.03f;
		}
	}
	else
	{
		mForwardSpeed -= mFrameTime * 0.0007f;

		if (mForwardSpeed < 0.0f)
		{
			mForwardSpeed = 0.0f;
		}
	}

	radians = mRotY * 0.0174532925f;

	mPosX -= sinf(radians) * mForwardSpeed;
	mPosZ -= cosf(radians) * mForwardSpeed;
	LOG("%f", mForwardSpeed);
	
}

void XEngine::Controller::MoveBackward(bool key)
{
	float radians;

	if (key)
	{
		mBackwardSpeed += mFrameTime * 10.001f;

		if (mBackwardSpeed > (mFrameTime * 0.03f))
		{
			mBackwardSpeed = mFrameTime * 0.03f;
		}
	}
	else
	{
		mBackwardSpeed -= mFrameTime * 0.0007f;

		if (mBackwardSpeed < 0.0f)
		{
			mBackwardSpeed = 0.0f;
		}
	}

	radians = mRotY * 0.0174532925f;

	mPosX += sinf(radians) * mBackwardSpeed;
	mPosZ += cosf(radians) * mBackwardSpeed;

	return;
}

void XEngine::Controller::MoveUpward(bool key)
{
	if (key)
	{
		mUpwardSpeed += mFrameTime * 1.5f;

		if (mUpwardSpeed > (mFrameTime  * 15.0f))
		{
			mUpwardSpeed = mFrameTime * 15.0f;
		}
	}
	else
	{
		mUpwardSpeed -= mFrameTime * 0.5f;

		if (mUpwardSpeed < 0.0f)
		{
			mUpwardSpeed = 0.0f;
		}
	}

	mPosY += mUpwardSpeed;

}

void XEngine::Controller::MoveDownward(bool key)
{
	if (key)
	{
		mDownwardSpeed += mFrameTime * 1.5f;

		if (mDownwardSpeed > (mFrameTime  * 15.0f))
		{
			mDownwardSpeed = mFrameTime * 15.0f;
		}
	}
	else
	{
		mDownwardSpeed -= mFrameTime * 0.5f;

		if (mDownwardSpeed < 0.0f)
		{
			mDownwardSpeed = 0.0f;
		}
	}

	mPosY -= mDownwardSpeed;


}

void XEngine::Controller::TurnLeft(bool key)
{
	if (key)
	{
		mLeftTurnSpeed += mFrameTime * 5.0f;

		if (mLeftTurnSpeed > (mFrameTime * 150.0f))
		{
			mLeftTurnSpeed = mFrameTime * 150.0f;
		}
	}
	else
	{
		mLeftTurnSpeed -= mFrameTime * 3.5f;

		if (mLeftTurnSpeed < 0.0f)
		{
			mLeftTurnSpeed = 0.0f;
		}
	}

	mRotY -= mLeftTurnSpeed;

	if (mRotY < 0.0f)
	{
		mRotY += 360.0f;
	}
}

void XEngine::Controller::TurnRight(bool key)
{
	if (key)
	{
		mRightTurnSpeed += mFrameTime * 5.0f;

		if (mRightTurnSpeed > (mFrameTime * 150.0f))
		{
			mRightTurnSpeed = mFrameTime * 150.0f;
		}
	}
	else
	{
		mRightTurnSpeed -= mFrameTime * 3.5f;

		if (mRightTurnSpeed < 0.0f)
		{
			mRightTurnSpeed = 0.0f;
		}
	}

	mRotY += mRightTurnSpeed;

	if (mRotY > 360.0f)
	{
		mRotY -= 360.0f;
	}
}

void XEngine::Controller::LookUpward(bool key)
{
	if (key)
	{
		mLookUpSpeed += mFrameTime * 7.5f;

		if (mLookUpSpeed > (mFrameTime * 75.0f))
		{
			mLookUpSpeed = mFrameTime * 75.0f;
		}
	}
	else
	{
		mLookUpSpeed -= mFrameTime * 2.0f;

		if (mLookUpSpeed < 0.0f)
		{
			mLookUpSpeed = 0.0f;
		}
	}

	mRotY -= mLookUpSpeed;


	if (mRotY > 90.0f)
	{
		mRotY = 90.0f;
	}
}

void XEngine::Controller::LookDownward(bool key)
{
	if (key)
	{
		mLookDownSpeed += mFrameTime * 7.5f;

		if (mLookDownSpeed > (mFrameTime * 75.0f))
		{
			mLookDownSpeed = mFrameTime  * 75.0f;
		}
	}
	else
	{
		mLookDownSpeed -= mFrameTime * 2.0f;

		if (mLookDownSpeed < 0.0f)
		{
			mLookDownSpeed = 0.0f;
		}
	}

	mRotX += mLookDownSpeed;

	if (mRotX < -90.0f)
	{
		mRotX = -90.0f;
	}
}
