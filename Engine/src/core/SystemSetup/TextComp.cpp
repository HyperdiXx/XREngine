#include "TextComp.h"

TextComponent::TextComponent()
{
}

TextComponent::~TextComponent()
{
}

bool TextComponent::Init(ID3D11Device *device, ID3D11DeviceContext *deviceContext, const char *text, const char *texture, real32 textHeight, int32 spaceSize)
{
	mTextHeight = textHeight;
	mSpaceSize = spaceSize;

	if(!LoadFontData(text))
	{
		return false;
	}

	if(!LoadTexture(device, deviceContext, texture))
	{
		return false;
	}

	return true;
}

void TextComponent::Release()
{
	ReleaseTexture();
	ReleaseFontData();
}

ID3D11ShaderResourceView * TextComponent::GetTexture()
{
	return mTexture->GetTexture();
}

void TextComponent::BuildVertexArray(void *vertex, const char *words, real32 drawX, real32 drawY)
{
	Vertex* v;
	v = (Vertex*)vertex;

	int32 numLetters = (int32)strlen(words);
	int32 index = 0;
	int32 letter;


	for (size_t i = 0; i < numLetters; ++i)
	{
		letter = ((int32)words[i]) - 32;

		if (letter == 0)
		{
			drawX = drawY + (real32)mSpaceSize;
		}
		else 
		{
			v[index].pos = XMFLOAT3(drawX, drawY, 0.0f); // 0.0f, 1.0f
			v[index].text = XMFLOAT2(mFont[letter].left, 0.0f);
			index++;

			v[index].pos = XMFLOAT3(drawX + mFont[letter].size, (drawY - mTextHeight), 0.0f);//1.0f, 0.0f
			v[index].text = XMFLOAT2(mFont[letter].right, 1.0f);
			index++;

			v[index].pos = XMFLOAT3(drawX, drawY - mTextHeight, 0.0f);
			v[index].text = XMFLOAT2(mFont[letter].left, 1.0f);
			index++;

			v[index].pos = XMFLOAT3(drawX, drawY, 0.0f);
			v[index].text = XMFLOAT2(mFont[letter].left, 0.0f);
			index++;

			v[index].pos = XMFLOAT3(drawX + mFont[letter].size, drawY, 0.0f);
			v[index].text = XMFLOAT2(mFont[letter].right, 0.0f);
			index++;

			v[index].pos = XMFLOAT3(drawX + mFont[letter].size, drawY - mTextHeight, 0.0f);
			v[index].text = XMFLOAT2(mFont[letter].left, 1.0f);
			index++;

			drawX = drawX + mFont[letter].size + 1.0f;
		}
	}

	return;
}

int32 TextComponent::GetSentencePixelLength(char *words)
{
	int32 pixelLength = 0, n, letter;

	n = (int32)strlen(words);
	for (size_t i = 0; i < n; ++i)
	{
		letter = ((int32)words[i]) - 32;

		// If the letter is a space then count it as three pixels.
		if (letter == 0)
		{
			pixelLength += mSpaceSize;
		}
		else
		{
			pixelLength += (mFont[letter].size + 1);
		}
	}


	return (pixelLength);
}

int32 TextComponent::GetFontHeight()
{
	return (int32)mTextHeight;
}

bool TextComponent::LoadFontData(const char *filename)
{
	std::ifstream f;
	mFont = new Font[95];
	if (!mFont)
		return false;

	f.open(filename);
	if (f.fail())
	{
		return false;
	}

	char t;

	// TODO: (Vlad)
	// Test if works without double fget
	///////////////////////////////////

	for (size_t i = 0; i < 95; ++i)
	{
		f.get(t);
		while (t != ' ')
		{
			f.get(t);
		}
		/*f.get(t);
		while (t != ' ')
		{
			f.get(t);
		}*/

		f >> mFont[i].left;
		f >> mFont[i].right;
		f >> mFont[i].size;
	}

	f.close();

	return true;
}

void TextComponent::ReleaseFontData()
{
	if (mFont)
	{
		delete [] mFont;
		mFont = NULL;
	}
}

bool TextComponent::LoadTexture(ID3D11Device *device, ID3D11DeviceContext *deviceContext, const char *filename)
{
	mTexture = new Texture;
	if(!mTexture)
	{
		return false;
	}

	if (!mTexture->Init(device, deviceContext, filename))
	{
		return false;
	}

	return true;
}

void TextComponent::ReleaseTexture()
{
	if (mTexture)
	{
		mTexture->Release();
		delete mTexture;
		mTexture = 0;
	}
}


