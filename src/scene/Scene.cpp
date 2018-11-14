
#include "Scene.h"

Scene::Scene()
{
	//camera = 0;
}

Scene::~Scene()
{

}

bool Scene::Initialize(D3DClass *render, HWND hwnd, int32 w, int32 h, real32 depth)
{
	mCamera = new Camera;
	if (!mCamera)
		return false;

	mCamera->SetPosition(128.0f, 10.0f, 128.0f);
	mCamera->Render();
	mCamera->RenderBaseViewMatrix();
	LOG("Camera Init...\n");

	mController = new Controller;
	if (!mController)
	{
		return false;
	}

	mController->SetPosition(128.0f, 10.0f, 128.0f);
	mController->SetRotation(0.0f, 0.0f, 0.0f);
	LOG("Controller Init...\n");
	
	/*mGui = new GUI;
	if (!mGui)
	{
		return false;
	}

	if (mGui->Init(render, w, h))
	{
		LOG("GUI Init...\n");
	}*/
	
	mTerrain = new Terrain;
	if (!mTerrain)
	{
		return false;
	}

	if (mTerrain->Init(render->GetDevice(), "../Engine/data/heightmap01.bmp"))
	{
		LOG("Terrain Init...\n");
	}

	mLight = new Light;
	if (!mLight)
		return false;

	mLight->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	mLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	mLight->SetDirection(0.0f, 0.0f, 0.75f);

	LOG("LightIsInit!");

	IsGUI = true;
	IsWireframe = true;

		
	return true;
}

void Scene::Release()
{
	if (mLight)
	{
		delete mLight;
		mLight = 0;
	}

	if (mTerrain)
	{
		mTerrain->Release();
		delete mTerrain;
		mTerrain = 0;
	}

	if (mController)
	{
		delete mController;
		mController = 0;
	}

	if (mCamera)
	{
		delete mCamera;
		mCamera = 0;
	}

	if (mGui)
	{
		mGui->Release();
		delete mGui;
		mGui = 0;
	}

}

bool Scene::Update(D3DClass *render, Input *input, ShaderManager *sh, TextureManager* tm, real32 frameTime, int32 fps)
{
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	HandleMovementInput(input, frameTime);

	mController->GetPosition(posX, posY, posZ);
	mController->GetRotation(rotX, rotY, rotZ);
	
	/*result = mGui->Update(render->GetDeviceContext(), fps, posX, posY, posZ, rotX, rotY, rotZ);
	if (!result)
	{
		return false;
	}
	*/
	result = Render(render, sh, tm);
	if (!result)
	{
		return false;
	}

	return true;
}

void Scene::HandleMovementInput(Input *Input, float frameTime)
{
	bool keyDown = false;
	float posX, posY, posZ, rotX, rotY, rotZ;

	mController->SetFrameTime(frameTime);

	keyDown = Input->IsLeftPressed();
	mController->TurnLeft(keyDown);
	
	keyDown = Input->IsRightPressed();
	mController->TurnRight(keyDown);

	keyDown = Input->IsUpPressed();
	mController->MoveForward(keyDown);

	keyDown = Input->IsDownPressed();
	mController->MoveBackward(keyDown);

//	keyDown = Input->IsAPressed();
//	mController->MoveUpward(keyDown);

	//keyDown = Input->IsZPressed();
	//mController->MoveDownward(keyDown);

	//keyDown = Input->IsPgUpPressed();
	//mController->LookUpward(keyDown);

//	keyDown = Input->IsPgDownPressed();
//	mController->LookDownward(keyDown);

	mController->GetPosition(posX, posY, posZ);
	mController->GetRotation(rotX, rotY, rotZ);

	mCamera->SetPosition(posX, posY, posZ);
	mCamera->SetRotation(rotX, rotY, rotZ);

	if (Input->IsF1Toggled())
	{
		IsGUI = !IsGUI;
	}

	if (Input->IsF2Toggled())
	{
		IsWireframe = !IsWireframe;
	}

}

bool Scene::Render(D3DClass *render, ShaderManager *shM, TextureManager* txM)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseviewMatrix, orthoMatrix;

	mCamera->Render();

	render->GetWorldMatrix(worldMatrix);
	mCamera->GetViewMatrix(viewMatrix);
	render->GetProjectionMatrix(projectionMatrix);
	mCamera->GetBaseViewMatrix(baseviewMatrix);
	render->GetOrthoMatrix(orthoMatrix);

	render->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	if (IsWireframe)
	{
		render->EnableWireframe();
	}

	mTerrain->Render(render->GetDeviceContext());

	//shM->ColorShaderRender(render->GetDeviceContext(), mTerrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//shM->TextureShaderRender(render->GetDeviceContext(), mTerrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, txM->getTexture(1));
	shM->TerrainShaderRender(render->GetDeviceContext(), mTerrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		mLight->GetAmbientColor(),
		mLight->GetDiffuseColor(),
		mLight->GetDirection());


	if (IsWireframe)
	{
		render->DisableWireframe();
	}
	

	/*if (IsGUI)
	{
		mGui->Render(render, shM, worldMatrix, viewMatrix, orthoMatrix);
	}*/

	render->EndScene();

	return true;
}



