
#include "AppAbst.h"

AppAbstraction::AppAbstraction()
{


}

AppAbstraction::~AppAbstraction()
{
}

bool AppAbstraction::Init(HINSTANCE hInstance, HWND hWnd, int32 W, int32 H)
{
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

	shM = new ShaderManager;
	if (!shM)
	{
		return false;
	}

	shM->Init(mRender->GetDevice(), hWnd);

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

	if (!mScene->Update(mRender, mInput, shM, mTimer->GetTime(), mFPS->GetFps()))
	{
		return false;
	}

	return true;
}

bool AppAbstraction::Release()
{
	if (mScene)
	{
		mScene->Release();
		delete mScene;
		mScene = 0;
	}

	if (mFPS)
	{
		delete mFPS;
		mFPS = 0;
	}

	if (mTimer)
	{
		delete mTimer;
		mTimer = 0;
	}

	if (shM)
	{
		shM->Release();
		delete shM;
		shM = 0;
	}

	if (mRender)
	{
		mRender->Shutdown();
		delete mRender;
		mRender = 0;
	}

	if (mInput)
	{
		mInput->Release();
		delete mInput;
		mInput = 0;
	}
	return true;
}
