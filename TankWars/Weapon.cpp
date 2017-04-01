#include "Weapon.h"


Weapon::Weapon(int sx, int sy, int pow, float agl)
{
	startX = sx;
	startY = sy;
	angle = agl;
	power = pow;

	if (angle < 0)
		directionVector = 1;
	else
		directionVector = -1;

	color = { 255, 0, 0 };
}

void Weapon::setColor(Color c)
{
	color = c;
}

std::pair<int, int> Weapon::draw(float time)
{
	int x = directionVector * power * cos(angle) * time;
	int y = directionVector * power * sin(angle) * time + (0.5)*(9.8)*(time * time);

	glPointSize(10);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2f(startX + x, startY + y);

	glEnd();

	return std::pair<int, int>(startX + x, startY + y);
}
void Weapon::erase(float time)
{
	int x = directionVector * power * cos(angle) * time;
	int y = directionVector * power * sin(angle) * time + (0.5)*(9.8)*(time * time);

	glPointSize(10);
	glColor3ub(gameGlobals::backColor.r, gameGlobals::backColor.g, gameGlobals::backColor.b);
	glBegin(GL_POINTS);
	glVertex2f(startX + x, startY + y);
	glEnd();

}

void Weapon::explodeAnime(float time)
{
	float x = startX + directionVector * power * cos(angle) * time;
	float y = startY + directionVector * power * sin(angle) * time + (0.5)*(9.8)*(time * time);


	for (float i = 0; i < 10; i += 0.05)
	{
		glColor3ub(255, 0, 0);
		drawCircle(x, y, i * 4 + 1);
		glutSwapBuffers();
	}

	glColor3ub(gameGlobals::backColor.r, gameGlobals::backColor.g, gameGlobals::backColor.b);
	glPointSize(70);
	drawCircle(x, y, 10 * 4 + 1);
	glutSwapBuffers();
	drawCircle(x, y, 10 * 4 + 1);
	glutSwapBuffers();
}

void Weapon::drawCircle(int x, int y, int r)
{
	glBegin(GL_LINES);
	for (float i = 0; i < 2 * 3.2; i += 0.1)
	{
		glVertex2f(x, y);
		glVertex2f(x + r*cos(i), y + r*sin(i));
	}
	glEnd();
}
