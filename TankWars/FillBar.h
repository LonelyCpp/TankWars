#pragma once
#include <GL/freeglut.h>
#include "color.h"

class FillBar
{
	int x;
	int y;
	int width, height;
	float fill;	//percentage fill
	Color fillColor;

public:
	FillBar(int startX, int startY);

	void draw();

	void setFill(float percent);

	void setDim(int width, int height);

	void setFillColor(Color c);

	void erase();
};

