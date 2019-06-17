#ifndef SYSTEM_RENDERING_H
#define SYSTEM_RENDERING_H


// TODO includes librarys

#include <Windows.h>

#include <string>
#include <iostream>
#include<d3d11.h>
#include <d3dcompiler.h>


//include libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// TODO include membres or classes






class SystemRendering
{
public:
	SystemRendering();
	SystemRendering(const SystemRendering& other);
	~SystemRendering();



	bool Initiliazed(HWND window, int width, int height);
	bool Render(float red, float green, float blue, float alpha);
	bool Release();

	bool Present(bool vSync);


private:
	ID3D11Device* m_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	
private:
	IDXGIDevice* m_dgxiDevive;
	IDXGIAdapter* m_dxgiAdapter;
	IDXGIFactory* m_dxgiFactory;
	IDXGISwapChain* m_idxgi_swapcain;
};








#endif // !SYSTEM_RENDERING_H
