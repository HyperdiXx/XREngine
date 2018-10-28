#pragma once

#ifndef _SCENE_H_
#define _SCENE_H_

#include "Setup.h"

#include <windows.h>

#include "Camera.h"
#include "Controller.h"
#include "d3dclass.h"
#include "ShaderManager.h"
#include "Input.h"
#include "Timer.h"
#include "Terrain.h"
#include "GUI.h"


class Scene
{
public:
	Scene();
	~Scene();

	bool Initialize(D3DClass*, HWND, int32, int32, real32);
	void Release();
	bool Update(D3DClass*, Input*, ShaderManager*, real32, int32);
private:

	void HandleMovementInput(Input*, float);
	bool Render(D3DClass*, ShaderManager*);

private:
	Scene(const Scene& obj) {};

	Scene &operator=(const Scene& obj) {}
private:
	Camera * mCamera;
	Controller* mController;
	Terrain* mTerrain;
	GUI* mGui;
	bool IsGUI;
};
#endif // !_SCENE_H_

