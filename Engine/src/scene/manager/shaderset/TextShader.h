#pragma once

#ifndef _TEXT_SHADER_H
#define _TEXT_SHADER_H

#include "../../../core/pch/TypesSetup.h"
#include "../../../Core.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>

using namespace DirectX;


struct XENGINE_API TextShader
{
	struct Matrix
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX proj;
	};
	struct PixelI
	{
		XMFLOAT4 pixelColor;
	};

	TextShader();
	~TextShader();

	bool Init(ID3D11Device*, HWND);
	bool Render(ID3D11DeviceContext*, int, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*, XMFLOAT4);
	void Release();
	
	bool InitShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	bool ShaderPass(ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);
	void ReleaseShader();

	ID3D11VertexShader * mVertexShader;
	ID3D11PixelShader* mPixelShader;
	ID3D11InputLayout* mLayout;
	ID3D11Buffer* mMatrixBuffer;
	ID3D11SamplerState* mSampleState;
	ID3D11Buffer* mPixelBuffer;
};
#endif // !_TEXT_SHADER_H

