
#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")


#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

namespace XEngine
{
	class RendererComponent
	{
	public:
		RendererComponent();
		RendererComponent(const RendererComponent&);
		~RendererComponent();

		bool Initialize(int, int, bool, HWND, bool, float, float);
		void Shutdown();

		void BeginScene(float, float, float, float);
		void EndScene();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();

		void GetProjectionMatrix(XMMATRIX&);
		void GetWorldMatrix(XMMATRIX&);
		void GetOrthoMatrix(XMMATRIX&);

		void GetVideoCard(char*, int&);

		void TurnZBufferOn();
		void TurnZBufferOff();

		void TurnOnCulling();
		void TurnOffCulling();

		void EnableAlphaBlending();
		void EnableAlphaToCoverageBlending();
		void DisableAlphaBlending();

		void EnableWireframe();
		void DisableWireframe();
	private:
		bool mVsync_enabled;
		int mVideoCardMemory;
		char mVideoCardDescription[128];
		IDXGISwapChain* m_swapChain;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D* m_depthStencilBuffer;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11RasterizerState* m_rasterState;
		ID3D11RasterizerState* m_rasterStateNoCulling;
		ID3D11RasterizerState* m_rasterStateWireframe;
		XMMATRIX m_projectionMatrix;
		XMMATRIX m_worldMatrix;
		XMMATRIX m_orthoMatrix;
		ID3D11DepthStencilState* m_depthDisabledStencilState;
		ID3D11BlendState* m_alphaEnableBlendingState;
		ID3D11BlendState* m_alphaDisableBlendingState;
		ID3D11BlendState* m_alphaEnableBlendingState2;
	};
}
#endif