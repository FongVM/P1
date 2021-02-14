#include "p1Windows.h"

char isToggle, colorInput = 'N';
int redValue = 0, greenValue = 0, blueValue = 0, speed = 1, isPlus = 1, isRandom = 0, x = 0, y = 0, bgCount = 0, cursorCount = 0, rectIndex = 0, lineCount = 1, textCount = 0, lineTextCount[15];
bool isShift, isBack, isNewLine;
std::string printText ,lineText;

Windows::Windows()
{
	this->hInstance = GetModuleHandle(NULL);
	this->g_hWnd = NULL;
}


//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		if (wParam != VK_BACK && wParam != VK_RETURN)
		{
			if (lineCount <= 15 && textCount < 40)
			{
				printText.append(1, wParam);
				textCount++;
			}
		}
		if (wParam == VK_BACK)
		{
			if (printText.length() != 0)
			{
				printText.erase((printText.length() - 1), 1);
				textCount--;
				if (textCount < 0)
				{
					lineCount -= 1;
					textCount = lineTextCount[lineCount - 1];
					printf("%d %d\n", lineCount, textCount);
				}
			}
		}
		if (wParam == VK_RETURN)
		{
			if (lineCount < 15)
			{
				if(textCount < 0)
				{
					textCount = 0;
				}
				lineTextCount[lineCount - 1] = textCount;
				printText.append("\n");
				lineCount += 1;
				textCount = 0;
			}
		}
		//printf("%d\n", wParam);
		//if (wParam == VK_ESCAPE)
		//{
		//	PostQuitMessage(0);
		//	break;
		//}
		//if (wParam == 'F')
		//{
		//	isToggle = 'Y';
		//	break;
		//}
		//if (wParam == 'R')
		//{
		//	colorInput = 'R';
		//	break;
		//}
		//else if (wParam == 'G')
		//{
		//	colorInput = 'G';
		//	break;
		//}
		//else if (wParam == 'B')
		//{
		//	colorInput = 'B';
		//	break;
		//}
		//if (wParam == 219)
		//{
		//	if (speed < 10)
		//	{
		//		speed += 1;
		//		printf("SP: %2d RGB:%( %d, %d, %d %)\n", speed, redValue, greenValue, blueValue);
		//	}
		//	break;
		//}
		//if (wParam == 221)
		//{
		//	if (speed > 1)
		//	{
		//		speed -= 1;
		//		printf("SP: %2d RGB:%( %d, %d, %d %)\n", speed, redValue, greenValue, blueValue);
		//	}
		//	break;
		//}
		//if (wParam == 'P')
		//{
		//	if (isPlus == 1)
		//	{
		//		isPlus = 0;
		//		printf("Decrement\n");
		//	}

		//	else
		//	{
		//		isPlus = 1;
		//		printf("Increment\n");
		//	}
		//}
		//if (wParam == 'L')
		//{
		//	if (isRandom == 1)
		//	{
		//		isRandom = 0;
		//		printf("Not random number\n");
		//	}

		//	else
		//	{
		//		isRandom = 1;
		//		printf("Random number\n");
		//	}
		//}
		//if (wParam == VK_UP)
		//{
		//	bgCount += 1;
		//	break;
		//}
		//else if (wParam == VK_DOWN)
		//{
		//	bgCount -= 1;
		//	break;
		//}
		//else if (wParam == VK_LEFT)
		//{
		//	cursorCount -= 1;
		//	break;
		//}
		//else if (wParam == VK_RIGHT)
		//{
		//	cursorCount += 1;
		//	break;
		//}

		//if (wParam >= 48 && wParam <= 57)
		//{
		//	rectIndex = wParam - 48;
		//	printf("%d %d\n", wParam, rectIndex);
		//}
		//if (wParam == 190)
		//{
		//	rectIndex = 10;
		//	printf("%d %d\n", wParam, rectIndex);
		//}
		//if (wParam == 187)
		//{
		//	rectIndex = 11;
		//	printf("%d %d\n", wParam, rectIndex);
		//}
		//if (isShift && wParam == 187)
		//{
		//	rectIndex = 12;
		//	printf("%d %d\n", wParam, rectIndex);
		//}
		//if (wParam == 189)
		//{
		//	rectIndex = 13;
		//	printf("%d %d\n", wParam, rectIndex);
		//}
		//if (isShift && wParam == 56)
		//{
		//	rectIndex = 14;
		//	printf("%d %d\n", wParam, rectIndex);
		//}
		//if (wParam == 191)
		//{
		//	rectIndex = 15;
		//	printf("%d %d\n", wParam, rectIndex);
		//}
		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Windows::createWindow()
{
	/*
	Step 1
	Define and Register a Window.

*/

	WNDCLASS wndClass;

	//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACKONWHITE);
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Practical 1&2&3", WS_OVERLAPPEDWINDOW, 0, 100, 640, 480, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

	//	Some interesting function to try out.
	ShowCursor(false);

}
bool Windows::createDirectX()
{
	IDirect3D9 * direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 640;
	d3dPP.BackBufferHeight = 480;
	d3dPP.hDeviceWindow = g_hWnd;


	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);


	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool Windows::createSprite()
{
	//	Initialization

	//	Create sprite. Study the documentation. 
	HRESULT hr = D3DXCreateSprite(d3dDevice, &sprite);

	//	Create texture. Study the documentation.
	hr = D3DXCreateTextureFromFile(d3dDevice, "Sprite/bg1.png", &texture1);
	hr = D3DXCreateTextureFromFile(d3dDevice, "Sprite/pointer.png", &texture2);
	hr = D3DXCreateTextureFromFileEx(d3dDevice, "Sprite/numbers.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 0), 
									NULL, NULL, &texture3);
	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);

	//	Specify the "	" rectangle.
	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.right = 640;
	spriteRect.bottom = 480;

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++)
		{
			rectList[row * 4 + col].left = col * 64;
			rectList[row * 4 + col].top = row * 64;
			rectList[row * 4 + col].right = col * 64 + 64;
			rectList[row * 4 + col].bottom = row * 64 + 64;
		}
	}

	cursorColor = D3DCOLOR_XRGB(255, 255, 255);
	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool Windows::createFont() {
	//	Initialization

	font = NULL;
	//	Create font. Study the documentation.
	HRESULT hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	textRect.left = 0;
	textRect.top = 0;
	textRect.right = 520;
	textRect.bottom = 400;

	textRect2.left =260;
	textRect2.top = 400;
	textRect2.right = 520;
	textRect2.bottom = 420;

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void Windows::toggleScreen()
{
	if (isToggle == 'Y')
	{
		if (d3dPP.Windowed)
		{
			d3dPP.Windowed = false;
			d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
			d3dPP.BackBufferWidth = 400;
			d3dPP.BackBufferHeight = 300;
		}
		else
		{
			d3dPP.Windowed = true;
			d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
			d3dPP.BackBufferWidth = 400;
			d3dPP.BackBufferHeight = 300;
			SetWindowLongPtr(g_hWnd, GWL_STYLE, WS_POPUP);
			SetWindowPos(g_hWnd, HWND_TOP, 0, 0, 400, 300, SWP_NOZORDER | SWP_SHOWWINDOW);
		}
		sprite->Release();
		sprite = NULL;
		d3dDevice->Reset(&d3dPP);
		D3DXCreateSprite(d3dDevice, &sprite);
		isToggle = 'N';
	}
}
void Windows::color()
{
	if (colorInput != 'N')
	{
		if (colorInput == 'R')
		{
			//redValue += speed;
			//if (redValue > 255)
			//{
			//	redValue -= 256;
			//}
			if (isRandom == 0)
			{
				if (isPlus == 1)
				{
					redValue += speed;
				}
				else
				{
					redValue -= speed;
				}
				if (redValue >= 255)
				{
					isPlus = 0;
					redValue = 255;
				}
				else if (redValue <= 0)
				{
					isPlus = 1;
					redValue = 0;
				}
			}
			else
			{
				redValue = rand() % 255;
			}

		}
		else if (colorInput == 'G')
		{
			//greenValue += speed;
			//if (greenValue > 255)
			//{
			//	greenValue -= 256;
			//}
			if (isRandom == 0)
			{
				if (isPlus == 1)
				{
					greenValue += speed;
				}
				else
				{
					greenValue -= speed;
				}
				if (greenValue >= 255)
				{
					isPlus = 0;
					greenValue = 255;
				}
				else if (greenValue <= 0)
				{
					isPlus = 1;
					greenValue = 0;
				}
			}
			else
			{
				greenValue = rand() % 255;
			}

		}
		else if (colorInput == 'B')
		{
			//blueValue += speed;
			//if (blueValue > 255)
			//{
			//	blueValue -= 256;
			//}
			if (isRandom == 0)
			{
				if (isPlus == 1)
				{
					blueValue += speed;
				}
				else
				{
					blueValue -= speed;
				}
				if (blueValue >= 255)
				{
					isPlus = 0;
					blueValue = 255;
				}
				else if (blueValue <= 0)
				{
					isPlus = 1;
					blueValue = 0;
				}
			}
			else
			{
				blueValue = rand() % 255;
			}

		}
		colorInput = 'N';
		printf("SP: %2d RGB:%( %d, %d, %d %)\n", speed, redValue, greenValue, blueValue);
	}
}

void Windows::changeColor()
{
	if (bgCount == 0)
	{
		D3DXCreateTextureFromFile(d3dDevice, "Sprite/bg1.png", &texture1);
	}
	else if (bgCount == 1)
	{
		D3DXCreateTextureFromFile(d3dDevice, "Sprite/bg2.png", &texture1);
	}
	else if (bgCount == 2)
	{
		D3DXCreateTextureFromFile(d3dDevice, "Sprite/bg3.png", &texture1);
	}
	if (bgCount < 0)
	{
		bgCount = 2;
	}
	else if (bgCount > 2)
	{
		bgCount = 0;
	}

	if (cursorCount == 0)
	{
		cursorColor = D3DCOLOR_XRGB(255, 255, 255);
	}
	else if (cursorCount == 1)
	{
		cursorColor = D3DCOLOR_XRGB(255, 0, 0);
	}
	else if (cursorCount == 2)
	{
		cursorColor = D3DCOLOR_XRGB(0, 255, 0);
	}
	else if (cursorCount == 3)
	{
		cursorColor = D3DCOLOR_XRGB(0, 0, 255);
	}
	if (cursorCount < 0)
	{
		cursorCount = 3;
	}
	else if (cursorCount > 3)
	{
		cursorCount = 0;
	}
}

bool Windows::loop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/
	/*
		The if- version process one message per one iteration loop
		The while- version will clear the message queue before dealing with your own code.
		Another function is GetMessage.
		This function is not suitable for game, because it will block your program until it recieves a message.
		your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
		Suitable for event based program, such as bussiness app.
	*/
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) break;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}
	isShift = GetKeyState(VK_SHIFT);
	isBack = GetKeyState(VK_BACK);
	if (textCount == 40 && !isBack)
	{
		if (lineCount < 15)
		{
			if (textCount < 0)
			{
				textCount = 0;
			}
			lineTextCount[lineCount - 1] = textCount;
			printText.append("\n");
			lineCount += 1;
			textCount = 0;
		}
	}

	lineText = "Line Count :" + std::to_string(lineCount);

	//	Begin the scene

	//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(redValue, greenValue, blueValue), 1.0f, 0);
	d3dDevice->BeginScene();

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//	Sprite rendering. Study the documentation.
	//sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(texture1, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(x, y, 0), D3DCOLOR_XRGB(255, 255, 255));
	sprite->Draw(texture2, NULL, NULL, &D3DXVECTOR3(x, y, 0), cursorColor);
	sprite->Draw(texture3, &rectList[rectIndex], &D3DXVECTOR3(32, 32, 0), &D3DXVECTOR3(320, 240, 0), D3DCOLOR_XRGB(0, 0, 0));

	font->DrawText(sprite, printText.c_str(), -1, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
	font->DrawText(sprite,lineText.c_str(), -1, &textRect2, 0, D3DCOLOR_XRGB(255, 255, 255));
	//	End sprite drawing
	sprite->End();

	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
	/*
		Write your code here...
	*/
	if (msg.message == WM_QUIT)
		return false;
	else if (msg.message != WM_QUIT)
		return true;

}

void Windows::clearWindow()
{
	sprite->Release();
	sprite = NULL;
	texture1->Release();
	texture1 = NULL;
	texture2->Release();
	texture2 = NULL;
	texture3->Release();
	texture3 = NULL;
	font->Release();
	font = NULL;
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}