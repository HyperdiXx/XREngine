#include "TextureManager.h"

XEngine::TextureManager::TextureManager()
{

}

XEngine::TextureManager::~TextureManager()
{

}

bool 
XEngine::TextureManager::Init(int n)
{
	mCount = n;

	mTexture = new Texture[mCount];
	if (!mTexture)
	{
		LOG("Failed to load textures...\n");
		return false;
	}
		
	return true;
}

void 
XEngine::TextureManager::Release()
{
	for (size_t i = 0; i < mCount; ++i)
	{
		mTexture[i].Release();
	}
	delete[] mTexture;
	mTexture = NULL;
}

bool 
XEngine::TextureManager::LoadTexture(ID3D11Device *device, ID3D11DeviceContext *deviceContext, int id, char *filename)
{
	mTexture[id].Init(device, deviceContext, filename);
		
	return true;
}

ID3D11ShaderResourceView * 
XEngine::TextureManager::getTexture(int id)
{
	return mTexture[id].GetTexture();
}
