#pragma once

#include <GL/freeglut.h>
#include <cmath>

class Terrain
{
	int x, y;

public:
	Terrain(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	float terrainEquation(float x)
	{
		return (400 * sin(x / 200.0) + 100 * cos(x / 80.0) + 100 * cos(x / 80.0));
	}

	void draw()
	{
		glPointSize(1);

		for (float i = 0; i < 2000; i++)
		{
			glPointSize(5);
			glColor3ub(85, 63, 35);
			glBegin(GL_POINTS);
			glVertex2f(x + i, y + terrainEquation(i));
			glEnd();

			glColor3ub(58, 95, 11); //  Leaf Green
			glBegin(GL_LINES);
			glVertex2f(x + i, y + terrainEquation(i));
			glVertex2f(x + i, 1000);
			glEnd();

		}


		glBegin(GL_POLYGON);
		glColor3ub(58, 95, 11);	//  Leaf Green
		glVertex2d(0, 600);
		glVertex2d(2000, 600);
		glColor3ub(85, 63, 35);	//mud brown
		glVertex2d(2000, 800);
		glVertex2d(0, 1000);
		glEnd();

	}

	bool didHit(float checkX, float checkY)
	{
		if (checkY > (y + terrainEquation(checkX - x)))
			return true;
		return false;
	}
};