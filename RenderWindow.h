#pragma once
#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include "GraphicsEngine.h"


class RenderWindow
{
public:
	RenderWindow();
	RenderWindow(std::string title, int width, int height);
	RenderWindow(const RenderWindow& other);
	~RenderWindow();


	LRESULT CALLBACK WindowProc(HWND   hwnd, UINT   uMsg, WPARAM wParam, LPARAM lParam);

	bool Initialized(std::string title, int width, int height);
	
	// todo code for initialization 
	bool Run();
	bool Update();
	bool Shutdown();


private:
	std::string title;
	std::string windowClassNname;
	
	int height;
	int width;
	bool isRuning;

	HWND window;
	HINSTANCE hInstance;

private:
	GraphicsEngine* m_graphicsEngine;

};





#endif // !RENDER_WINDOW_H








