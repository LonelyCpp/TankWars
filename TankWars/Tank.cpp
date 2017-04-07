#include "Tank.h"
#include <vector>

void Tank::drawCircle(float x, float y, float r)
{
	glBegin(GL_POINTS);
	glPointSize(1);
	for(float i = 0; i < 2 * 3.14159; i += 0.5)
	{
		glVertex2f(x + r * cos(i), y + r * sin(i));
	}
	glEnd();
}

Tank::Tank(int x, int y)
	:healthBar(x + 30, y + 100)
{
	this->x = x;
	this->y = y;
	health = 100;

	hitBox = { 0 + x, 100 + y, 135 + x, 0 + y };
	healthBar.setDim(50, 5);
	healthBar.setFill(health);
}

void Tank::drawHitBox()
{
	glBegin(GL_LINE_LOOP);

	glVertex2f(hitBox.botx, hitBox.boty);
	glVertex2f(hitBox.topx, hitBox.boty);
	glVertex2f(hitBox.topx, hitBox.topy);
	glVertex2f(hitBox.botx, hitBox.topy);

	glEnd();
}


void Tank::draw(bool draw)
{
	//drawHitBox();
	//<base>

	healthBar.draw();
	glColor3ub(66, 74, 59);

	glBegin(GL_POLYGON);

	glVertex2f(5 + x, 42 + y);
	glVertex2f(120 + x, 42 + y);
	glVertex2f(115 + x, 51 + y);
	glVertex2f(8 + x, 51 + y);
	glEnd();

	glBegin(GL_POLYGON);

	glVertex2f(115 + x, 51 + y);
	glVertex2f(107 + x, 64 + y);
	glVertex2f(18 + x, 64 + y);
	glVertex2f(8 + x, 51 + y);
	glEnd();

	
	glColor3ub(120, 134, 107);

	glBegin(GL_POLYGON);

	glVertex2f(5 + x, 42 + y);
	glVertex2f(120 + x, 42 + y);
	glVertex2f(115 + x, 51 + y);
	glVertex2f(8 + x, 51 + y);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(94 + x, 31 + y);
	glVertex2d(14 + x, 31 + y);
	glVertex2d(14 + x, 41 + y);
	glVertex2d(94 + x, 41 + y);

	glEnd();

	glColor3ub(0, 0, 0);

	glBegin(GL_LINES);
	for (int i = 0; i <= 8; i++)
	{
		glVertex2d(14 + x + i * 10, 31 + y);
		glVertex2d(14 + x + i * 10, 41 + y);
	}
	
	glEnd();

	glPointSize(8);
	glBegin(GL_POINTS);
	for(int i = 0; i<7; i++)
		glVertex2f(26 + i*12 + x, 58 + y);
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
	for (int i = 0; i<9; i++)
		glVertex2f(13 + i * 12 + x, 45 + y);
	glEnd();

	glBegin(GL_LINE_LOOP);

	glVertex2f(5 + x, 42 + y);
	glVertex2f(120 + x, 42 + y);
	glVertex2f(115 + x, 51 + y);
	glVertex2f(8 + x, 51 + y);

	glEnd();

	//<cannon>

	glColor3ub(color.r, color.b, color.g);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(54 + x, 25 + y);

	if (armAngle < 0)
		glVertex2f(ARM_LENGTH*cos(armAngle) + (54 + x), ARM_LENGTH*sin(armAngle) + 25 + y);
	else
		glVertex2f(-1 * ARM_LENGTH*cos(armAngle) + (54 + x) , -1 * ARM_LENGTH*sin(armAngle) + 25 + y);

	glEnd();
	glLineWidth(1);

	//</cannon>
	glColor3ub(120, 134, 107);
	glBegin(GL_POLYGON);
	glVertex2d(84 + x, 31 + y);
	glVertex2d(94 + x, 25 + y);
	glVertex2d(14 + x, 25 + y);
	glVertex2d(24 + x, 31 + y);
	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);

	glVertex2d(84 + x, 31 + y);
	glVertex2d(84 + x, 25 + y);
	glVertex2d(24 + x, 25 + y);
	glVertex2d(24 + x, 31 + y);

	glEnd();
	//</base>
}

void Tank::setColor(Color c)
{
	color = c;
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
		{
			health -= 30;
			healthBar.setFill(health);
			return true;
		}
			

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

Weapon* Tank::createWeapon(int power)
{
	Weapon *w;
	if (armAngle < 0)
		w =  new Weapon(ARM_LENGTH*cos(armAngle) + 54 + x, ARM_LENGTH*sin(armAngle) + 15 + y, power, armAngle);
	else
		w = new Weapon(-1 * ARM_LENGTH*cos(armAngle) + 54 + x, -1 * ARM_LENGTH*sin(armAngle) + 15 + y, power, armAngle);

	w->setColor(color);
	return w;
}