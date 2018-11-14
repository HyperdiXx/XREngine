#pragma once

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../../core/pch/TypesSetup.h"

#include <d3d11.h>
#include <stdio.h>

namespace XEngine
{
	struct Texture
	{
		struct TextureHeader
		{
			unsigned short width;
			unsigned short height;
			unsigned char bpp;
			unsigned char data2;
			unsigned char data1[12];
		};
	
		Texture();
		~Texture();

		bool Init(ID3D11Device*, ID3D11DeviceContext*, char*);
		void Release();

		ID3D11ShaderResourceView* GetTexture();

		bool LoadTarga(char*, int&, int&);

		ID3D11Texture2D* mTexture;
		ID3D11ShaderResourceView* mShaderView;
		unsigned char* mData;
	};
}

#endif // !_TEXTURE_H

