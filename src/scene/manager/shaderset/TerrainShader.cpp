#include "TerrainShader.h"

XEngine::TerrainShader::TerrainShader()
{
	mVertexShader = 0;
	mPixelShader = 0;
	mInputLayout = 0;
	mSampleState = 0;
	mMatrix = 0;
	mLight = 0;
}

XEngine::TerrainShader::~TerrainShader()
{

}

bool 
XEngine::TerrainShader::Init(ID3D11Device *device, HWND hWnd)
{
	if (!InitShader(device, hWnd, L"../Engine/terrainVS.hlsl", L"../Engine/terrainPS.hlsl"))
	{
		LOG("Failed to INITTERRAIN SHADER\n");
		return false;
	}


	return true;
}

bool 
XEngine::TerrainShader::Render(ID3D11DeviceContext *deviceContext, int indices, XMMATRIX &world, XMMATRIX &view, XMMATRIX &proj, XMFLOAT4 &ambient, XMFLOAT4 &diffuse, XMFLOAT3 &dir)
{
	ShaderPass(deviceContext, world, view, proj, ambient, diffuse, dir);
	RenderShader(deviceContext, indices);

	return true;
}

void 
XEngine::TerrainShader::Release()
{
	ReleaseShader();
}

bool 
XEngine::TerrainShader::InitShader(ID3D11Device *device, HWND hWnd, WCHAR * vertex, WCHAR *pixel)
{
	HRESULT res;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc;
	
	res = D3DCompileFromFile(vertex, NULL, NULL, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer,
		&errorMessage);

	if (FAILED(res))
	{

		LOG("%s", errorMessage);

		return false;
	}

	res = D3DCompileFromFile(pixel, NULL, NULL, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer,
		&errorMessage);

	if (FAILED(res))
	{

		LOG("%s", errorMessage);

		return false;
	}


	device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &mVertexShader);
	device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &mPixelShader);

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "NORMAL";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	res = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &mInputLayout);
	if (FAILED(res))
	{
		LOG("FAILED to create InputLayout\n");
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	device->CreateSamplerState(&samplerDesc, &mSampleState);


	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(Matrix);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	res = device->CreateBuffer(&matrixBufferDesc, NULL, &mMatrix);
	if (FAILED(res))
	{
		return false;
	}

	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(Light);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	res = device->CreateBuffer(&lightBufferDesc, NULL, &mLight);
	if (FAILED(res))
	{
		return false;
	}


	return true;
}

void 
XEngine::TerrainShader::ReleaseShader()
{
	mLight->Release();
	mLight = 0;

	mMatrix->Release();
	mMatrix = 0;

	mSampleState->Release();
	mSampleState = 0;

	mInputLayout->Release();
	mInputLayout = 0;

	mVertexShader->Release();
	mVertexShader = 0;

	mPixelShader->Release();
	mPixelShader = 0;
		
}

bool 
XEngine::TerrainShader::ShaderPass(ID3D11DeviceContext *deviceContext, XMMATRIX &world, XMMATRIX &view, XMMATRIX &proj, XMFLOAT4 &ambient, XMFLOAT4 &diffuse, XMFLOAT3 &dir)
{
	D3D11_MAPPED_SUBRESOURCE map;
	Matrix* ptr1;
	Light* ptr2;

	world = XMMatrixTranspose(world);
	view = XMMatrixTranspose(view);
	proj = XMMatrixTranspose(proj);

	deviceContext->Map(mMatrix, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);

	ptr1 = static_cast<Matrix*>(map.pData);

	ptr1->world = world;
	ptr1->view = view;
	ptr1->proj = proj;

	deviceContext->Unmap(mMatrix, 0);

	unsigned int bufNum = 0;

	deviceContext->VSSetConstantBuffers(bufNum, 1, &mMatrix);
	
	//lightmap
	deviceContext->Map(mLight, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	
	ptr2 = static_cast<Light*>(map.pData);

	
	ptr2->ambientCol = ambient;
	ptr2->diffuseCol = diffuse;
	ptr2->direction = dir;
	ptr2->padding = 0.0f;

	deviceContext->Unmap(mLight, 0);

	bufNum = 0;

	deviceContext->PSSetConstantBuffers(bufNum, 1, &mLight);

	return true;
}

void 
XEngine::TerrainShader::RenderShader(ID3D11DeviceContext *deviceContext, int indices)
{
	deviceContext->IASetInputLayout(mInputLayout);

	deviceContext->VSSetShader(mVertexShader, NULL, 0);
	deviceContext->PSSetShader(mPixelShader, NULL, 0);

	deviceContext->PSSetSamplers(0, 1, &mSampleState);

	deviceContext->DrawIndexed(indices, 0, 0);

}
