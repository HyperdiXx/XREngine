#pragma once

#ifndef _GUI_H
#define _GUI_H

#include "../../scene/objects/Text.h"
#include "../../Core.h"

namespace XEngine
{
	class XENGINE_API GUI
	{
	public:
		GUI();
		~GUI();

		bool Init(RendererComponent*, int32, int32);
		bool Render(RendererComponent*, ShaderManager*, XMMATRIX&, XMMATRIX&, XMMATRIX&);
		void Release();
		bool Update(ID3D11DeviceContext*, int, float, float, float, float, float, float);

		bool UpdateFPSString(ID3D11DeviceContext*, int);
		bool UpdatePosString(ID3D11DeviceContext*, real32, real32, real32, real32, real32, real32);
	private:
		TextComponent * mTextcomp;
		Text * mVideoInfo, *mFPSInfo, *mPosInfo;
		int32 mPrevFPS;
		int32 mPrevPos[6];
	};

}
#endif // !_GUI_H

