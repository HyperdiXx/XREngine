#pragma once

#ifndef _APP_ABST_
#define _APP_APST_

const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#include "Setup.h"
#include "Timer.h"
#include "d3dclass.h"
#include "FPS.h"
#include "Input.h"
#include "ShaderManager.h"
#include "Scene.h"

class AppAbstraction
{
public:
	AppAbstraction();
	~AppAbstraction();

	bool Init(HINSTANCE, HWND, int32, int32);
	bool Update();
	bool Release();

private:

	Input* mInput;
	D3DClass* mRender;
	FpsStat* mFPS;
	GameTimer* mTimer;
	Scene* mScene;
	ShaderManager* shM;



};
#endif // !_APP_ABST_

