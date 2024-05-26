#include "Figures.hpp"


Location::Location(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Location::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Location::getX() { return x; }
int Location::getY() { return y; }


Point::Point(int x, int y) : Location(x, y) {};

void Point::show(HDC hdc)
{
	SetPixel(hdc, x, y, RGB(0, 0, 0));
}

Barrier::Barrier(int x, int y) : Point(x, y) {};

int Barrier::getRight() {
	return x + right + weightLine * 2;
}
int Barrier::getBottom() {
	return y + bottom + weightLine * 2;
}

void Point::move(int offsetX, int offsetY)
{
	this->x += offsetX;
	this->y += offsetY;
}


Face::Face(int x, int y) : Point(x, y) {};

void Face::onKeyDown(WPARAM wParam) {
	int step = 50;
	switch (wParam) {
	case 'W':
		move(0, -step);
		break;
	case 'S':
		move(0, step);
		break;
	case 'A':
		move(-step, 0);
		break;
	case 'D':
		move(step, 0);
		break;
	}
}

void Face::showContour(HDC hdc) {
	Ellipse(hdc, 0 + x + weightLine, 0 + y + weightLine, 200 + x + weightLine, 200 + y + weightLine);
}

void  Face::showEyes(HDC hdc) {
	Ellipse(hdc, 50 + x + weightLine, 50 + y + weightLine, 80 + x + weightLine, 80 + y + weightLine);
	Ellipse(hdc, 62 + x + weightLine, 62 + y + weightLine, 68 + x + weightLine, 68 + y + weightLine);

	Ellipse(hdc, 120 + x + weightLine, 50 + y + weightLine, 150 + x + weightLine, 80 + y + weightLine);
	Ellipse(hdc, 132 + x + weightLine, 62 + y + weightLine, 138 + x + weightLine, 68 + y + weightLine);
}

void Face::showMouth(HDC hdc) {
	MoveToEx(hdc, 65 + x + weightLine, 150 + y + weightLine, NULL);
	LineTo(hdc, 135 + x + weightLine, 150 + y + weightLine);
}

void Face::show(HDC hdc)
{
	HPEN pen = CreatePen(PS_SOLID, weightLine * 2, RGB(0, 0, 0));
	SelectObject(hdc, pen);

	showContour(hdc);
	showEyes(hdc);
	showMouth(hdc);

	SelectObject(hdc, GetStockObject(BLACK_PEN));
	DeleteObject(pen);
}

int Face::getRight() {
	return x + 200 + weightLine * 2;
}
int Face::getBottom() {
	return y + 200 + weightLine * 2;
}

bool Face::hit(int left, int top, int right, int bottom)
{
	return (!( (x > right) || (y > bottom) || (getRight() < left) || (getBottom() < top) ));
}


Soda::Soda(int x, int y) : Barrier(x, y) { weightLine = 2; };

void Soda::show(HDC hdc)
{
	HPEN pen = CreatePen(PS_SOLID, weightLine * 2, RGB(0, 0, 0));
	SelectObject(hdc, pen);

	Ellipse(hdc, 20 + x + weightLine, 0 + y + weightLine, 80 + x + weightLine, 20 + y + weightLine);
	Arc(hdc, 20 + x + weightLine, 80 + y + weightLine, 80 + x + weightLine, 100 + y + weightLine, 20 + x + weightLine, 90 + y + weightLine, 80 + x + weightLine, 90 + y + weightLine);
	
	MoveToEx(hdc, 20 + x + weightLine, 90 + y + weightLine, NULL);
	LineTo(hdc, 20 + x + weightLine, 10 + y + weightLine);
	MoveToEx(hdc, 80 + x + weightLine, 90 + y + weightLine, NULL);
	LineTo(hdc, 80 + x + weightLine, 10 + y + weightLine);

	TextOutA(hdc, 23 + x, 49 + y, "Баночка", 7);

	SelectObject(hdc, GetStockObject(BLACK_PEN));
	DeleteObject(pen);
}


Plane::Plane(int x, int y) : Barrier(x, y) { weightLine = 5; };

void Plane::show(HDC hdc)
{
	HPEN pen = CreatePen(PS_SOLID, weightLine * 2, RGB(0, 0, 0));
	SelectObject(hdc, pen);

	MoveToEx(hdc, 0 + x + weightLine, 50 + y + weightLine, NULL);
	LineTo(hdc, 90 + x + weightLine, 50 + y + weightLine);
	LineTo(hdc, 100 + x + weightLine, 30 + y + weightLine);

	MoveToEx(hdc, 40 + x + weightLine, 50 + y + weightLine, NULL);
	LineTo(hdc, 80 + x + weightLine, 0 + y + weightLine);
	MoveToEx(hdc, 40 + x + weightLine, 50 + y + weightLine, NULL);
	LineTo(hdc, 80 + x + weightLine, 100 + y + weightLine);

	SelectObject(hdc, GetStockObject(BLACK_PEN));
	DeleteObject(pen);
}


DeadFace::DeadFace(int x, int y) : Face(x, y) {};

void DeadFace::showEyes(HDC hdc) {
	MoveToEx(hdc, 50 + x + weightLine, 50 + y + weightLine, NULL);
	LineTo(hdc, 80 + x + weightLine, 80 + y + weightLine);
	MoveToEx(hdc, 80 + x + weightLine, 50 + y + weightLine, NULL);
	LineTo(hdc, 50 + x + weightLine, 80 + y + weightLine);

	MoveToEx(hdc, 120 + x + weightLine, 50 + y + weightLine, NULL);
	LineTo(hdc, 150 + x + weightLine, 80 + y + weightLine);
	MoveToEx(hdc, 150 + x + weightLine, 50 + y + weightLine, NULL);
	LineTo(hdc, 120 + x + weightLine, 80 + y + weightLine);
}


SurpriseFace::SurpriseFace(int x, int y) : Face(x, y) {};

void SurpriseFace::showMouth(HDC hdc) {
	Ellipse(hdc, 65 + x + weightLine, 115 + y + weightLine, 135 + x + weightLine, 185 + y + weightLine);
}


SmileFace::SmileFace(int x, int y) : Face(x, y) {};

void SmileFace::showMouth(HDC hdc) {
	Arc(hdc, 65 + x + weightLine, 98 + y + weightLine, 135 + x + weightLine, 167 + y + weightLine, 65 + x + weightLine, 133 + y + weightLine, 135 + x + weightLine, 133 + y + weightLine);
}


CryFace::CryFace(int x, int y) : SmileFace(x, y) {};

void CryFace::showEyes(HDC hdc) {
	Ellipse(hdc, 50 + x + weightLine, 50 + y + weightLine, 80 + x + weightLine, 80 + y + weightLine);
	Ellipse(hdc, 62 + x + weightLine, 62 + y + weightLine, 68 + x + weightLine, 68 + y + weightLine);
	Ellipse(hdc, 60 + x + weightLine, 85 + y + weightLine, 70 + x + weightLine, 100 + y + weightLine);

	Ellipse(hdc, 120 + x + weightLine, 50 + y + weightLine, 150 + x + weightLine, 80 + y + weightLine);
	Ellipse(hdc, 132 + x + weightLine, 62 + y + weightLine, 138 + x + weightLine, 68 + y + weightLine);
	Ellipse(hdc, 130 + x + weightLine, 85 + y + weightLine, 140 + x + weightLine, 100 + y + weightLine);
}

void CryFace::showMouth(HDC hdc) {
	Arc(hdc, 65 + x + weightLine, 133 + y + weightLine, 135 + x + weightLine, 202 + y + weightLine, 135 + x + weightLine, 167 + y + weightLine, 65 + x + weightLine, 167 + y + weightLine);
}
