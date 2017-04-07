#pragma once

#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include "color.h"
class Terrain
{
	int x, y;
	std::vector< std::pair<int, int> > crators;
	void drawCircle(int x, int y, int r);

public:
	Terrain(int x, int y);

	float terrainEquation(float x);

	void draw();

	bool didHit(float checkX, float checkY);
};