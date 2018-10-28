#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Setup.h"

#include <DirectXMath.h>

using namespace DirectX;

class Camera
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
	XMMATRIX mViewMatrix, mBaseViewMatrix;
};
#endif // !_CAMERA_H_

