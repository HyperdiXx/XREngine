#include "TextureShader.h"

XEngine::TextureShader::TextureShader()
{
}

XEngine::TextureShader::~TextureShader()
{
}

bool 
XEngine::TextureShader::Init(ID3D11Device *device, HWND hWnd)
{
	
	if (!InitShader(device, hWnd, L"../Engine/textureVS.hlsl", L"../Engine/texturePS.hlsl"))
	{
		LOG("Failed to setup texture shaders...\n");
		return false;
	}
	return true;
}

bool 
XEngine::TextureShader::Render(ID3D11DeviceContext *deviceContext, int index, XMMATRIX &world, XMMATRIX &view, XMMATRIX &proj, ID3D11ShaderResourceView *text)
{
	ShaderPass(deviceContext, world, view, proj, text);
	RenderShader(deviceContext, index);
	
	return true;
}

void 
XEngine::TextureShader::Release()
{
	ReleaseShader();
}

bool 
XEngine::TextureShader::InitShader(ID3D11Device *device, HWND hWnd, LPCWSTR hlsl1, LPCWSTR hlsl2)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	ID3D10Blob* vertexBuff;
	ID3D10Blob* pixelBuff;
	ID3D10Blob* errorBuff;
	int32 nElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;

	D3DCompileFromFile(hlsl1, NULL, NULL, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexBuff, &errorBuff);

	D3DCompileFromFile(hlsl2, NULL, NULL, "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelBuff, &errorBuff);

	device->CreateVertexShader(vertexBuff->GetBufferPointer(), vertexBuff->GetBufferSize(), NULL, &mVertexShader);
	device->CreatePixelShader(pixelBuff->GetBufferPointer(), pixelBuff->GetBufferSize(), NULL, &mPixelShader);

	//StartInputLayout
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;


	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	nElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	device->CreateInputLayout(polygonLayout, nElements, vertexBuff->GetBufferPointer(), vertexBuff->GetBufferSize(), &mLayout);

	vertexBuff->Release();
	vertexBuff = NULL;
	pixelBuff->Release();
	pixelBuff = NULL;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(Matrix);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	//create constant buffer in VS
	device->CreateBuffer(&matrixBufferDesc, NULL, &mMatrixBuffer);

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

	device->CreateSamplerState(&samplerDesc, &mSamplerState);


	return true;
}

void 
XEngine::TextureShader::ReleaseShader()
{
	mSamplerState->Release();
	mSamplerState = NULL;

	mMatrixBuffer->Release();
	mMatrixBuffer = NULL;

	mLayout->Release();
	mLayout = NULL;

	mPixelShader->Release();
	mPixelShader = NULL;

	mVertexShader->Release();
	mVertexShader = NULL;
}

bool 
XEngine::TextureShader::ShaderPass(ID3D11DeviceContext *deviceContext, XMMATRIX& world, XMMATRIX& view, XMMATRIX &proj, ID3D11ShaderResourceView * text)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Matrix* ptr;
	int32 num = 0;

	world = DirectX::XMMatrixTranspose(world);
	view = DirectX::XMMatrixTranspose(view);
	proj = DirectX::XMMatrixTranspose(proj);

	deviceContext->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ptr = (Matrix*)mappedResource.pData;

	ptr->world = world;
	ptr->view = view;
	ptr->proj = proj;

	deviceContext->Unmap(mMatrixBuffer, 0);
	deviceContext->VSSetConstantBuffers(num, 1, &mMatrixBuffer);
	deviceContext->PSGetShaderResources(0, 1, &text);

	return true;
}

void 
XEngine::TextureShader::RenderShader(ID3D11DeviceContext *deviceContext, int index)
{
	deviceContext->IASetInputLayout(mLayout);
	deviceContext->VSSetShader(mVertexShader, NULL, 0);
	deviceContext->PSSetShader(mPixelShader, NULL, 0);
	deviceContext->PSSetSamplers(0, 1, &mSamplerState);
	deviceContext->DrawIndexed(index, 0, 0);
}
