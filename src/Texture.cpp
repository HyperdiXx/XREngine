#include "Texture.h"

Texture::Texture()
{


}

Texture::~Texture()
{
}

bool Texture::Init(ID3D11Device * device, ID3D11DeviceContext * deviceContext, char * filename)
{
	mTexture = NULL;
	mData = NULL;
	mShaderView = NULL;

	int32 height, width;

	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderDesc;

	if (!LoadTarga(filename, height, width))
	{
		return false;
	}

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

	if (!device->CreateTexture2D(&textureDesc, NULL, &mTexture))
	{
		return false;
	}

	int32 rowPitch = width * 4 * sizeof(unsigned char);
	
	//set texture with read image
	deviceContext->UpdateSubresource(mTexture, 0, NULL, mData, rowPitch, 0);

	//shadedr resource view desc
	shaderDesc.Format = textureDesc.Format;
	shaderDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderDesc.Texture2D.MostDetailedMip = 0;
	shaderDesc.Texture2D.MipLevels = -1;

	if (!device->CreateShaderResourceView(mTexture, &shaderDesc, &mShaderView))
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
	if (mTexture)
	{
		mTexture->Release();
		mTexture = NULL;
	}
	if (mShaderView)
	{
		mShaderView->Release();
		mShaderView = NULL;
	}
	if (mData)
	{
		delete[] mData;
		mData = NULL;
	}

}

ID3D11ShaderResourceView * Texture::GetTexture()
{
	return mShaderView;
}

bool Texture::LoadTarga(char *filename, int32 &w, int32 &h)
{
	char* memoryAl;
	FILE* f;
	TextureHeader pH;

	int32 er;
	int32 bpp, c;

	er = fopen_s(&f, filename, "rb");
	if (er != 0)
	{
		return false;
	}

	c = (int32)fread(&pH, sizeof(TextureHeader), 1, f);
	if (c != 1)
	{
		return false;
	}

	w = (int32)pH.w;
	h = (int32)pH.h;
	bpp = (int32)pH.bpp;

	int32 size = w * h * 4;

	memoryAl = new char[size];
	if (!memoryAl)
	{
		return false;
	}

	c = (int32)fread(memoryAl, 1, size, f);
	if (c != size)
	{
		return false;
	}

	er = fclose(f);
	if(er != 0)
	{
		return false;
	}

	mData = new char[size];
	if (mData)
	{
		return false;
	}

	
	int32 index = 0;

	
	int32 k = (w * h * 4) - (w * 4);

	
	for (size_t j = 0; j < h; ++j)
	{
		for (size_t i = 0; i < w; ++i)
		{
			mData[index + 0] = memoryAl[k + 2];  // Red.
			mData[index + 1] = memoryAl[k + 1];  // Green.
			mData[index + 2] = memoryAl[k + 0];  // Blue
			mData[index + 3] = memoryAl[k + 3];  // Alpha
									
			k += 4;
			index += 4;
		}

		k -= (w * 8);
	}

	// Release the targa image data now that it was copied into the destination array.
	delete[] memoryAl;
	memoryAl = 0;

	return true;
}
