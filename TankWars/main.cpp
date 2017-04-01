#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#include <Windows.h>
#include <mmsystem.h>
#include "color.h"
#include "Weapon.h"
#include "Tank.h"
#include "Terrain.h"

void display();
void changeSize(int w, int h);
void WeaponDriver(int t);
void mouseMove(int x, int y);
void mouseClick(int button, int s, int x, int y);
enum { SELECT_ANGLE = 0, SELECT_POWER, SHOOT };



namespace gameGlobals {
	int state = 0;	
	float time = 0;
	bool turn = 0;	
	Color backColor = { 255, 133, 82 };
}


Weapon *basicBomb = NULL;
Tank tank[2] = { Tank(50, 500), Tank(1100, 500) };
Terrain mountain(-300, 600);


int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Tank Wars");

	//-- My Init --
	glClearColor(gameGlobals::backColor.r / 255.0, gameGlobals::backColor.g / 255.0, gameGlobals::backColor.b / 255.0, 0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 699.0, 699.0, 0.0);
	//-- 
	
	gameGlobals::state = SELECT_ANGLE;

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	
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

void WeaponDriver(int t)
{
	if (gameGlobals::state == SHOOT)
	{
		std::pair<int, int> bombPos = basicBomb->draw(gameGlobals::time += 0.1);

		//-- check if the bomb has hit anything
		
		bool stopBomb = bombPos.second > 600 || mountain.didHit(bombPos.first, bombPos.second);

		stopBomb = stopBomb || tank[0].didHit(bombPos.first, bombPos.second) || tank[1].didHit(bombPos.first, bombPos.second);

		//--

		if ( !stopBomb )
		{
			tank[0].draw(true);
			tank[1].draw(true);
			mountain.draw();
			glutSwapBuffers();
			basicBomb->erase(gameGlobals::time - 0.1);
		}
		else
		{
			PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC);
			basicBomb->explodeAnime(gameGlobals::time);
			glutSwapBuffers();

			/*
			basicBomb->erase(gameGlobals::time);
			basicBomb->erase(gameGlobals::time - 0.1);
			glutSwapBuffers();
			basicBomb->erase(gameGlobals::time - 0.1);
			basicBomb->erase(gameGlobals::time);
			*/

			delete basicBomb;
			basicBomb = NULL;

			gameGlobals::state = 0;
			gameGlobals::time = 0;
			gameGlobals::turn = !gameGlobals::turn;
			return;
		}
	}

	glutTimerFunc(14, WeaponDriver, 0);
}

void mouseMove(int x, int y)
{

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
			
			glutTimerFunc(17, WeaponDriver, 0);

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

