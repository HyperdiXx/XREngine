#pragma once

#ifndef _APP_ABST_
#define _APP_APST_

const bool VSYNC_ENABLED = true;
const float FAR_PLANE = 1000.0f;
const float NEAR_PLANE = 0.1f;

#include "../pch/TypesSetup.h"
#include "Timer.h"
#include "../GraphicsDevice/d3dclass.h"
#include "FPS.h"
#include "../Input/Input.h"
#include "../../scene/manager/ShaderManager.h"
#include "../../scene/Scene.h"
#include "../../scene/manager/TextureManager.h"
#include "../../Core.h"

namespace XEngine
{
	class XENGINE_API AppAbstraction
	{
	public:
		AppAbstraction();
		~AppAbstraction();

		bool Init(HINSTANCE, HWND, int32, int32);
		bool Update();
		bool Release();
	private:
		Input * mInput;
		RendererComponent* mRender;
		FpsStat* mFPS;
		GameTimer* mTimer;
		Scene* mScene;
		ShaderManager* shM;
		TextureManager* textM;
	};

}

#endif // !_APP_ABST_

