#pragma once

#ifndef _GUI_H
#define _GUI_H

#include "../../scene/objects/Text.h"
#include "../../Core.h"

class XENGINE_API GUI
{
public:
	GUI();
	~GUI();

	bool Init(D3DClass*, int32, int32);
	bool Render(D3DClass*, ShaderManager*, XMMATRIX&, XMMATRIX&, XMMATRIX&);
	void Release();
	bool Update(ID3D11DeviceContext*, int, float, float, float, float, float, float);
private:
	bool UpdateFPSString(ID3D11DeviceContext*, int);
	bool UpdatePosString(ID3D11DeviceContext*, real32, real32, real32, real32, real32, real32);

private:
	TextComponent * mTextcomp;
	Text * mVideoInfo,  *mFPSInfo, * mPosInfo;
	int32 mPrevFPS;
	int32 mPrevPos[6];
};
#endif // !_GUI_H

