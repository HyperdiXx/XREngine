
#include "Camera.h"

using namespace XEngine;

XEngine::Camera::Camera()
{
	
}

XEngine::Camera::~Camera()
{
}

void XEngine::Camera::SetPosition(float x, float y, float z)
{
	mPosX = x;
	mPosY = y;
	mPosZ = z;
}

void XEngine::Camera::SetRotation(float x, float y, float z)
{
	mRotX = x;
	mRotY = y;
	mRotZ = z;
}

XMFLOAT3 XEngine::Camera::GetPosition()
{
	return XMFLOAT3(mPosX, mPosY, mPosZ);
}

XMFLOAT3 XEngine::Camera::GetRotation()
{
	return XMFLOAT3(mRotX, mRotY, mRotZ);
}

void XEngine::Camera::Render()
{

	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	upVector = XMLoadFloat3(&up);
	//upVector = up;

	position.x = mPosX;
	position.y = mPosY;
	position.z = mPosZ;

	positionVector = XMLoadFloat3(&position);

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	lookAtVector = XMLoadFloat3(&lookAt);

	pitch = mRotX * 0.0174532925f;
	yaw = mRotY * 0.0174532925f;
	roll = mRotZ * 0.0174532925f;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	mViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}

void XEngine::Camera::GetViewMatrix(XMMATRIX &view)
{
	view = mViewMatrix;
}

void XEngine::Camera::RenderBaseViewMatrix()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	upVector = XMLoadFloat3(&up);

	position.x = mPosX;
	position.y = mPosY;
	position.z = mPosZ;

	positionVector = XMLoadFloat3(&position);

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	lookAtVector = XMLoadFloat3(&lookAt);

	pitch = mRotX * 0.0174532925f;
	yaw = mRotY * 0.0174532925f;
	roll = mRotZ * 0.0174532925f;

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	mBaseViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}

void XEngine::Camera::GetBaseViewMatrix(XMMATRIX &base)
{
	base = mBaseViewMatrix;
}


