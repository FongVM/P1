#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "resource.h"
#include <string>

class Windows
{
private:
	//	Window handle
	HWND g_hWnd;
	HINSTANCE hInstance;
	//	Window's structure
	WNDCLASS wndClass;
	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3DDevice9 * d3dDevice;
	LPDIRECT3DTEXTURE9 texture1;
	LPDIRECT3DTEXTURE9 texture2;
	LPDIRECT3DTEXTURE9 texture3;
	LPD3DXSPRITE sprite;
	LPD3DXFONT font;
	RECT spriteRect;
	RECT rectList[16];
	RECT textRect;
	RECT textRect2;
	D3DCOLOR cursorColor;
public:
	Windows();
	void createWindow();
	bool createDirectX();
	bool createSprite();
	bool createFont();
	void toggleScreen();
	void changeColor();
	void clearWindow();
	void color();
	bool loop();
};

