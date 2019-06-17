#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <Windows.h>
#include "SystemRendering.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	GraphicsEngine(const GraphicsEngine& other);
	~GraphicsEngine();

	bool Initiliazed(HWND window, int width, int height);
	bool Update();
	bool Render();
	bool Release();

private:

	SystemRendering* m_systemRendering;

};






#endif // 







