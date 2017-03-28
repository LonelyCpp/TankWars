#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <Windows.h>
#include <mmsystem.h>

void display();
void changeSize(int w, int h);
void myInit();
void idleFunc(int t);
void mouseMove(int x, int y);
void mouseClick(int button, int s, int x, int y);
void drawCircle(int x, int y, int r);
enum { SELECT_ANGLE = 0, SELECT_POWER, SHOOT };
struct Color { float r, g, b; };

namespace gameGlobals {
	int state = 0;	
	float time = 0;
	bool turn = 0;	
	Color backColor = { 255, 133, 82 };
}

class Weapon
{
	int startX, startY, power;
	float angle;
	int directionVector;
	Color color;
public:

	Weapon(int sx, int sy, int pow, float agl)
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

	void setColor(Color c)
	{
		color = c;
	}

	std::pair<int, int> draw(float time)
	{
		int x = directionVector * power * cos(angle) * time;
		int y = directionVector * power * sin(angle) * time + (0.5)*(9.8)*(time * time);

		glPointSize(10);
		glColor3ub(color.r, color.g, color.b);
		glBegin(GL_POINTS);
		glVertex2f(startX +  x, startY + y);

		glEnd();

		return std::pair<int, int>(startX + x, startY + y);
	}
	void erase(float time)
	{
		int x = directionVector * power * cos(angle) * time;
		int y = directionVector * power * sin(angle) * time + (0.5)*(9.8)*(time * time);

		glPointSize(10);
		glColor3ub(gameGlobals::backColor.r, gameGlobals::backColor.g, gameGlobals::backColor.b);
		glBegin(GL_POINTS);
		glVertex2f(startX + x, startY + y);
		glEnd();

	}

	void explodeAnime(float time)
	{
		float x = startX + directionVector * power * cos(angle) * time;
		float y = startY + directionVector * power * sin(angle) * time + (0.5)*(9.8)*(time * time);

		
		for (float i = 0; i < 10; i+=0.05)
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

}*basicBomb;

class Tank {

	int x = 0, y = 0;
	float armAngle = 0;
	const int ARM_LENGTH = 80;
	struct { int botx, boty, topx, topy; } hitBox;

public:

	Tank(int x, int y)
	{
		this->x = x;
		this->y = y;

		hitBox = { 0 + x, 100 + y, 135 + x, 0 + y };
	}

	void draw(bool draw = true) 
	{


		glColor3ub(45, 53, 57);
		//<base>
		glBegin(GL_POLYGON);
		glVertex2d(7	+ x, 53 + y);
		glVertex2d(130	+ x, 53 + y);
		glVertex2d(108	+ x, 83 + y);
		glVertex2d(16	+ x, 83 + y);
		glVertex2d(2	+ x, 73 + y);
		glVertex2d(2	+ x, 58 + y);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2d(9	+ x, 48 + y);
		glVertex2d(111	+ x, 48 + y);
		glVertex2d(91	+ x, 34 + y);
		glVertex2d(18	+ x, 34 + y);
		glEnd();

		//<cannon>

		glColor3f(0, 1, 0);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex2f(54 + x, 15 + y);

		if(armAngle < 0)
			glVertex2f(ARM_LENGTH*cos(armAngle) + 54 + x, ARM_LENGTH*sin(armAngle) + 15 + y);
		else
			glVertex2f(-1*ARM_LENGTH*cos(armAngle) + 54 + x, -1 * ARM_LENGTH*sin(armAngle) + 15 + y);

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

	void erase()
	{
		glColor3ub(gameGlobals::backColor.r, gameGlobals::backColor.g, gameGlobals::backColor.b);
		glBegin(GL_POLYGON);
		glVertex2d(hitBox.botx - 30, hitBox.boty);
		glVertex2d(hitBox.botx - 30, hitBox.topy-65);
		glVertex2d(hitBox.topx, hitBox.topy-65);
		glVertex2d(hitBox.topx, hitBox.boty);
		glEnd();
	}

	bool didHit(int checkX, int checkY)
	{
		if ( checkX > hitBox.botx && checkX < hitBox.topx)
			if(checkY < hitBox.boty && checkY > hitBox.topy)
				return true;

		return false;
	}

	void updatePos(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void updateAngle(int mouseX, int mouseY)
	{
		if(mouseY < (15 + y))
		armAngle = atan(((15 + y) - mouseY) / (float)((54 + x) - mouseX));
	}

	Weapon* createWeapon()
	{
		if (armAngle < 0)
			return new Weapon(ARM_LENGTH*cos(armAngle) + 54 + x, ARM_LENGTH*sin(armAngle) + 15 + y, 120, armAngle);
		else
			return new Weapon(-1 * ARM_LENGTH*cos(armAngle) + 54 + x, -1 * ARM_LENGTH*sin(armAngle) + 15 + y, 120, armAngle);

	}

}tank[2] = { Tank(50, 500), Tank(1100, 500) };

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
		if (checkY > (y + terrainEquation(checkX - x)) )
			return true;
		return false;
	}
}mountain(-300, 600);

int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Tank Wars");
	myInit();
	
