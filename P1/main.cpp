#include "p1Windows.h"
#include <d3d9.h>
//	use int main if you want to have a console to print out message



int main()
//	use WinMain if you don't want the console
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Windows windows;
	windows.createWindow();
	if (!windows.createDirectX()|| !windows.createSprite()|| !windows.createFont())
	{
		return 0;
	}
	while (windows.loop())
	{
		windows.toggleScreen();
		windows.color();
		windows.changeColor();
	}

	windows.clearWindow();
	return 0;
}
