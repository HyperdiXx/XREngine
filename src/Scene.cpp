
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

	mCamera->SetPosition(10.0f, 0.0f, -10.0f);
	mCamera->Render();
	mCamera->RenderBaseViewMatrix();

	mController = new Controller;
	if (!mController)
	{
		return false;
	}

	mController->SetPosition(128.0f, 5.0f, -10.0f);
	mController->SetRotation(0.0f, 0.0f, 0.0f);

	mGui = new GUI;
	if (!mGui)
	{
		return false;
	}

	
	mTerrain = new Terrain;
	if (!mTerrain)
	{
		return false;
	}

	mTerrain->Init(render->GetDevice());

		
	return true;
}

void Scene::Release()
{
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

bool Scene::Update(D3DClass *render, Input *input, ShaderManager *sh, real32 frameTime, int32 fps)
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
	}*/

	result = Render(render, sh);
	if (!result)
	{
		return false;
	}

	return true;
}

void Scene::HandleMovementInput(Input *input, float frameTime)
{
	bool keyDown = false;
	real32 posX, posY, posZ, rotX, rotY, rotZ;


	mController->SetFrameTime(frameTime);

	////keyDown = input->IsLeftPressed();
	//mController->TurnLeft(keyDown);

	////keyDown = input->IsRightPressed();
	//mController->TurnRight(keyDown);

	keyDown = input->IsUpPressed();
	mController->MoveForward(keyDown);

	////keyDown = input->IsDownPressed();
	//mController->MoveBackward(keyDown);

	////keyDown = input->IsAPressed();
	//mController->MoveUpward(keyDown);

	////keyDown = input->IsZPressed();
	//mController->MoveDownward(keyDown);

	////keyDown = input->IsPgUpPressed();
	//mController->LookUpward(keyDown);

	////keyDown = input->IsPgDownPressed();
	//mController->LookDownward(keyDown);

	mController->GetPosition(posX, posY, posZ);
	mController->GetRotation(rotX, rotY, rotZ);

	mCamera->SetPosition(posX, posY, posZ);
	mCamera->SetRotation(rotX, rotY, rotZ);
	

}

bool Scene::Render(D3DClass *render, ShaderManager *shM)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseviewMatrix, orthoMatrix;

	mCamera->Render();

	render->GetWorldMatrix(worldMatrix);
	mCamera->GetViewMatrix(viewMatrix);
	render->GetProjectionMatrix(projectionMatrix);
	mCamera->GetBaseViewMatrix(baseviewMatrix);
	render->GetOrthoMatrix(orthoMatrix);

	render->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	mTerrain->Render(render->GetDeviceContext());
	shM->ColorShaderRender(render->GetDeviceContext(), mTerrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

	//mGui->Render(render, shM, worldMatrix, viewMatrix, orthoMatrix);

	render->EndScene();

	return true;
}



