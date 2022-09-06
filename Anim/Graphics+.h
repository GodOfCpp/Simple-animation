#pragma once

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
//=============================================================================

HWND hWnd;

class Graphics
{
private:
	static HPEN hPen;
	static HBRUSH hBrush;
	static HBITMAP bmMem;
	static HANDLE  hOld;
	static int wid, heg;
public:
	static HDC dc;
	static HDC dcMem;

	static void Set_pen(HDC, COLORREF, int);
	static void Set_brush(HDC, COLORREF, bool);
	static void Line(HDC, int, int, int, int);
	static void Point(HDC, int, int, COLORREF);
	static void Osi(HDC);
	static int GetWid() { return wid; }
	static int GetHeg() { return heg; }
	//Метод преобразования нормализованных
	//координат в экранные
	static void WinCoor(POINT &, const float, const float);
	//Метод преобразования экранных
	//координат в нормализованные
	static void NormCoor(const POINT, float&, float&);

	static void InitGraphics(HWND);
	~Graphics();
};
HBRUSH Graphics::hBrush = NULL;
HPEN Graphics::hPen = NULL;
HDC Graphics::dc = NULL;
HDC Graphics::dcMem = NULL;
HBITMAP Graphics::bmMem = NULL;
HANDLE  Graphics::hOld = NULL;
int Graphics::wid = 0;
int Graphics::heg = 0;

//Конструктор дополнен командами,
//реализующими создание внутренней памяти
void Graphics::InitGraphics(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	wid = rect.right;
	heg = rect.bottom;
	dc = GetDC(hWnd);
	Set_pen(dc,RGB(255, 255, 255), 1);
	Set_brush(dc,RGB(255, 255, 255), true);

	//Создается контекст памяти, совместимый
	//с контекстом отображения реального устройства
	dcMem = CreateCompatibleDC(Graphics::dc);

	//Для рисования в памяти из ее ячеек надо образовать структуру,
	//подобную экрану. Для этого удобно использовать
	//битовую карту(HBITMAP).
	//В памяти будем рисовать на битовой карте
	bmMem = CreateCompatibleBitmap(Graphics::dc, wid, heg);

	// Помещаем битовую карту в контекст памяти
	hOld = SelectObject(dcMem, bmMem);
}

Graphics::~Graphics()
{
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(bmMem);
	DeleteDC(dcMem);
	ReleaseDC(hWnd, dc);
	DeleteDC(dc);
}

//В методах Set_pen() и Set_brush()
//перед созданием новых объектов (перо и кисть)
//необходимо удалять старые
void Graphics::Set_pen(HDC dc, COLORREF col, int w)
{
	DeleteObject(hPen);
	hPen = CreatePen(PS_INSIDEFRAME, w, col);
	SelectObject(dc, hPen);
}
void Graphics::Set_brush(HDC dc, COLORREF col, bool empty)
{
	DeleteObject(hBrush);
	empty ? hBrush = ::CreateSolidBrush(col) : 
			hBrush = ::CreateSolidBrush(NULL_BRUSH);
	::SelectObject(dc, hBrush);
}
void Graphics::Line(HDC dc,int x1, int y1, int x2, int y2)
{
	MoveToEx(dc, x1, y1, NULL);
	LineTo(dc, x2, y2);
}
void Graphics::Point(HDC dc, int x, int y, COLORREF col)
{
	SetPixel(dc, x, y, col);
}
void Graphics::Osi(HDC dc)
{
	Set_pen(dc,RGB(255, 0, 0), 1);
	Line(dc, 0, heg / 2, wid - 1, heg / 2);
	Set_pen(dc,RGB(0, 255, 0), 1);
	Line(dc, wid / 2, 0, wid / 2, heg - 1);
}

void Graphics::WinCoor(POINT &pt, const float fx, const float fy)
{
	pt.x = int((fx + 1.f) * (wid / 2.f));
	pt.y = heg - int((fy + 1.f) * (heg / 2.f));
}

void Graphics::NormCoor(const POINT pt, float &fx, float &fy)
{
	fx = (pt.x - wid / 2.f) / (wid / 2.f);
	fy = (heg / 2.f - pt.y) / (heg / 2.f);
}

//Переопределение Graphics
typedef Graphics gr;

