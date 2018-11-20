#pragma once

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../../core/pch/TypesSetup.h"
#include "../objects/Texture.h"
#include "../../Core.h"


namespace XEngine
{
	class XENGINE_API TextureManager
	{
	public:
		TextureManager();
		~TextureManager();


		bool Init(int);
		void Release();

		bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, int, char*);

		ID3D11ShaderResourceView* getTexture(int);

	private:
		int mCount;
		Texture* mTexture;
	};
}


#endif // !TEXTURE_MANAGER_H

