#pragma once

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "Setup.h"

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;



class Terrain
{
private:
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT4 col;
	};
public:
	Terrain();
	~Terrain();

	bool Init(ID3D11Device*);
	bool Render(ID3D11DeviceContext*);
	void Release();

	int GetIndexCount();

private:
	ID3D11Buffer * mVertexBuffer, *mIndexBuffer;
	int mVertexCount, mIndexCount;
};
#endif // !_TERRAIN_H

