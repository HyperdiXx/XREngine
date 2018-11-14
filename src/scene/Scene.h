#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "../core/pch/TypesSetup.h"

#include <windows.h>

#include "../core/SystemSetup/Camera.h"
#include "../core/SystemSetup/Controller.h"
#include "../core/GraphicsDevice/d3dclass.h"
#include "manager/ShaderManager.h"
#include "manager/TextureManager.h"
#include "../core/Input/Input.h"
#include "../core/SystemSetup/Timer.h"
#include "Terrain.h"
#include "../core/GUI/GUI.h"
#include "Lighting.h"
#include "../Core.h"

using namespace XEngine;

class XENGINE_API Scene
{
public:
	Scene();
	~Scene();

	bool Initialize(D3DClass*, HWND, int32, int32, real32);
	void Release();
	bool Update(D3DClass*, Input*, ShaderManager*, TextureManager*, real32, int32);
private:

	void HandleMovementInput(Input*, float);
	bool Render(D3DClass*, ShaderManager*, TextureManager*);

private:
	//Scene(const Scene& obj) {};

	//Scene &operator=(const Scene& obj) { return 0; }
private:
	Camera * mCamera;
	Controller* mController;
	Terrain* mTerrain;
	GUI* mGui;
	Light* mLight;
	bool IsGUI, IsWireframe;
};
#endif // !_SCENE_H_

