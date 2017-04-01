#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include "color.h"
#include "Weapon.h"

class Tank {

	int x = 0, y = 0;
	float armAngle = 0;
	const int ARM_LENGTH = 80;
	struct { int botx, boty, topx, topy; } hitBox;

public:

	Tank(int x, int y);

	void draw(bool draw = true);

	void erase();

	bool didHit(int checkX, int checkY);

	void updatePos(int x, int y);

	void updateAngle(int mouseX, int mouseY);

	Weapon* createWeapon();
};