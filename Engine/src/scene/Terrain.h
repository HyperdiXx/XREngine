#pragma once

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <stdio.h>
#include <fstream>

#include <d3d11.h>
#include <DirectXMath.h>


#include "../core/pch/TypesSetup.h"
#include "../Core.h"

using namespace DirectX;


namespace XEngine
{
	struct XENGINE_API Terrain
	{
		struct Vertex
		{
			XMFLOAT3 pos;
			XMFLOAT3 normal;
		};
		struct HeightMap
		{
			float x, y, z;
			float nx, ny, nz;
		};
		struct Model
		{
			float x, y, z;
			//float tu, tv;
		};

		Terrain();
		~Terrain();

		bool Init(ID3D11Device*, const char*);
		bool Render(ID3D11DeviceContext*);
		void Release();


		void NormalizeHeightMap();
		bool CalculateNormals();
		bool LoadSetupFile(const char*);
		bool LoadBitmapHeight();
		bool LoadHeightMap(const char*);
		void ReleaseHeightMap();
		void SetTerrainCoordinates();
		bool BuildTerrainModel();
		void ReleaseModel();

		bool InitializeBuffers(ID3D11Device*);
		void ReleaseBuffers();
		void RenderBuffers(ID3D11DeviceContext*);


		int GetIndexCount();



		int mTerrainHeight, mTerrainWidth;
		float mHeightScale;
		char* mTerrainFilename;
		HeightMap* mHeightMap;
		Model* mTerrainModel;
		ID3D11Buffer * mVertexBuffer, *mIndexBuffer;
		int mVertexCount, mIndexCount;
	};
}
#endif // !_TERRAIN_H

