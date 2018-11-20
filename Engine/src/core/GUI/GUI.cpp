#include "GUI.h"

GUI::GUI()
{
}

GUI::~GUI()
{
}

bool GUI::Init(RendererComponent *render, int32 screenW, int32 screenH)
{
	char videocardinfo[128];
	int32 Memory;
	char VideoString[128];
	char memoryString[128];
	char tempString[16];

	mTextcomp = new TextComponent;
	if (!mTextcomp)
	{
		return false;
	}

	mTextcomp->Init(render->GetDevice(), render->GetDeviceContext(), "../Engine/data/font/font01.txt", "../Engine/data/font/font01.tga", 32.0f, 3);

	mFPSInfo = new Text;
	if (!mFPSInfo)
	{
		return false;
	}

	mFPSInfo->Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 16, false, mTextcomp, "FPS: 0", 10, 50, 0.0f, 1.0f, 0.0f);

	mPrevFPS = -1;

	//render->GetVideoCard(videocardinfo, Memory);
	//strcpy_s(VideoString, "Video Card: ");
	//strcat_s(VideoString, videocardinfo);

	//_itoa_s(Memory, tempString, 10);

	//strcpy_s(memoryString, "Video Memory: ");
	//strcat_s(memoryString, tempString);
	//strcat_s(memoryString, " MB");

	mVideoInfo = new Text[2];
	if (!mVideoInfo)
	{
		return false;
	}

	mVideoInfo[0].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 256, false, mTextcomp,
		VideoString, 10, 10, 1.0f, 1.0f, 1.0f);

	mVideoInfo[1].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 32, false, mTextcomp,
		VideoString, 10, 30, 1.0f, 1.0f, 1.0f);


	mPosInfo = new Text[6];
	if (!mPosInfo)
	{
		return false;
	}

	mPosInfo[0].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 16, false, mTextcomp,
		"X: 0", 10, 310, 1.0f, 1.0f, 1.0f);


	mPosInfo[1].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 16, false, mTextcomp,
		"Y: 0", 10, 330, 1.0f, 1.0f, 1.0f);

	mPosInfo[2].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 16, false, mTextcomp,
		"Z: 0", 10, 350, 1.0f, 1.0f, 1.0f);
	
	mPosInfo[3].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 16, false, mTextcomp,
		"rX: 0", 10, 370, 1.0f, 1.0f, 1.0f);
	
	mPosInfo[4].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 16, false, mTextcomp,
		"rY: 0", 10, 390, 1.0f, 1.0f, 1.0f);
	

	mPosInfo[5].Init(render->GetDevice(), render->GetDeviceContext(), screenW, screenH, 16, false, mTextcomp,
		"rZ: 0", 10, 410, 1.0f, 1.0f, 1.0f);
	
	for (size_t i = 0; i < 6; ++i)
	{
		mPrevPos[i] = -1;
	}
	
	return true;
}

bool GUI::Render(RendererComponent *render, ShaderManager *shadermanager, XMMATRIX &world, XMMATRIX &view, XMMATRIX &ortho)
{
	render->TurnZBufferOff();
	render->EnableAlphaBlending();

	mFPSInfo->Render(render->GetDeviceContext(), shadermanager, world, view, ortho, mTextcomp->GetTexture());

	mVideoInfo[0].Render(render->GetDeviceContext(), shadermanager, world, view, ortho, mTextcomp->GetTexture());
	mVideoInfo[1].Render(render->GetDeviceContext(), shadermanager, world, view, ortho, mTextcomp->GetTexture());

	for (size_t i = 0; i < 6; ++i)
	{
		mPosInfo[i].Render(render->GetDeviceContext(), shadermanager, world, view, ortho, mTextcomp->GetTexture());
	}

	render->DisableAlphaBlending();
	render->TurnZBufferOn();

	return true;
}

void GUI::Release()
{
	if (mPosInfo)
	{
		mPosInfo[0].Release();
		mPosInfo[1].Release();
		mPosInfo[2].Release();
		mPosInfo[3].Release();
		mPosInfo[4].Release();
		mPosInfo[5].Release();

		delete[] mPosInfo;
		mPosInfo = 0;
	}

	if (mVideoInfo)
	{
		mVideoInfo[0].Release();
		mVideoInfo[1].Release();

		delete[] mVideoInfo;
		mVideoInfo = 0;
	}

	if (mFPSInfo)
	{
		mFPSInfo->Release();
		delete mFPSInfo;
		mFPSInfo = 0;
	}

	if (mTextcomp)
	{
		mTextcomp->Release();
		delete mTextcomp;
		mTextcomp = 0;
	}

}

