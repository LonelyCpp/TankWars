#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include "color.h"
#include "Weapon.h"
#include "FillBar.h"

class Tank {

	int x = 0, y = 0;
	float armAngle = 0;
	const int ARM_LENGTH = 80;
	Color color = { 255, 0 , 0 };

	float health;
	FillBar healthBar;

	struct { int botx, boty, topx, topy; } hitBox;

	void drawCircle(float x, float y, float r);
	void drawHitBox();
public:

	Tank(int x, int y);

	void draw(bool draw = true);

	void setColor(Color c);

	void erase();

	bool didHit(int checkX, int checkY);

	void updatePos(int x, int y);

	void updateAngle(int mouseX, int mouseY);

	bool isDead() { return health < 0; }

	Weapon* createWeapon(int power = 120);
};