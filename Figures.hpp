#ifndef LR_OOP2_FIGURES
#define LR_OOP2_FIGURES

#include <windows.h>


class Location;
class Point;
class Barrier;

class IMeasure;

class Face;

class Soda;
class Plane;

class DeadFace;
class SurpriseFace;
class SmileFace;
class CryFace;


class Location
{
 protected:
	int x;
	int y;
 public:
	Location(int x, int y);
	void setXY(int x, int y);
	int getX();
	int getY();
	virtual void show(HDC hdc) = 0;
};

class Point : public Location
{
 public:
	Point(int x, int y);
	void move(int offsetX, int offsetY);
	virtual void show(HDC hdc);
};

class IMeasure {
	virtual int getRight() = 0;
	virtual int getBottom() = 0;
};

class Barrier : public Point, public IMeasure
{
 public:
	 int weightLine = 0;
	 Barrier(int x, int y);
	 int right = 100;
	 int bottom = 100;
	 int getRight();
	 int getBottom();
};

class Face : public Point, public IMeasure
{
 protected:
	int weightLine = 3;
 public:
	Face(int x, int y);
	void onKeyDown(WPARAM wParam);
	void showContour(HDC hdc);
	virtual void showEyes(HDC hdc);
	virtual void showMouth(HDC hdc);
	void show(HDC hdc);
	int getRight();
	int getBottom();
	bool hit(int left, int top, int right, int bottom);
};

class Soda : public Barrier
{
 public:
	 Soda(int x, int y);
	 void show(HDC hdc);
};

class Plane : public Barrier
{
 public:
	Plane(int x, int y);
	void show(HDC hdc);
};

class DeadFace : public Face
{
 public:
	 DeadFace(int x, int y);
	 void showEyes(HDC hdc);
};

class SurpriseFace : public Face
{
 public:
	SurpriseFace(int x, int y);
	void showMouth(HDC hdc);
};

class SmileFace : public Face
{
 public:
	SmileFace(int x, int y);
	void showMouth(HDC hdc);
};

class CryFace : public SmileFace
{
 public:
	CryFace(int x, int y);
	void showEyes(HDC hdc);
	void showMouth(HDC hdc);
};

#endif