bool GUI::Update(ID3D11DeviceContext *deviceContext, int FPS, float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	UpdateFPSString(deviceContext, FPS);

	UpdatePosString(deviceContext, posX, posY, posZ, rotX, rotY, rotZ);

	return true;
}

bool GUI::UpdateFPSString(ID3D11DeviceContext *deviceContext, int fps)
{
	char tempString[16];
	char finalString[16];
	float red, green, blue;
	bool result;

	// Check if the fps from the previous frame was the same, if so don't need to update the text string.
	if (mPrevFPS == fps)
	{
		return true;
	}

	// Store the fps for checking next frame.
	mPrevFPS = fps;

	if (fps > 1000)
	{
		fps = 1000;
	}

	_itoa_s(fps, tempString, 10);

	strcpy_s(finalString, "Fps: ");
	strcat_s(finalString, tempString);

	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;

/*	// If fps is 60 or above set the fps color to green.
	if (fps >= 60)
	{
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	if (fps < 60)
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}

	if (fps < 30)
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}
	*/
	result = mFPSInfo->UpdateSentence(deviceContext, mTextcomp, finalString, 10, 50, red, green, blue);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GUI::UpdatePosString(ID3D11DeviceContext *deviceContext, real32 posX, real32 posY, real32 posZ, real32 rotX, real32 rotY, real32 rotZ)
{

	int32 positionX = 0, positionY = 0, positionZ = 0, rotationX = 0, rotationY = 0, rotationZ = 0;
	char tempString[16];
	char finalString[16];
	bool result;

	if (positionX != mPrevPos[0])
	{
		mPrevPos[0] = positionX;
		_itoa_s(positionX, tempString, 10);
		strcpy_s(finalString, "X: ");
		strcat_s(finalString, tempString);
		result = mPosInfo[0].UpdateSentence(deviceContext, mTextcomp, finalString, 10, 100, 1.0f, 1.0f, 1.0f);
		if (!result) { return false; }
	}

	if (positionY != mPrevPos[1])
	{
		mPrevPos[1] = positionY;
		_itoa_s(positionY, tempString, 10);
		strcpy_s(finalString, "Y: ");
		strcat_s(finalString, tempString);
		result = mPosInfo[1].UpdateSentence(deviceContext, mTextcomp, finalString, 10, 120, 1.0f, 1.0f, 1.0f);
		if (!result) { return false; }
	}

	if (positionZ != mPrevPos[2])
	{
		mPrevPos[2] = positionZ;
		_itoa_s(positionZ, tempString, 10);
		strcpy_s(finalString, "Z: ");
		strcat_s(finalString, tempString);
		result = mPosInfo[2].UpdateSentence(deviceContext, mTextcomp, finalString, 10, 140, 1.0f, 1.0f, 1.0f);
		if (!result) { return false; }
	}

	if (rotationX != mPrevPos[3])
	{
		mPrevPos[3] = rotationX;
		_itoa_s(rotationX, tempString, 10);
		strcpy_s(finalString, "rX: ");
		strcat_s(finalString, tempString);
		result = mPosInfo[3].UpdateSentence(deviceContext, mTextcomp, finalString, 10, 180, 1.0f, 1.0f, 1.0f);
		if (!result) { return false; }
	}

	if (rotationY != mPrevPos[4])
	{
		mPrevPos[4] = rotationY;
		_itoa_s(rotationY, tempString, 10);
		strcpy_s(finalString, "rY: ");
		strcat_s(finalString, tempString);
		result = mPosInfo[4].UpdateSentence(deviceContext, mTextcomp, finalString, 10, 200, 1.0f, 1.0f, 1.0f);
		if (!result) { return false; }
	}

	if (rotationZ != mPrevPos[5])
	{
		mPrevPos[5] = rotationZ;
		_itoa_s(rotationZ, tempString, 10);
		strcpy_s(finalString, "rZ: ");
		strcat_s(finalString, tempString);
		result = mPosInfo[5].UpdateSentence(deviceContext, mTextcomp, finalString, 10, 220, 1.0f, 1.0f, 1.0f);
		if (!result) { return false; }
	}


	
	return true;
}


