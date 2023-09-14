#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Sow.h"
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam);

double pi = 3.14, al=1.570796326,dy=1,dx=0;
int i, j, rx, xball = 287, yball = 350, a[10] = {1,1,1,1,1,1,1,1,1,1},z,l;
_Bool up=0, lft=0,rgt=0,k=1;
POINT px;
LPSTR pl;

void PaintGrid(HDC hdc);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowsProc;
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "SimpleApplication";

	RegisterClass(&wc);

	hWnd = CreateWindow("SimpleApplication",
		"Arkanoid",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		600,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//SetTimer(hWnd, IDT_TIMER1, 500, NULL, (TIMERPROC)NULL);
	SetTimer(hWnd, IDT_TIMER2, 3, (TIMERPROC)NULL);

	while (GetMessage(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT r;


	RECT platform;
	platform.left = 0;
	platform.top = 390;
	platform.right = 600;
	platform.bottom = 430;

	static HPEN hpenGrid;
	static HPEN hpenGrid1;
	static HBRUSH hbrush;
	static CHOOSECOLOR cc;
	static COLORREF CustColors[16];
	switch (uMsg)
	{
	case WM_CREATE:
		hpenGrid = CreatePen(PS_SOLID, 4, RGB(197, 29, 52));
		hpenGrid1 = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
		hbrush = CreateSolidBrush(RGB(197, 29, 52));

		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hWnd;
		cc.lpCustColors = CustColors;
		cc.Flags = CC_RGBINIT;
		SetCursorPos(300, 420);
		z = rand()%4;
		ShowCursor(FALSE);

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &r);
		SelectObject(hdc, hpenGrid);
		PaintGrid(hdc, 0, 0);
		EndPaint(hWnd, &ps);
		
		break;

	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		SelectObject(hdc, hpenGrid1);
		Rectangle(hdc, rx, 400, rx + 120, 420);
		rx = LOWORD(lParam);
		SelectObject(hdc, hpenGrid);
		Rectangle(hdc, rx, 400, rx + 120, 420);
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, &pl, TRUE);
		
		break;

	case WM_TIMER:
		switch (wParam)
		{
			
		case IDT_TIMER2: 
			hdc = GetDC(hWnd);
			GetClientRect(hWnd, &r);
			SelectObject(hdc, hpenGrid1);
			Ellipse(hdc, xball, yball, xball + 26, yball + 26);
			//Платфоpма
			if ((xball > rx) && (xball < rx + 120) && (yball == 374))
			{
			if (k)
				
				{
					dx=z;
					k = 0;
				}
			up = 1;
				//al = (rand(4) +1) * pi / 6;

				

			}
			
			//Потолок
			if (yball == 33)
			{
				
				l=xball/60;
				if (a[l] == 1)
				{
					a[l] = 0;
					up = 0;
					//n++;
				}
				
				hdc = GetDC(hWnd);
				GetClientRect(hWnd, &r);
				SelectObject(hdc, hpenGrid1);
				Rectangle(hdc, l * 60, 0, l * 60 + 60, 30);
				ReleaseDC(hWnd, hdc);
				InvalidateRect(hWnd, &r, FALSE);

			}
			if (yball == 13)
			{
				up = 0;
			}
			//Левая стена
			if (xball == 0)
			{
				lft = 1;
				rgt = 0;
			}
			//Пpавая стенка
			if (xball == 574)
			{
				rgt = 1;
				lft = 0;
			}
			//Условие потолка
			if (up)
			{
					
				yball=yball-dy;
				
			
			}
				//Гpавитация
			if (!up)
				{
					

					yball = yball + dy;

				}
			
			
			//Условие левой стены
			if (lft)
			{
				
				
				xball = xball + dx;
				
			}
			
			//Условие на пpавой стенке
			if (rgt)
			{
				xball = xball - dx;
			}
			//Не касается стен
			if ((!lft)&&(!rgt))
			xball = xball + dx;
			//Падение шаpика
			if (yball == 620)
			{
				for (i = 0; i < 10; i++)
					a[i] = 1;
				yball = 350;
				xball = 287;
				SetCursorPos(300, 420);
			}
			SelectObject(hdc, hpenGrid);
			Ellipse(hdc, xball, yball, xball + 26, yball + 26);
			ReleaseDC(hWnd, hdc);
			InvalidateRect(hWnd, &r, FALSE);

			break;
		}

		break;

	case WM_DESTROY:
		DeleteObject(hpenGrid);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void PaintGrid(HDC hdc)
{
	for (i = 0; i < 10; i++)
		
		if (a[i] == 1)
			Rectangle(hdc, i * 60, j * 30, i * 60 + 60, j * 30 + 30);	
}