	gameGlobals::state = SELECT_ANGLE;

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	//glutIdleFunc(idleFunc);
	glutTimerFunc(17, idleFunc, 0);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);

	glutMainLoop();
	
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);

	tank[0].draw(true);
	tank[1].draw(true);
	mountain.draw();
	glutSwapBuffers();
}

void idleFunc(int t)
{
	if (gameGlobals::state == SHOOT)
	{
		//glClear(GL_COLOR_BUFFER_BIT);

		std::pair<int, int> bombPos = basicBomb->draw(gameGlobals::time += 0.1);
		
		bool stopBomb = bombPos.second > 600 || mountain.didHit(bombPos.first, bombPos.second);

		stopBomb = stopBomb || tank[0].didHit(bombPos.first, bombPos.second) || tank[1].didHit(bombPos.first, bombPos.second);

		if ( !stopBomb )
		{
			tank[0].draw(true);
			tank[1].draw(true);
			glutSwapBuffers();
			basicBomb->erase(gameGlobals::time - 0.1);
		}
		else
		{
			PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC);
			basicBomb->explodeAnime(gameGlobals::time);
			glutSwapBuffers();
			basicBomb->erase(gameGlobals::time);
			basicBomb->erase(gameGlobals::time - 0.1);
			glutSwapBuffers();
			basicBomb->erase(gameGlobals::time - 0.1);
			basicBomb->erase(gameGlobals::time);
			gameGlobals::state = 0;
			gameGlobals::time = 0;
			gameGlobals::turn = !gameGlobals::turn;
		}
	}

	glutTimerFunc(14, idleFunc, 0);
}

void mouseMove(int x, int y)
{

	//glClear(GL_COLOR_BUFFER_BIT);

	switch (gameGlobals::state)
	{
	case SELECT_ANGLE : 
		tank[gameGlobals::turn].erase();
		tank[gameGlobals::turn].updateAngle(x, y);
		tank[0].draw(true);
		tank[1].draw(true);
		mountain.draw();
		glutSwapBuffers();
		break;

	case SELECT_POWER:
		break;
	}

}

void mouseClick(int button, int s, int x, int y)
{
	if (s == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (gameGlobals::state == SHOOT)
			return;

		gameGlobals::state = (gameGlobals::state + 1) % 3;
		
		if (gameGlobals::state == 2)
		{
			basicBomb = tank[gameGlobals::turn].createWeapon();
			basicBomb->setColor({ 0, (float)!gameGlobals::turn*255, (float)gameGlobals::turn*255 });
			PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC);
		}
			
	}
		
}

void changeSize(int w, int h) 
{
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, h, 0.0);

}

void myInit()
{
	glClearColor(gameGlobals::backColor.r/255.0, gameGlobals::backColor.g/255.0, gameGlobals::backColor.b/255.0, 0 );
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 699.0, 699.0, 0.0);
}

void drawCircle(int x, int y, int r)
{
	glBegin(GL_LINES);
	for (float i = 0; i < 2 * 3.2; i += 0.1)
	{
		glVertex2f(x, y);
		glVertex2f(x + r*cos(i), y + r*sin(i));
	}
	glEnd();
}