#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_


#include "../../Core.h"
#include <DirectXMath.h>


using namespace DirectX;

namespace XEngine
{
	class XENGINE_API Camera
	{
	public:
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
	private:
		float mPosX, mPosY, mPosZ;
		float mRotX, mRotY, mRotZ;
		DirectX::XMMATRIX mViewMatrix, mBaseViewMatrix;
	};
}

#endif // !_CAMERA_H_

