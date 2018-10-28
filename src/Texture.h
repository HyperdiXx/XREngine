#pragma once

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "Setup.h"

#include <d3d11.h>
#include <stdio.h>


class Texture
{
private:
	struct TextureHeader
	{
		unsigned short w;
		unsigned short h;
		unsigned char bpp;
		unsigned char data2;
		unsigned char data1[12];
	};
public:

	Texture();
	~Texture();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, char*);
	void Release();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool LoadTarga(char*, int32&, int32&);

private:
	ID3D11Texture2D * mTexture;
	ID3D11ShaderResourceView* mShaderView;
	char* mData;
};
#endif // !_TEXTURE_H

