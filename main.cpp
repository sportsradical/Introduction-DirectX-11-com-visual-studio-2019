#include "RenderWindow.h"



int main()
{
	RenderWindow* renderwindow = new RenderWindow();

	if (renderwindow->Initialized("sample", 800, 600))
	{
		while (renderwindow->Run())
		{
			renderwindow->Update();
		}
	}





	return 0;
}


