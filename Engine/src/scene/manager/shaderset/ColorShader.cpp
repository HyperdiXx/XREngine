
#include "ColorShader.h"

ColorShader::ColorShader()
{
	mMatrixBuffer = 0;
}

ColorShader::~ColorShader()
{
}

bool ColorShader::Initialize(ID3D11Device * device, HWND hWnd)
{
	InitializeShader(device, hWnd, L"../Engine/colorVS.hlsl", L"../Engine/colorPS.hlsl");
	

	return true;
}

void ColorShader::Shutdown()
{
	ShutdownShader();
}

bool ColorShader::Render(ID3D11DeviceContext* deviceContext, int32 index, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix)
{

	ShaderPass(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	RenderShader(deviceContext, index);


	return true;
}

bool ColorShader::InitializeShader(ID3D11Device* device, HWND hWnd, WCHAR * hlslShader1, WCHAR * hlslShader2)
{
	HRESULT res;
	ID3D10Blob* errorMessage = NULL;
	ID3D10Blob* vertexShaderBuffer = NULL;
	ID3D10Blob* pixelShaderBuffer = NULL;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	res = D3DCompileFromFile(hlslShader1, NULL, NULL, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
	if (FAILED(res))
		return false;
	res = D3DCompileFromFile(hlslShader2, NULL, NULL, "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	if (FAILED(res))
		return false;

	res = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &VertexShader);

	res = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &PixelShader);

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout.
	res = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &mLayout);
	if (FAILED(res))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(Matrices);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	res = device->CreateBuffer(&matrixBufferDesc, NULL, &mMatrixBuffer);
	if (FAILED(res))
	{
		return false;
	}


	return true;
}

void ColorShader::ShutdownShader()
{
	if (mMatrixBuffer)
	{
		mMatrixBuffer->Release();
		mMatrixBuffer = 0;
	}

	if (mLayout)
	{
		mLayout->Release();
		mLayout = 0;
	}

	if (PixelShader)
	{
		PixelShader->Release();
		PixelShader = 0;
	}

	if (VertexShader)
	{
		VertexShader->Release();
		VertexShader = 0;
	}

}

void ColorShader::OutputShaderErrorMessage(ID3D10Blob *, HWND, WCHAR *)
{

}

bool ColorShader::ShaderPass(ID3D11DeviceContext* deviceContext, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	Matrices* dataPtr;
	unsigned int bufferNumber;

	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projMatrix = XMMatrixTranspose(projMatrix);

	//XMMATRIX MVP = worldMatrix * viewMatrix * projMatrix;

	result = deviceContext->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	dataPtr = (Matrices*)mappedResource.pData;
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->proj = projMatrix;

	deviceContext->Unmap(mMatrixBuffer, 0);

	bufferNumber = 0;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &mMatrixBuffer);

	return false;
}

void ColorShader::RenderShader(ID3D11DeviceContext *deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(mLayout);
	deviceContext->VSSetShader(VertexShader, NULL, 0);
	deviceContext->PSSetShader(PixelShader, NULL, 0);
	
	deviceContext->DrawIndexed(indexCount, 0, 0);

}
