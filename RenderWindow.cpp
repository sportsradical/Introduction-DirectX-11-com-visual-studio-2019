#include "RenderWindow.h"

RenderWindow::RenderWindow()
{
	m_graphicsEngine = NULL;
}

RenderWindow::RenderWindow(std::string title, int width, int height)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->isRuning = true;
}

RenderWindow::RenderWindow(const RenderWindow& other)
{
}

RenderWindow::~RenderWindow()
{

}

LRESULT RenderWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{

		break;
	}
	case WM_DESTROY:
	{
		Shutdown();
		break;
	}
	default:
		break;
	}



	return DefWindowProc(this->window, uMsg, wParam, lParam);
}



// TODO Code for Initialization 

bool RenderWindow::Run()
{
	bool result;
	m_graphicsEngine = new GraphicsEngine();

	if (!m_graphicsEngine)
	{
		return false;
	}

	result = m_graphicsEngine->Initiliazed(this->window, this->width, this->height);
	
	// se nao existir resultados deve voltar a falso 
	// isto é nao ha resultados deve returnar a um erro  


	if (!result)
	{
		MessageBox(this->window, "Graphics engine Failed Initialization", "ERROR", MB_OK);
		return false;
	}


	return true;
}


bool RenderWindow::Initialized(std::string title, int width, int height)
{

	this->title = title;
	this->width = width;
	this->height = height;
	this->windowClassNname = title;

	::WNDCLASSEX wc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = 0;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = this->hInstance;
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->windowClassNname.c_str();

	if (!RegisterClassEx(&wc))
	{
		return false;
	}


	this->window = CreateWindowEx(WS_OVERLAPPED, this->windowClassNname.c_str(), this->title.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE |WS_SYSMENU | WS_CAPTION, 0, 0, this->width, this->height, NULL, NULL, this->hInstance, NULL);


	if (this->window == NULL)
	{
		return false;
	}

	::ShowWindow(this->window, SW_SHOW);
	::SetForegroundWindow(this->window);
	::SetFocus(this->window);
	::UpdateWindow(this->window);
	::ShowCursor(true);

	isRuning = true;



	return true;

}

bool RenderWindow::Update()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	// todo codigo para update

	while (isRuning)
	{
		if (PeekMessage(&msg, this->window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		// test
		if (msg.message == WM_NULL)
		{
			if (IsWindow(this->window))
			{
				this->window = NULL;
				UnregisterClass(this->windowClassNname.c_str(), this->hInstance);
				return false;
			}
		}
		m_graphicsEngine->Update();
	}

	return true;

}

bool RenderWindow::Shutdown()
{
	isRuning = false;

	if (IsWindow(this->window))
	{
		this->window = NULL;
		UnregisterClass(this->windowClassNname.c_str(), this->hInstance);

	}

	DestroyWindow(this->window);

	m_graphicsEngine->Release();

	return true;
}


