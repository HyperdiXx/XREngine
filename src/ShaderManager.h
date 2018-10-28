#pragma once

#ifndef _SHADER_MANAGER_
#define _SHADER_MANAGER_

#include "Setup.h"
#include "d3dclass.h"
#include "ColorShader.h"
#include "TextShader.h"

class ShaderManager
{
public:
	ShaderManager() {}
	ShaderManager(const ShaderManager&) {}
	~ShaderManager() {}

	ShaderManager& operator=(const ShaderManager&) {}

	static void CreateInstance()
	{
		if (mInstance == NULL)
		{
			mInstance = new ShaderManager;
		}
	}

	static ShaderManager* GetObject()
	{
		return mInstance;
	}

	static void DestroyInstance()
	{
		if (mInstance) 
		{
			delete mInstance;
			mInstance = NULL;
		}
	}

	bool Init(ID3D11Device*, HWND);
	void Release();

	bool ColorShaderRender(ID3D11DeviceContext*, int32, XMMATRIX&, XMMATRIX&, XMMATRIX&);
	bool FontShaderRender(ID3D11DeviceContext*, int32, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*, XMFLOAT4&);

protected:
	static ShaderManager* mInstance;
private:

	ColorShader * mColorShader;
	TextShader* mTextShader;

};
#endif // !_SHADER_MANAGER_

