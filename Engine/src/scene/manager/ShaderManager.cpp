#include "ShaderManager.h"

using namespace XEngine;

bool ShaderManager::Init(ID3D11Device *device, HWND hWnd)
{
	mColorShader = new ColorShader;
	if (!mColorShader)
	{
		LOG("Failed to init color in shadermanager...\n");
		return false;
	}

	mColorShader->Initialize(device, hWnd);


	mTerrainShader = new TerrainShader;
	if (!mTerrainShader)
	{
		LOG("Failed to init terrain shader...\n");
		return false;
	}

	mTerrainShader->Init(device, hWnd);

	/*mTextureShader = new TextureShader;
	if (!mTextureShader)
	{
		LOG("Failed to init texture in shadermanager...\n");
		return false;
	}

	mTextureShader->Init(device, hWnd);*/

	mTextShader = new TextShader;
	if (!mTextShader)
	{
		LOG("Failed to init text in shadermanager...\n");
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

	if (mTextShader)
	{
		mTextShader->Release();
		delete mTextShader;
		mTextShader = NULL;
	}

	if (mTextureShader)
	{
		mTextureShader->Release();
		delete mTextureShader;
		mTextureShader = NULL;
	}

	if (mTerrainShader)
	{
		mTerrainShader->Release();
		delete mTerrainShader;
		mTerrainShader = NULL;
	}
}

bool ShaderManager::ColorShaderRender(ID3D11DeviceContext* deviceContext, int32 indecs, XMMATRIX & worldMatrix, XMMATRIX & viewMatrix, XMMATRIX & projMatrix)
{
	return mColorShader->Render(deviceContext, indecs, worldMatrix, viewMatrix, projMatrix);
}

bool ShaderManager::FontShaderRender(ID3D11DeviceContext *deviceContext, int32 inde, XMMATRIX &world, XMMATRIX &view, XMMATRIX &proj, ID3D11ShaderResourceView *text, XMFLOAT4 &color)
{
	return mTextShader->Render(deviceContext, inde, world, view, proj, text, color);
}

bool ShaderManager::TextureShaderRender(ID3D11DeviceContext *deviceContext, int32 inde, XMMATRIX & world, XMMATRIX & view, XMMATRIX & proj, ID3D11ShaderResourceView *texture)
{
	return mTextureShader->Render(deviceContext, inde, world, view, proj, texture);
}

bool ShaderManager::TerrainShaderRender(ID3D11DeviceContext *deviceContext, int32 ind, XMMATRIX &world, XMMATRIX &view, XMMATRIX &proj, XMFLOAT4 &ambient, XMFLOAT4 &diffuse, XMFLOAT3 &dir)
{
	return mTerrainShader->Render(deviceContext, ind, world, view, proj, ambient, diffuse, dir);
}

