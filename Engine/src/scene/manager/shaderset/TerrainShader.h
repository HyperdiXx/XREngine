#pragma once

#ifndef TERRAIN_SHADER
#define TERRAIN_SHADER

#include "../../../core/pch/TypesSetup.h"
#include "../../../Core.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>

using namespace DirectX;


namespace XEngine
{
	class XENGINE_API TerrainShader
	{
	private:
		struct Matrix
		{
			XMMATRIX world, view, proj;
		};

		struct Light
		{
			XMFLOAT4 ambientCol;
			XMFLOAT4 diffuseCol;
			XMFLOAT3 direction;
			float padding;
		};
	public:
		TerrainShader();
		~TerrainShader();

		bool Init(ID3D11Device*, HWND);
		bool Render(ID3D11DeviceContext*, int, XMMATRIX&, XMMATRIX&, XMMATRIX&, XMFLOAT4&, XMFLOAT4&, XMFLOAT3&);
		void Release();


		bool InitShader(ID3D11Device*, HWND, LPCWSTR, LPCWSTR);

		void ReleaseShader();
		bool ShaderPass(ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX&, XMFLOAT4&, XMFLOAT4&, XMFLOAT3&);
		void RenderShader(ID3D11DeviceContext*, int);
	private:
		ID3D11InputLayout* mInputLayout;
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader* mPixelShader;
		ID3D11SamplerState* mSampleState;
		ID3D11Buffer* mMatrix;
		ID3D11Buffer* mLight;
	};

}
#endif // !

