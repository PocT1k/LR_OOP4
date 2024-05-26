/*************************************************************
*                    КАФЕДРА № 304 2 КУРС                    *
*------------------------------------------------------------*
* Project Type   : Win32 Console Application                 *
* Project Name   : LR OOP3                                   *
* File Name      : LR OOP3.cpp                               *
* Language       : C++                                       *
* Programmers(s) : Новиков К.А.                              *
* Modifyed by    :                                           *
* Lit sourse     :                                           *
* Created        : 12/05/23                                  *
* Last Revision  : 12/05/23                                  *
* Comments(s)    : Динамический полиморфизм                  *
*************************************************************/

#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>

#include "Figures.hpp"


static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("Labwork");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), szTitle, NULL);
		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1024, 512, NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		MessageBox(NULL, _T("Call to CreateWindow failed!"), szTitle, NULL);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//Инициализаци объектов
int startX = 700, startY = 0;

Soda soda(startX * 2 + 200, 50);
Plane plane(0, 50);

Face *face1 = new Face(startX, startY);
DeadFace *face2 = new DeadFace(startX, startY);
SurpriseFace *face3 = new SurpriseFace(startX, startY);
SmileFace *face4 = new SmileFace(startX, startY);
CryFace *face5 = new CryFace(startX, startY);

//Массив переходов
int faceNow = 0;
Face* faceArr[5] = { face1, face2, face3, face4, face5 };
Face* facePtr = faceArr[faceNow];

//Матрица переходов
int transitionMatrix[2][5] = {
	{ 3, 1, 1, 2, 0 },
	{ 2, 0, 4, 0, 4 }
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");

	switch (message) {
	case WM_KEYDOWN:
	{
		facePtr->onKeyDown(wParam);

		if (facePtr->hit(soda.getX(), soda.getY(), soda.getRight(), soda.getBottom()) == 1) {
			faceNow = transitionMatrix[0][faceNow];
			facePtr = faceArr[faceNow];
			facePtr->setXY(startX, startY);
		}

		if (facePtr->hit(plane.getX(), plane.getY(), plane.getRight(), plane.getBottom()) == 1) {
			faceNow = transitionMatrix[1][faceNow];
			facePtr = faceArr[faceNow];
			facePtr->setXY(startX, startY);
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		facePtr->show(hdc);
		soda.show(hdc);
		plane.show(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}
