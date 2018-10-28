#pragma once

#ifndef _TEXT_COMP
#define _TEXT_COMP


#include <DirectXMath.h>
#include <fstream>


using namespace DirectX;

#include "Texture.h"


class TextComponent
{
private:
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
public:
	TextComponent();
	~TextComponent();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, char*, char*, real32, int32);
	void Release();

	ID3D11ShaderResourceView* GetTexture();
	void BuildVertexArray(void*, char*, real32, real32);
	int32 GetSentencePixelLength(char*);
	int32 GetFontHeight();

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

private:
	Font * mFont;
	real32 mTextHeight;
	int32 mSpaceSize;
	Texture * mTexture;
};
#endif // !_TEXT_COMP

