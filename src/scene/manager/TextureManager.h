#pragma once

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../../core/pch/TypesSetup.h"
#include "../objects/Texture.h"
#include "../../Core.h"


namespace XEngine
{
	struct XENGINE_API TextureManager
	{
		TextureManager();
		~TextureManager();


		bool Init(int);
		void Release();

		bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, int, char*);

		ID3D11ShaderResourceView* getTexture(int);

		int mCount;
		Texture* mTexture;
	};
}


#endif // !TEXTURE_MANAGER_H

