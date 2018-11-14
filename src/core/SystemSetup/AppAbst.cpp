
#include "AppAbst.h"

AppAbstraction::AppAbstraction()
{


}

AppAbstraction::~AppAbstraction()
{
}

bool AppAbstraction::Init(HINSTANCE hInstance, HWND hWnd, int32 W, int32 H)
{
	bool resl;

	mInput = new Input;

	if (!mInput->Init(hInstance, hWnd, W, H))
	{
		return false;
	}

	mRender = new D3DClass;
	if (!mRender)
	{
		return false;
	}

	if (!mRender->Initialize(W, H, VSYNC_ENABLED, hWnd, false, SCREEN_DEPTH, SCREEN_NEAR))
	{
		return false;
	}

	mTimer = new GameTimer;
	if (!mTimer)
	{
		return false;
	}

	mTimer->Init();

	mFPS = new FpsStat;
	if (!mFPS)
	{
		return false;
	}

	mFPS->Initialize();

	/*shM = new ShaderManager;
	if (!shM)
	{
		return false;
	}

	shM->Init(mRender->GetDevice(), hWnd);

	/*textM = new TextureManager;
	if (!textM)
	{
		return false;
	}

	/*resl = textM->Init(10);
	if (FAILED(resl))
	{
		return false;
	}
	resl = textM->LoadTexture(mRender->GetDevice(), mRender->GetDeviceContext(), 0, "../Engine/data/textures/test.tga");
	if(FAILED(resl))
	{
		return false;
	}
	resl = textM->LoadTexture(mRender->GetDevice(), mRender->GetDeviceContext(), 1, "../Engine/data/textures/dirt01d.tga");
	if (FAILED(resl))
	{
		return false;
	}*/

	mScene = new Scene;
	if (!mScene->Initialize(mRender, hWnd, W, H, SCREEN_DEPTH))
	{
		return false;
	}
	
	return true;
}

bool AppAbstraction::Update()
{

	mFPS->Update();
	mTimer->Tick();

	if (!mInput->Update())
	{
		return false;
	}

	if (mInput->IsEscapePressed() == true)
	{
		return false;
	}

	if (!mScene->Update(mRender, mInput, shM, textM, mTimer->GetTime(), mFPS->GetFps()))
	{
		return false;
	}

	return true;
}

bool AppAbstraction::Release()
{
	if (textM)
	{
		textM->Release();
		delete textM;
		textM = NULL;
	}

	if (mScene)
	{
		mScene->Release();
		delete mScene;
		mScene = NULL;
	}

	if (mFPS)
	{
		delete mFPS;
		mFPS = NULL;
	}

	if (mTimer)
	{
		delete mTimer;
		mTimer = NULL;
	}

	if (shM)
	{
		shM->Release();
		delete shM;
		shM = NULL;
	}

	if (mRender)
	{
		mRender->Shutdown();
		delete mRender;
		mRender = NULL;
	}

	if (mInput)
	{
		mInput->Release();
		delete mInput;
		mInput = NULL;
	}
	return true;
}
