#include "ShaderManager.h"

bool ShaderManager::Init(ID3D11Device *device, HWND hWnd)
{
	mColorShader = new ColorShader;
	if (!mColorShader)
	{
		return false;
	}

	mColorShader->Initialize(device, hWnd);


	mTextShader = new TextShader;
	if (!mTextShader)
	{
		return false;
	}

	mTextShader->Init(device, hWnd);


	return (true);
}

void ShaderManager::Release()
{
	if (mColorShader)
	{
		mColorShader->Shutdown();
		delete mColorShader;
		mColorShader = NULL;
	}
}

bool ShaderManager::ColorShaderRender(ID3D11DeviceContext* deviceContext, int32 indecs, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projMatrix)
{
	return mColorShader->Render(deviceContext, indecs, worldMatrix, viewMatrix, projMatrix);
}

bool ShaderManager::FontShaderRender(ID3D11DeviceContext *, int32, XMMATRIX &, XMMATRIX &, XMMATRIX &, ID3D11ShaderResourceView *, XMFLOAT4 &)
{
	return false;
}
