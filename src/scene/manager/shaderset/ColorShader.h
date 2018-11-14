#pragma once

#ifndef _COLOR_SHADER_
#define _COLOR_SHADER_

#include "../../../core/pch/TypesSetup.h"
#include "../../../Core.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>


using namespace DirectX;

struct XENGINE_API ColorShader
{

	struct Matrices
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX proj;
		XMMATRIX ModelViewProj;
	};

	ColorShader();
	~ColorShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int32, XMMATRIX&, XMMATRIX&, XMMATRIX&);

	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool ShaderPass(ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX&);
	void RenderShader(ID3D11DeviceContext*, int);

	ID3D11InputLayout* mLayout;

	ID3D11PixelShader* PixelShader;
	ID3D11VertexShader* VertexShader;
	ID3D11Buffer* mMatrixBuffer;


};
#endif // !_COLOR_SHADER_
