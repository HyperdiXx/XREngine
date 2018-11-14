#pragma once

#ifndef LIGHT_CLASS
#define LIGHT_CLASS

#include "../Core.h"

#include <DirectXMath.h>

using namespace DirectX;

namespace XEngine
{
	struct Light
	{
		Light();
		~Light();

		void SetDirection(float, float, float);
		void SetAmbientColor(float, float, float, float);
		void SetDiffuseColor(float, float, float, float);

		XMFLOAT4& GetAmbientColor();
		XMFLOAT4& GetDiffuseColor();
		XMFLOAT3& GetDirection();

		XMFLOAT4 AbientColor;
		XMFLOAT4 DiffColor;
		XMFLOAT3 Direction;
	};
}
#endif // !LIGHT_CLASS

