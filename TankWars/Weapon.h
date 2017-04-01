#pragma once
#include "color.h"
#include <GL/freeglut.h>
#include <utility>
#include <cmath>
class Weapon
{
	int startX, startY, power;
	float angle;
	int directionVector;
	Color color;

public:

	Weapon(int sx, int sy, int pow, float agl);
	
	void setColor(Color c);
	
	std::pair<int, int> draw(float time);
	
	void erase(float time);
	
	void explodeAnime(float time);
	
	void drawCircle(int x, int y, int r);

};