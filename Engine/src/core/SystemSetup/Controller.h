#pragma once

#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "../pch/TypesSetup.h"
#include "../../Core.h"
#include <math.h>

namespace XEngine 
{
	class XENGINE_API Controller
	{
	public:
		Controller();
		~Controller();

		void SetPosition(float, float, float);
		void SetRotation(float, float, float);

		void GetPosition(float&, float&, float&);
		void GetRotation(float&, float&, float&);

		void SetFrameTime(float);

		void MoveForward(bool);
		void MoveBackward(bool);
		void MoveUpward(bool);
		void MoveDownward(bool);
		void TurnLeft(bool);
		void TurnRight(bool);
		void LookUpward(bool);
		void LookDownward(bool);

	private:
		float mPosX, mPosY, mPosZ;
		float mRotX, mRotY, mRotZ;

		float mFrameTime;

		float mForwardSpeed, mBackwardSpeed;
		float mUpwardSpeed, mDownwardSpeed;
		float mLeftTurnSpeed, mRightTurnSpeed;
		float mLookUpSpeed, mLookDownSpeed;


	};
}
#endif // !_CONTROLLER_H

