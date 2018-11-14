#include "Terrain.h"

XEngine::Terrain::Terrain()
{
	mVertexBuffer = 0;
	mIndexBuffer = 0;
	mTerrainFilename = 0;
	mHeightMap = 0;
	mTerrainModel = 0;
}

XEngine::Terrain::~Terrain()
{

}

bool XEngine::Terrain::Init(ID3D11Device *device, const char *setupFilename)
{
	

	/*if (LoadSetupFile(setupFilename))
	{
		LOG("SetupFile\n");
	}

	if (LoadBitmapHeight())
	{
		LOG("SetupBitmap\n");
	}

	SetTerrainCoordinates();
	LOG("Setup terrainCoordinates\n");

	if(BuildTerrainModel())
	{
		LOG("BuildTerrainModel\n");
	}
	
	ReleaseHeightMap();
	LOG("ReleaseHeightMap\n");
	
	if (InitializeBuffers(device))
	{
		LOG("InitializeBuffersTerrain\n");
	}

	ReleaseModel();
	LOG("Release model\n");*/
	if (!LoadHeightMap(setupFilename))
	{
		LOG("Failed to load HeightMap");
		return false;
	}

	NormalizeHeightMap();

	if (CalculateNormals())
	{
		LOG("CalculateNormals\n");
	}

	if (!InitializeBuffers(device))
	{
		LOG("FailedInitializeBuffersTerrain\n");
	}

	return true;
}

bool XEngine::Terrain::Render(ID3D11DeviceContext *deviceContext)
{
	RenderBuffers(deviceContext);

	return true;
}

void XEngine::Terrain::Release()
{
	ReleaseBuffers();
	ReleaseModel();
	ReleaseHeightMap();
}

void XEngine::Terrain::NormalizeHeightMap()
{

	for (size_t j = 0; j < mTerrainHeight; ++j)
	{
		for (size_t i = 0; i < mTerrainWidth; ++i)
		{
			mHeightMap[(mTerrainHeight * j) + i].y /= 15.0f;
		}
	}

}

