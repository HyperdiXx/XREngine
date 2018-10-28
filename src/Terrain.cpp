#include "Terrain.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

bool Terrain::Init(ID3D11Device *device)
{
	Vertex* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	int32 terrainWidth = 256, terrainHeight = 256, index = 0;
	XMFLOAT4 color;
	real32 posX, posZ;


	color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	mVertexCount = (terrainWidth - 1) * (terrainHeight - 1) * 8;
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

	for (size_t i = 0; i < terrainHeight - 1; ++i)
	{
		for (size_t j = 0; j < terrainWidth - 1; ++j)
		{
			posX = (real32)i;
			posZ = (real32)j + 1;

			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
			indices[index] = index;
			index++;
			
			posX = (real32)i + 1;
			posZ = (real32)j + 1;

			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
			indices[index] = index;
			index++;

			posX = (real32)i + 1;
			posZ = (real32)j + 1;

			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
			indices[index] = index;
			index++;

			posX = (real32)i + 1;
			posZ = (real32)j;

			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
			indices[index] = index;
			index++;

			posX = (real32)i + 1;
			posZ = (real32)j;

			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
			indices[index] = index;
			index++;

			posX = (real32)i;
			posZ = (real32)j;

			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
			indices[index] = index;
			index++;

			posX = (real32)i;
			posZ = (real32)j;

			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
			indices[index] = index;
			index++;

			posX = (real32)i;
			posZ = (real32)j + 1;
			 
			vertices[index].pos = XMFLOAT3(posX, 0.0f, posZ);
			vertices[index].col = color;
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

	device->CreateBuffer(&vertexBufferDesc, &vertexData,&mVertexBuffer);

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

bool Terrain::Render(ID3D11DeviceContext *deviceContext)
{
	UINT offset = 0, stride = sizeof(Vertex);

	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	return true;
}

void Terrain::Release()
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

int Terrain::GetIndexCount()
{
	return (mIndexCount);
}

