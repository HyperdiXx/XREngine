#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_


#include "../../Core.h"
#include <DirectXMath.h>


using namespace DirectX;

namespace XEngine
{
	struct XENGINE_API Camera
	{
		Camera();
		~Camera();

		void SetPosition(float, float, float);
		void SetRotation(float, float, float);

		XMFLOAT3 GetPosition();
		XMFLOAT3 GetRotation();

		void Render();
		void GetViewMatrix(XMMATRIX&);

		void RenderBaseViewMatrix();
		void GetBaseViewMatrix(XMMATRIX&);

		float mPosX, mPosY, mPosZ;
		float mRotX, mRotY, mRotZ;
		XMMATRIX mViewMatrix, mBaseViewMatrix;
	};
}

#endif // !_CAMERA_H_

