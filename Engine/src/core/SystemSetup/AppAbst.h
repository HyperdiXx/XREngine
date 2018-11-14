#pragma once

#ifndef _APP_ABST_
#define _APP_APST_

const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#include "../pch/TypesSetup.h"
#include "Timer.h"
#include "../GraphicsDevice/d3dclass.h"
#include "FPS.h"
#include "../Input/Input.h"
#include "../../scene/manager/ShaderManager.h"
#include "../../scene/Scene.h"
#include "../../scene/manager/TextureManager.h"
#include "../../Core.h"

struct XENGINE_API AppAbstraction
{
	AppAbstraction();
	~AppAbstraction();

	bool Init(HINSTANCE, HWND, int32, int32);
	bool Update();
	bool Release();

	Input* mInput;
	D3DClass* mRender;
	FpsStat* mFPS;
	GameTimer* mTimer;
	Scene* mScene;
	ShaderManager* shM;
	TextureManager* textM;
};
#endif // !_APP_ABST_

