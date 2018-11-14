#include "Text.h"

Text::Text()
{
	
}

Text::~Text()
{
}

bool Text::Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext, 
	int32 W, int32 H, int32 maxL, bool shadow, TextComponent *textComp, const char *text, int32 positionX, int32 positionY,
	real32 r, real32 g, real32 b)
{

	mScreenWidth = W;
	mScreenHeight = H;
	mMaxLength = maxL;
	mShadow = shadow;

	if (!InitializeSentence(device, deviceContext, textComp, text, positionX, positionY, r, g, b))
	{
		return false;
	}


	return true;
}

void Text::Release()
{
	mVertexBuffer->Release();
	mVertexBuffer = NULL;

	mIndexBuffer->Release();
	mIndexBuffer = NULL;

	mVertexBuffer2->Release();
	mVertexBuffer2 = NULL;

	mIndexBuffer2->Release();
	mIndexBuffer2 = NULL;
}

void Text::Render(ID3D11DeviceContext *deviceContext, ShaderManager *shaderManager, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &orthoMatrix, ID3D11ShaderResourceView *fontTexture)
{
	RenderSentence(deviceContext, shaderManager, worldMatrix, viewMatrix, orthoMatrix, fontTexture);
}


bool Text::InitializeSentence(ID3D11Device *device, ID3D11DeviceContext *deviceContext, TextComponent *textComp, const char *text, int32 posX, int32 posY, real32 r, real32 g, real32 b)
{
	Vertex *sent;
	unsigned long *index;

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	mVertexCount = mMaxLength * 6;
	mIndexCount = mMaxLength * 6;

	sent = new Vertex[mVertexCount];
	if (!sent)
	{
		return false;
	}

	index = new unsigned long[mIndexCount];
	if (!index)
	{
		return false;
	}

	memset(sent, 0, (sizeof(Vertex) * mVertexCount));

	for (size_t i = 0; i < mIndexCount; ++i)
	{
		index[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = sent;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if (!device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = index;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (!device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer))
	{
		return false;
	}

	if (mShadow)
	{
		if (!device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer2))
		{
			return false;
		}
	
		if (!device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer2))
		{
			return false;
		}
	
	}

	delete[] sent;
	sent = 0;

	delete[] index;
	index = 0;

	if (!UpdateSentence(deviceContext, textComp, text, posX, posY, r, g, b))
	{
		return false;
	}
	
	return true;
}

bool Text::UpdateSentence(ID3D11DeviceContext *deviceContext, TextComponent *textComp, const char *text, int32 posX, int32 posY, float r, float g, float b)
{
	int nLetters = (int32)strlen(text);
	Vertex *vertex;
	int drawX, drawY;
	D3D11_MAPPED_SUBRESOURCE sub;
	void* verticesPtr;
	XMFLOAT4 px;

	mPixelColor = XMFLOAT4(1.0f, 1.0f, 0.0, 1.0f);

	//if (nLetters > mMaxLength)
		//return false;

	vertex = new Vertex[mVertexCount];
	if (!vertex)
	{
		return false;
	}

	memset(vertex, 0, sizeof(Vertex) * mVertexCount);

	drawX = (real32)(((mScreenWidth / 2) * - 1) + posX);
	drawY = (real32)((mScreenHeight / 2) - posY);

	textComp->BuildVertexArray((void*)vertex, text, drawX, drawY);

	if (!deviceContext->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub))
	{
		return false;
	}

	verticesPtr = (void*)sub.pData;

	memcpy(verticesPtr, (void*)vertex, (sizeof(Vertex) * mVertexCount));

	deviceContext->Unmap(mVertexBuffer, 0);

	if (mShadow)
	{
		memset(vertex, 0, (sizeof(Vertex) * mVertexCount));

		drawX = (float)((((mScreenWidth / 2) * -1) + posX) + 2);
		drawY = (float)(((mScreenHeight / 2) - posY) - 2);
		textComp->BuildVertexArray((void*)vertex, text, drawX, drawY);

		if(!deviceContext->Map(mVertexBuffer2, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub))
		{
			return false;
		}
		verticesPtr = (void*)sub.pData;
		memcpy(verticesPtr, (void*)vertex, (sizeof(Vertex) * mVertexCount));
		deviceContext->Unmap(mVertexBuffer2, 0);
	}

	
	delete[] vertex;
	vertex = NULL;

		
	return true;
}


void Text::RenderSentence(ID3D11DeviceContext *deviceContext, ShaderManager *shM, XMMATRIX &worldMatrix, XMMATRIX &view, XMMATRIX &orthoMatrix, ID3D11ShaderResourceView *fontTexture)
{
	unsigned int stride, offset;
	XMFLOAT4 shadowColor;


	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex);
	offset = 0;

	if (mShadow)
	{
		shadowColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

		deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer2, &stride, &offset);
		deviceContext->IASetIndexBuffer(mIndexBuffer2, DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		shM->FontShaderRender(deviceContext, mIndexCount, worldMatrix, view, orthoMatrix, fontTexture, shadowColor);
	}
	

	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shM->FontShaderRender(deviceContext, mIndexCount, worldMatrix, view, orthoMatrix, fontTexture, mPixelColor);

}

