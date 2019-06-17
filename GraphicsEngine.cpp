#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{
	m_systemRendering =  NULL;
}

GraphicsEngine::GraphicsEngine(const GraphicsEngine& other)
{
}

GraphicsEngine::~GraphicsEngine()
{
}

// TODO Code for Initialization
bool GraphicsEngine::Initiliazed(HWND window, int width, int height)
{
	bool result;

	m_systemRendering = new SystemRendering();
	if (!m_systemRendering)
	{
		return false;
	}

	result = m_systemRendering->Initiliazed(window, width, height);
	if (!result)
	{
		MessageBox(NULL, "Failed Initialization System Rendering Engine", "ERROR", MB_OK);
		return false;
	}



	return true;
}

// TODO Code for Update

bool GraphicsEngine::Update()
{
	bool result = true;

	result = Render();

	if (!result)
	{
		MessageBox(NULL, "Failed Renderization Engine", "ERROR", MB_OK);
		return false;
	}


	return true;
}


// TODO Code for Renderization

bool GraphicsEngine::Render()
{
	m_systemRendering->Render(0.0f, 0.0f, 1.0f, 1.0f);

	return true;
}

// TODO Code for Relase or destroy 
bool GraphicsEngine::Release()
{
	m_systemRendering->Release();
	return true;
}