bool XEngine::Terrain::CalculateNormals()
{

	float vertex1[3], vertex2[3], vertex3[3];
	float vector1[3], vector2[3], sum[3], l;

	Model* normals = new Model[(mTerrainHeight - 1) * (mTerrainWidth - 1)];
	if (!normals)
	{
		LOG("Failed to init normals");
		return false;
	}

	for (size_t j = 0; j < mTerrainHeight - 1; ++j)
	{
		for (size_t i = 0; i < mTerrainWidth - 1; ++i)
		{
			int index1 = (j * mTerrainHeight) + 1;
			int index2 = (j * mTerrainHeight) + (i + 1);
			int index3 = ((j+1) * mTerrainHeight) + i; 

			vertex1[0] = mHeightMap[index1].x;
			vertex1[1] = mHeightMap[index1].y;
			vertex1[2] = mHeightMap[index1].z;

			vertex2[0] = mHeightMap[index2].x;
			vertex2[1] = mHeightMap[index2].y;
			vertex2[2] = mHeightMap[index2].z;

			vertex3[0] = mHeightMap[index3].x;
			vertex3[1] = mHeightMap[index3].y;
			vertex3[2] = mHeightMap[index3].z;

			vector1[0] = vertex1[0] - vertex3[0];
			vector1[1] = vertex1[1] - vertex3[1];
			vector1[2] = vertex1[2] - vertex3[2];

			vector2[0] = vertex3[0] - vertex2[0];
			vector2[1] = vertex3[1] - vertex2[1];
			vector2[2] = vertex3[2] - vertex2[2];

			int index = (j * (mTerrainHeight-1)) + i;

			normals[index].x = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
			normals[index].y = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
			normals[index].z = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
		}
	}
	
	for (size_t j = 0; j < mTerrainHeight; ++j)
	{
		for (size_t i = 0; i < mTerrainWidth; ++i)
		{
			sum[0] = 0.0f;
			sum[1] = 0.0f;
			sum[2] = 0.0f;

			int count = 0;

			// Bottom left face.
			if (((i - 1) >= 0) && ((j - 1) >= 0))
			{
				int index = ((j - 1) * (mTerrainHeight - 1)) + (i - 1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Bottom right face.
			if ((i < (mTerrainWidth - 1)) && ((j - 1) >= 0))
			{
				int index = ((j - 1) * (mTerrainHeight - 1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper left face.
			if (((i - 1) >= 0) && (j < (mTerrainHeight - 1)))
			{
				int index = (j * (mTerrainHeight - 1)) + (i - 1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper right face.
			if ((i < (mTerrainWidth - 1)) && (j < (mTerrainHeight - 1)))
			{
				int index = (j * (mTerrainHeight - 1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Take the average of the faces touching this vertex.
			sum[0] = (sum[0] / (float)count);
			sum[1] = (sum[1] / (float)count);
			sum[2] = (sum[2] / (float)count);

			// Calculate the length of this normal.
			l = sqrt((sum[0] * sum[0]) + (sum[1] * sum[1]) + (sum[2] * sum[2]));

			// Get an index to the vertex location in the height map array.
			int index = (j * mTerrainHeight) + i;

			// Normalize the final shared normal for this vertex and store it in the height map array.
			mHeightMap[index].nx = (sum[0] / l);
			mHeightMap[index].ny = (sum[1] / l);
			mHeightMap[index].nz = (sum[2] / l);
		}
	}

	delete[] normals;
	normals = 0;

	return true;
}

bool XEngine::Terrain::LoadSetupFile(const char *name)
{
	int stringLength = 256;
	char inp;
	std::ifstream f(name);
	
	mTerrainFilename = new char[stringLength];
	if (!mTerrainFilename)
	{
		LOG("Failed setup terrainFilename");
		return false;
	}

	f.get(inp);
	while (inp != ':')
	{
		f.get(inp);
	}

	f >> mTerrainFilename;

	f.get(inp);
	while (inp != ':')
	{
		f.get(inp);
	}

	f >> mTerrainHeight;

	f.get(inp);
	while (inp != ':')
	{
		f.get(inp);
	}

	f >> mTerrainWidth;

	f.get(inp);
	while (inp != ':')
	{
		f.get(inp);
	}

	f >> mHeightScale;

	f.close();

	return true;
}

bool XEngine::Terrain::LoadBitmapHeight()
{
	FILE* ptr = nullptr;
	unsigned long long count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char* bitmapImage;
	unsigned char height;
	int imageSize;

	mHeightMap = new HeightMap[mTerrainWidth * mTerrainHeight];
	if (!mHeightMap)
	{
		LOG("Heightmap read...\n");
		return false;
	}

	//fopen_s(&ptr, mTerrainFilename, "rb");
	//LOG("Completely read file in binary");

	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, ptr);
	if (!count)
	{
		LOG("Read file header suc...\n");
		return false;
	}

	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, ptr);
	if (!count)
	{
		LOG("Read info header...\n");
		return false;
	}

	if ((bitmapInfoHeader.biHeight != mTerrainHeight) || (bitmapInfoHeader.biWidth != mTerrainWidth))
	{
		return false;
	}

	imageSize = mTerrainHeight * ((mTerrainWidth * 3) + 1);

	bitmapImage = new unsigned char[imageSize];
	if (!bitmapImage)
	{
		LOG("FAILED to read BitnapImage");
		return false;
	}

	fseek(ptr, bitmapFileHeader.bfOffBits, SEEK_SET);
	count = fread(bitmapImage, 1, imageSize, ptr);
	if (count != imageSize)
	{
		LOG("Failed to read into bitmapdata");
		return false;
	}

	fclose(ptr);

	int index = 0;
	int k = 0;

	for (size_t j = 0; j < mTerrainHeight; ++j)
	{
		for (size_t i = 0; i < mTerrainWidth; ++i)
		{
			// Bitmaps are upside down so load bottom to top into the height map array.
			index = (mTerrainWidth * (mTerrainHeight - 1 - j)) + i;

			// Get the grey scale pixel value from the bitmap image data at this location.
			height = bitmapImage[k];

			// Store the pixel value as the height at this point in the height map array.
			mHeightMap[index].y = (float)height;

			// Increment the bitmap image data index.
			k += 3;
		}

		// Compensate for the extra byte at end of each line in non-divide by 2 bitmaps (eg. 257x257).
		k++;
	}

	
	delete[] bitmapImage;
	bitmapImage = NULL;


	return true;
}

bool XEngine::Terrain::LoadHeightMap(const char *filename)
{
	FILE* filePtr;
	int error;
	unsigned int count;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int imageSize, k, index;
	unsigned char* bitmapImage;
	unsigned char height;

	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	mTerrainWidth = bitmapInfoHeader.biWidth;
	mTerrainHeight = bitmapInfoHeader.biHeight;

	imageSize = mTerrainWidth * mTerrainHeight * 3;

	bitmapImage = new unsigned char[imageSize];
	if (!bitmapImage)
	{
		return false;
	}

	
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	count = fread(bitmapImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	mHeightMap = new HeightMap[mTerrainWidth * mTerrainHeight];
	if (!mHeightMap)
	{
		return false;
	}

	// Initialize the position in the image data buffer.
	k = 0;

	// Read the image data into the height map.
	for (size_t j = 0; j < mTerrainHeight; ++j)
	{
		for (size_t i = 0; i < mTerrainWidth; ++i)
		{
			height = bitmapImage[k];

			index = (mTerrainHeight * j) + i;

			mHeightMap[index].x = (float)i;
			mHeightMap[index].y = (float)height;
			mHeightMap[index].z = (float)j;

			k += 3;
		}
	}

	delete[] bitmapImage;
	bitmapImage = 0;

	return true;
}

void XEngine::Terrain::ReleaseHeightMap()
{
	delete[] mHeightMap;
	mHeightMap = NULL;
}

void XEngine::Terrain::SetTerrainCoordinates()
{
	for (size_t i = 0; i < mTerrainHeight; ++i)
	{
		for (size_t j = 0; j < mTerrainWidth; ++j)
		{
			int index = (mTerrainWidth * j) + i;

			mHeightMap[index].x = (float)i;
			mHeightMap[index].z = -(float)j;

			mHeightMap[index].z += (float)(mTerrainHeight - 1);

			mHeightMap[index].y /= mHeightScale;
		}
	}
		
}

bool XEngine::Terrain::BuildTerrainModel()
{
	int index1, index2, index3, index4;
	int numVertexOfTriangle = 6;

	mVertexCount = (mTerrainHeight - 1) * (mTerrainWidth - 1) * numVertexOfTriangle;

	mTerrainModel = new Model[mVertexCount];
	if (!mTerrainModel)
	{
		LOG("FAILED to setup terrain model");
		return false;
	}
	
	int index = 0;

	for (size_t j = 0; j < (mTerrainHeight - 1); ++j)
	{
		for (size_t i = 0; i < (mTerrainWidth - 1); ++i)
		{
			index1 = (mTerrainWidth * j) + i;
			index2 = (mTerrainWidth * j) + (i + 1);
			index3 = (mTerrainWidth * (j + 1)) + i;
			index4 = (mTerrainWidth * (j + 1)) + (i + 1);

			//setup first triangle in the quad
			mTerrainModel[index].x = mHeightMap[index1].x;
			mTerrainModel[index].y = mHeightMap[index1].y;
			mTerrainModel[index].z = mHeightMap[index1].z;
			//mTerrainModel[index].tu = 0.0f;
			//mTerrainModel[index].tv = 0.0f;
			index++;

			mTerrainModel[index].x = mHeightMap[index2].x;
			mTerrainModel[index].y = mHeightMap[index2].y;
			mTerrainModel[index].z = mHeightMap[index2].z;
			//mTerrainModel[index].tu = 1.0f;
			//mTerrainModel[index].tv = 0.0f;
			index++;

			mTerrainModel[index].x = mHeightMap[index3].x;
			mTerrainModel[index].y = mHeightMap[index3].y;
			mTerrainModel[index].z = mHeightMap[index3].z;
			//mTerrainModel[index].tu = 0.0f;
			//mTerrainModel[index].tv = 1.0f;
			index++;

			//setup second triangle in the quad
			mTerrainModel[index].x = mHeightMap[index3].x;
			mTerrainModel[index].y = mHeightMap[index3].y;
			mTerrainModel[index].z = mHeightMap[index3].z;
			//mTerrainModel[index].tu = 0.0f;
			//mTerrainModel[index].tv = 1.0f;
			index++;

			mTerrainModel[index].x = mHeightMap[index2].x;
			mTerrainModel[index].y = mHeightMap[index2].y;
			mTerrainModel[index].z = mHeightMap[index2].z;
			//mTerrainModel[index].tu = 1.0f;
			//mTerrainModel[index].tv = 0.0f;
			index++;

			mTerrainModel[index].x = mHeightMap[index4].x;
			mTerrainModel[index].y = mHeightMap[index4].y;
			mTerrainModel[index].z = mHeightMap[index4].z;
			//mTerrainModel[index].tu = 1.0f;
			//mTerrainModel[index].tv = 1.0f;
			index++;
			
		}
	}



	return false;
}

void XEngine::Terrain::ReleaseModel()
{
	delete[] mTerrainModel;
	mTerrainModel = NULL;
}

bool XEngine::Terrain::InitializeBuffers(ID3D11Device *device)
{
	Vertex* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	XMFLOAT4 color;
	real32 posX, posZ;

	color = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.5f);

	mVertexCount = (mTerrainWidth - 1) * (mTerrainHeight - 1) * 6;
	mIndexCount = mVertexCount;

	vertices = new Vertex[mVertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[mIndexCount];
	if (!indices)
	{
		return false;
	}

	int index = 0;


	for (size_t j = 0; j < (mTerrainHeight - 1); ++j)
	{
		for (size_t i = 0; i< (mTerrainWidth - 1); ++i)
		{
			int index1 = (mTerrainHeight * j) + i;          // Bottom left.
			int index2 = (mTerrainHeight * j) + (i + 1);      // Bottom right.
			int index3 = (mTerrainHeight * (j + 1)) + i;      // Upper left.
			int index4 = (mTerrainHeight * (j + 1)) + (i + 1);  // Upper right.

															 // Upper left.
			vertices[index].pos = XMFLOAT3(mHeightMap[index3].x, mHeightMap[index3].y, mHeightMap[index3].z);
			vertices[index].normal = XMFLOAT3(mHeightMap[index3].nx, mHeightMap[index3].ny, mHeightMap[index3].nz);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].pos = XMFLOAT3(mHeightMap[index4].x, mHeightMap[index4].y, mHeightMap[index4].z);
			vertices[index].normal = XMFLOAT3(mHeightMap[index4].nx, mHeightMap[index4].ny, mHeightMap[index4].nz);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].pos = XMFLOAT3(mHeightMap[index1].x, mHeightMap[index1].y, mHeightMap[index1].z);
			vertices[index].normal = XMFLOAT3(mHeightMap[index1].nx, mHeightMap[index1].ny, mHeightMap[index1].nz);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].pos = XMFLOAT3(mHeightMap[index1].x, mHeightMap[index1].y, mHeightMap[index1].z);
			vertices[index].normal = XMFLOAT3(mHeightMap[index1].nx, mHeightMap[index1].ny, mHeightMap[index1].nz);
			indices[index] = index;
			index++;

			// Upper right.
			vertices[index].pos = XMFLOAT3(mHeightMap[index4].x, mHeightMap[index4].y, mHeightMap[index4].z);
			vertices[index].normal = XMFLOAT3(mHeightMap[index4].nx, mHeightMap[index4].ny, mHeightMap[index4].nz);
			indices[index] = index;
			index++;

			// Bottom right.
			vertices[index].pos = XMFLOAT3(mHeightMap[index2].x, mHeightMap[index2].y, mHeightMap[index2].z);
			vertices[index].normal = XMFLOAT3(mHeightMap[index2].nx, mHeightMap[index2].ny, mHeightMap[index2].nz);
			indices[index] = index;
			index++;
		}
	}


	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer);

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer);

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void XEngine::Terrain::ReleaseBuffers()
{
	if (mIndexBuffer)
	{
		mIndexBuffer->Release();
		mIndexBuffer = 0;
	}

	if (mVertexBuffer)
	{
		mVertexBuffer->Release();
		mVertexBuffer = 0;
	}
}

void XEngine::Terrain::RenderBuffers(ID3D11DeviceContext *deviceContext)
{
	UINT offset = 0, stride = sizeof(Vertex);

	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

int XEngine::Terrain::GetIndexCount()
{
	return (mIndexCount);
}

