#include "Lighting.h"

XEngine::Light::Light()
{
}

XEngine::Light::~Light()
{
}

void XEngine::Light::SetDirection(float x, float y, float z)
{
	Direction = XMFLOAT3(x, y, z);
}

void XEngine::Light::SetAmbientColor(float r, float g, float b, float a)
{
	AbientColor = XMFLOAT4(r, g, b, a);
}

void XEngine::Light::SetDiffuseColor(float r, float g, float b, float a)
{
	DiffColor = XMFLOAT4(r, g, b, a);
}

XMFLOAT4 & XEngine::Light::GetAmbientColor()
{
	return AbientColor;
}

XMFLOAT4 & XEngine::Light::GetDiffuseColor()
{
	return DiffColor;
}

XMFLOAT3 & XEngine::Light::GetDirection()
{
	return Direction;
}
