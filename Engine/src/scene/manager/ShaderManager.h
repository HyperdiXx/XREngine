#pragma once

#ifndef _SHADER_MANAGER_
#define _SHADER_MANAGER_

#include "../../core/pch/TypesSetup.h"
#include "../../core/GraphicsDevice/d3dclass.h"
#include "shaderset/ColorShader.h"
#include "shaderset/TextShader.h"
#include "shaderset/TextureShader.h"
#include "shaderset/TerrainShader.h"
#include "../../Core.h"

namespace XEngine
{
	class XENGINE_API ShaderManager
	{
	public:
		ShaderManager() {}
		~ShaderManager() {}

		/*static void CreateInstance()
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
		*/
		bool Init(ID3D11Device*, HWND);
		void Release();

		bool ColorShaderRender(ID3D11DeviceContext*, int32, XMMATRIX&, XMMATRIX&, XMMATRIX&);
		bool FontShaderRender(ID3D11DeviceContext*, int32, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*, XMFLOAT4&);
		bool TextureShaderRender(ID3D11DeviceContext*, int32, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*);
		bool TerrainShaderRender(ID3D11DeviceContext*, int32, XMMATRIX&, XMMATRIX&, XMMATRIX&, XMFLOAT4&, XMFLOAT4&, XMFLOAT3&);

	protected:
		//static ShaderManager* mInstance;
	private:

		ColorShader * mColorShader;
		TextShader* mTextShader;
		TextureShader* mTextureShader;
		TerrainShader* mTerrainShader;

	};
}

#endif // !_SHADER_MANAGER_

