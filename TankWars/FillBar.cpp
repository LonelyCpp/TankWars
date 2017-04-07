#include "FillBar.h"



FillBar::FillBar(int startX, int startY)
{
	x = startX;
	y = startY;

	width = 100;
	height = 1;

	fillColor = { 0, 255, 0 };
	fill = 0;
}

void FillBar::draw()
{
	glColor3ub(0, 0, 0);

	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();

	glColor3ub(fillColor.r, fillColor.g, fillColor.b);

	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + fill * width, y);
	glVertex2f(x + fill * width, y + height);
	glVertex2f(x, y + height);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();

}

void FillBar::setFill(float percent)
{
	fill = 0.01 * percent;
}

void FillBar::setDim(int width, int height)
{
	this->height = height;
	this->width = width;
}

void FillBar::setFillColor(Color c)
{
	fillColor = c;
}

void FillBar::erase()
{
	glColor3ub(gameGlobals::backColor.r, gameGlobals::backColor.g, gameGlobals::backColor.b);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}
