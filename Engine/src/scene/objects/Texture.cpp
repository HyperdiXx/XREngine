
#include "Texture.h"

using namespace XEngine;

Texture::Texture()
{
	mData = 0;
	mTexture = 0;
	mShaderView = 0;
}


Texture::~Texture()
{
}


bool Texture::Init(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* filename)
{
	bool result;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;


	// Load the targa image data into memory.
	result = LoadTarga(filename, height, width);
	if (!result)
	{
		return false;
	}

	// Setup the description of the texture.
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// Create the empty texture.
	hResult = device->CreateTexture2D(&textureDesc, NULL, &mTexture);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data.
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the targa image data into the texture.
	deviceContext->UpdateSubresource(mTexture, 0, NULL, mData, rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture.
	hResult = device->CreateShaderResourceView(mTexture, &srvDesc, &mShaderView);
	if (FAILED(hResult))
	{
		return false;
	}

	deviceContext->GenerateMips(mShaderView);

	delete[] mData;
	mData = 0;

	return true;
}


void Texture::Release()
{
	if (mShaderView)
	{
		mShaderView->Release();
		mShaderView = 0;
	}

	if (mTexture)
	{
		mTexture->Release();
		mTexture = 0;
	}

	if (mData)
	{
		delete[] mData;
		mData = 0;
	}

	return;
}


ID3D11ShaderResourceView* Texture::GetTexture()
{
	return mShaderView;
}


bool Texture::LoadTarga(const char* filename, int& height, int& width)
{
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TextureHeader targaFileHeader;
	unsigned char* targaImage;

	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	count = (unsigned int)fread(&targaFileHeader, sizeof(TextureHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	height = (int)targaFileHeader.height;
	width = (int)targaFileHeader.width;
	bpp = (int)targaFileHeader.bpp;

	if (bpp != 32)
	{
		return false;
	}

	imageSize = width * height * 4;

	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return false;
	}

	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Allocate memory for the targa destination data.
	mData = new unsigned char[imageSize];
	if (!mData)
	{
		return false;
	}

	// Initialize the index into the targa destination data array.
	index = 0;

	// Initialize the index into the targa image data.
	k = (width * height * 4) - (width * 4);

	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
	for (j = 0; j<height; j++)
	{
		for (i = 0; i<width; i++)
		{
			mData[index + 0] = targaImage[k + 2];  // Red.
			mData[index + 1] = targaImage[k + 1];  // Green.
			mData[index + 2] = targaImage[k + 0];  // Blue
			mData[index + 3] = targaImage[k + 3];  // Alpha

														 // Increment the indexes into the targa data.
			k += 4;
			index += 4;
		}

		// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		k -= (width * 8);
	}

	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = 0;

	return true;
}