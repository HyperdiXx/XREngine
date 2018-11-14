#pragma once

#ifndef _TEXT_H
#define _TEXT_H

#include "../../core/SystemSetup/TextComp.h"
#include "../manager/ShaderManager.h"

struct TextComponent;

struct Text
{

	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 text;
	};

	Text();
	~Text();

	bool Init(ID3D11Device*, ID3D11DeviceContext*, int32, int32, int32, bool, TextComponent*, char*, int32, int32, real32, real32, real32);
	void Release();
	void Render(ID3D11DeviceContext*, ShaderManager*, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*);

	bool UpdateSentence(ID3D11DeviceContext*, TextComponent*, char*, int32, int32, float, float, float);


	bool InitializeSentence(ID3D11Device*, ID3D11DeviceContext*, TextComponent*, char*, int32, int32, real32, real32, real32);
	void RenderSentence(ID3D11DeviceContext*, ShaderManager*, XMMATRIX&, XMMATRIX&, XMMATRIX&, ID3D11ShaderResourceView*);

	ID3D11Buffer *mVertexBuffer, *mIndexBuffer, *mVertexBuffer2, *mIndexBuffer2;
	int32 mScreenWidth, mScreenHeight, mMaxLength, mVertexCount, mIndexCount;
	bool mShadow;
	XMFLOAT4 mPixelColor;

};
#endif // !_TEXT_H

