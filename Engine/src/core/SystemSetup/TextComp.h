#pragma once

#ifndef _TEXT_COMP
#define _TEXT_COMP


#include <DirectXMath.h>
#include <fstream>

#include "../../scene/objects/Texture.h"
#include "../../Core.h"

using namespace DirectX;
using namespace XEngine;

struct XENGINE_API TextComponent
{
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 text;
	};
	struct Font
	{
		float left;
		float right;
		int size;
	};

	TextComponent();
	~TextComponent();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, const char*, const char*, real32, int32);
	void Release();

	ID3D11ShaderResourceView* GetTexture();
	void BuildVertexArray(void*, const char*, real32, real32);
	int32 GetSentencePixelLength(char*);
	int32 GetFontHeight();

	bool LoadFontData(const char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*);
	void ReleaseTexture();

	Font * mFont;
	real32 mTextHeight;
	int32 mSpaceSize;
	Texture * mTexture;
};
#endif // !_TEXT_COMP

