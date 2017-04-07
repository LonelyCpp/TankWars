#include "Terrain.h"
#include <random>
#include <time.h>
Terrain::Terrain(int x, int y)
{
	this->x = x;
	this->y = y;
}

float Terrain::terrainEquation(float x)
{
	return (400 * sin(x / 200.0) + 100 * cos(x / 80.0) + 100 * cos(x / 80.0));
}

void Terrain::draw()
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
	glVertex2d(0, y);
	glVertex2d(2000, y);
	glColor3ub(85, 63, 35);	//mud brown
	glVertex2d(2000, 2000);
	glVertex2d(0, 1000);
	glEnd();

	glColor3ub(gameGlobals::backColor.r, gameGlobals::backColor.g, gameGlobals::backColor.b);
	for (int i = 0; i < crators.size(); i++)
	{
		drawCircle(crators[i].first, crators[i].second, 41);
	}



}

bool Terrain::didHit(float checkX, float checkY)
{
	if (checkY > y)
	{
		crators.push_back({ checkX, checkY });
		return true;
	}
		
	if (checkY > (y + terrainEquation(checkX - x)))
	{
		crators.push_back({ checkX, checkY });
		return true;
	}
		
	return false;
}

void Terrain::drawCircle(int x, int y, int r)
{
	glBegin(GL_LINES);
	for (float i = 0; i < 2 * 3.2; i += 0.1)
	{
		glVertex2f(x, y);
		glVertex2f(x + r*cos(i), y + r*sin(i));
	}
	glEnd();
}
