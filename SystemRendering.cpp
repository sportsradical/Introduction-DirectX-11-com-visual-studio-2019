#include "SystemRendering.h"

SystemRendering::SystemRendering()
{
	m_idxgi_swapcain = 0;
	m_device = 0;
	m_deviceContext = 0;
	m_renderTargetView = 0;
	

	
}

SystemRendering::SystemRendering(const SystemRendering& other)
{
}

SystemRendering::~SystemRendering()
{
}

bool SystemRendering::Initiliazed(HWND window, int width, int height)
{

	HRESULT h = 0;


	D3D_DRIVER_TYPE driveType[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};


	UINT sizeDriveType = ARRAYSIZE(driveType);

	D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_11_0, 
		D3D_FEATURE_LEVEL_11_1
	};
	UINT feature_level = ARRAYSIZE(featureLevel);

	
	for (UINT driveType_index = 0; driveType_index < sizeDriveType;)
	{
		h = D3D11CreateDevice(NULL, driveType[driveType_index], NULL, NULL, featureLevel, feature_level, D3D11_SDK_VERSION,
			&m_device, &m_feature_level, &m_deviceContext);

		if (SUCCEEDED(h))
			break;

		++driveType_index;
	}
	
	if (FAILED(h))
	{
		MessageBox(window, "Failed Create Device", "ERROR", MB_OK);
		return false;
	}

	m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dgxiDevive);
	m_dgxiDevive->GetParent(__uuidof(IDXGIAdapter), (void**)& m_dxgiAdapter);
	m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)& m_dxgiFactory);

	DXGI_SWAP_CHAIN_DESC swap_chain_desc = { 0 };
	ZeroMemory(&swap_chain_desc, sizeof(m_idxgi_swapcain));


	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Height = height;
	swap_chain_desc.BufferDesc.Width = width;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = window;
	swap_chain_desc.Windowed = true;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;

	h = m_dxgiFactory->CreateSwapChain(m_device, &swap_chain_desc, &m_idxgi_swapcain);
	if (FAILED(h))
	{
		MessageBox(window, "Failed Create Swap Chain", "ERROR", MB_OK);
		return false;
	}


	ID3D11Texture2D* buffer;
	h = m_idxgi_swapcain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(h))
	{
		return false;
	}

	
	
	h = m_device->CreateRenderTargetView(buffer, NULL, &m_renderTargetView);
	buffer->Release();
	if (FAILED(h))
	{
		return false;
	}

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);

	D3D11_VIEWPORT viewport;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	
	// Create the viewport.
	m_deviceContext->RSSetViewports(1, &viewport);

	
	return true;
}

bool SystemRendering::Render(float red, float green, float blue, float alpha)
{
	FLOAT color[] = { red, green, blue, alpha };

	
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
	
	Present(true);
	
	
	return true;
}


bool SystemRendering::Present(bool vSync)
{
	m_idxgi_swapcain->Present(1, 0);
	return true;
}



bool SystemRendering::Release()
{
	if (m_device)
	{
		m_device->Release();
		m_device = 0;
	}


	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = 0;
	}

	if (m_idxgi_swapcain)
	{
		m_idxgi_swapcain->Release();
		m_idxgi_swapcain = 0;
	}

	return true;
}



