#include "Tank.h"


Tank::Tank(int x, int y)
{
	this->x = x;
	this->y = y;

	hitBox = { 0 + x, 100 + y, 135 + x, 0 + y };
}



void Tank::draw(bool draw)
{


	glColor3ub(45, 53, 57);
	//<base>
	glBegin(GL_POLYGON);
	glVertex2d(7 + x, 53 + y);
	glVertex2d(130 + x, 53 + y);
	glVertex2d(108 + x, 83 + y);
	glVertex2d(16 + x, 83 + y);
	glVertex2d(2 + x, 73 + y);
	glVertex2d(2 + x, 58 + y);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(9 + x, 48 + y);
	glVertex2d(111 + x, 48 + y);
	glVertex2d(91 + x, 34 + y);
	glVertex2d(18 + x, 34 + y);
	glEnd();

	//<cannon>

	glColor3f(0, 1, 0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(54 + x, 15 + y);

	if (armAngle < 0)
		glVertex2f(ARM_LENGTH*cos(armAngle) + 54 + x, ARM_LENGTH*sin(armAngle) + 15 + y);
	else
		glVertex2f(-1 * ARM_LENGTH*cos(armAngle) + 54 + x, -1 * ARM_LENGTH*sin(armAngle) + 15 + y);

	glEnd();
	glLineWidth(1);

	//</cannon>
	glColor3ub(45, 53, 57);
	glBegin(GL_POLYGON);
	glVertex2d(84 + x, 31 + y);
	glVertex2d(84 + x, 15 + y);
	glVertex2d(24 + x, 15 + y);
	glVertex2d(24 + x, 31 + y);
	glEnd();
	//</base>
}

void Tank::erase()
{
	glColor3ub(gameGlobals::backColor.r, gameGlobals::backColor.g, gameGlobals::backColor.b);
	glBegin(GL_POLYGON);
	glVertex2d(hitBox.botx - 30, hitBox.boty);
	glVertex2d(hitBox.botx - 30, hitBox.topy - 65);
	glVertex2d(hitBox.topx, hitBox.topy - 65);
	glVertex2d(hitBox.topx, hitBox.boty);
	glEnd();
}

bool Tank::didHit(int checkX, int checkY)
{
	if (checkX > hitBox.botx && checkX < hitBox.topx)
		if (checkY < hitBox.boty && checkY > hitBox.topy)
			return true;

	return false;
}

void Tank::updatePos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Tank::updateAngle(int mouseX, int mouseY)
{
	if (mouseY < (15 + y))
		armAngle = atan(((15 + y) - mouseY) / (float)((54 + x) - mouseX));
}

Weapon* Tank::createWeapon()
{
	if (armAngle < 0)
		return new Weapon(ARM_LENGTH*cos(armAngle) + 54 + x, ARM_LENGTH*sin(armAngle) + 15 + y, 120, armAngle);
	else
		return new Weapon(-1 * ARM_LENGTH*cos(armAngle) + 54 + x, -1 * ARM_LENGTH*sin(armAngle) + 15 + y, 120, armAngle);

}