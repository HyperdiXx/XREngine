#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../../core/pch/TypesSetup.h"
#include "../../../Core.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>


using namespace DirectX;


namespace XEngine
{
	struct XENGINE_API TextureShader
	{
		struct Matrix
		{
			XMMATRIX world, view, proj;
		};

		TextureShader();
		~TextureShader();

		bool Init(ID3D11Device*, HWND);
		bool Render(ID3D11DeviceContext*, int, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*);
		void Release();

		bool InitShader(ID3D11Device*, HWND, LPCWSTR, LPCWSTR);
		
		void ReleaseShader();
		bool ShaderPass(ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*);
		void RenderShader(ID3D11DeviceContext*, int);


		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader* mPixelShader;
		ID3D11Buffer* mMatrixBuffer;
		ID3D11InputLayout* mLayout;
		ID3D11SamplerState* mSamplerState;
	};
}

#endif // !TERRAIN_SHADER_H

