#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#include <Windows.h>
#include <mmsystem.h>
#include <string>

#include "color.h"
#include "Weapon.h"
#include "Tank.h"
#include "Terrain.h"
#include "FillBar.h"
#include "introCut.h"
#include "mainMenu.h"
#include "EndGame.h"

void display();
void changeSize(int w, int h);
void WeaponDriver(int t);
void mouseMove(int x, int y);
void mouseClick(int button, int s, int x, int y);
void powerSelector(int t);
enum { SELECT_ANGLE = 0, SELECT_POWER, SHOOT };
enum { INTRO_CUT = 0, MAIN_MENU, PLAY_GAME, END_GAME};


namespace gameGlobals {
	int gamePart = INTRO_CUT;
	int state = 0;	
	float time = 0;
	bool turn = 0;	
	int selectedPower = 100;
	int winner = -1;
	Color backColor = { 255, 255, 255 };
}


Weapon *basicBomb = NULL;
Tank tank[2] = { Tank(50, 636), Tank(1100, 636) };
Terrain mountain(-300, 700);
FillBar powerBar(500, 10);


int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1000);
	glutCreateWindow("Tank Wars");

	//-- My Init --
	glClearColor(gameGlobals::backColor.r / 255.0, gameGlobals::backColor.g / 255.0, gameGlobals::backColor.b / 255.0, 0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 499.0, 0.0);
	
	tank[0].setColor({ 255, 0, 0 });
	tank[0].setColor({ 0, 0, 255 });
	powerBar.setDim(200, 20);

	//-- 
	
	gameGlobals::state = SELECT_ANGLE;

	glutDisplayFunc(display);
	//glutReshapeFunc(changeSize);
	
	

	glutMainLoop();
	
	return 0;
}

void display()
{
	glClearColor(gameGlobals::backColor.r / 255.0, gameGlobals::backColor.g / 255.0, gameGlobals::backColor.b / 255.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);

	if (gameGlobals::gamePart != END_GAME)
	{
		if (IntroCut::isDone())
			gameGlobals::gamePart = MAIN_MENU;
		if (MainMenu::isDone())
			gameGlobals::gamePart = PLAY_GAME;
	}


	if (gameGlobals::gamePart == INTRO_CUT)
	{		
		gameGlobals::backColor = { 255, 255, 255};
		IntroCut::display();
	}
	else if (gameGlobals::gamePart == MAIN_MENU)
	{
		glutReshapeFunc(changeSize);

		gameGlobals::backColor = { 0, 0, 0 };
		glutPassiveMotionFunc(MainMenu::mouseMove);
		glutMouseFunc(MainMenu::mouseClick);
		MainMenu::display();
	}
	else if(gameGlobals::gamePart == PLAY_GAME)
	{
		glPointSize(1);
		glLineWidth(1);

		gameGlobals::backColor = { 255, 133, 82 };

		glClearColor(gameGlobals::backColor.r / 255.0, gameGlobals::backColor.g / 255.0, gameGlobals::backColor.b / 255.0, 0);
		glutPassiveMotionFunc(mouseMove);
		glutMouseFunc(mouseClick);

		mountain.draw();

		tank[0].draw(true);
		tank[1].draw(true);

		glutSwapBuffers();
	}
	else if (gameGlobals::gamePart == END_GAME)
	{
		glClearColor(gameGlobals::backColor.r / 255.0, gameGlobals::backColor.g / 255.0, gameGlobals::backColor.b / 255.0, 0);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1, 1, -1, 1);

		endgame::display();

		MainMenu::RenderString1(-0.25, -0.7, "GAME OVER", 0.05);
		if(gameGlobals::winner == 1)
			MainMenu::RenderString1(-0.35, -0.9, "PLAYER 1 WINS!", 0.05);
		else
			MainMenu::RenderString1(-0.35, -0.9, "PLAYER 2 WINS!", 0.05);


		glutPassiveMotionFunc(NULL);
		glutMouseFunc(NULL);
		glutSwapBuffers();
	}
	
	
	
}

void WeaponDriver(int t)
{
	if (gameGlobals::state == SHOOT)
	{
		std::pair<int, int> bombPos = basicBomb->draw(gameGlobals::time += 0.1);

		//-- check if the bomb has hit anything
		
		bool stopBomb = mountain.didHit(bombPos.first, bombPos.second);

		stopBomb = stopBomb || tank[0].didHit(bombPos.first, bombPos.second) || tank[1].didHit(bombPos.first, bombPos.second);

		//--

		if ( !stopBomb )
		{
			mountain.draw();

			tank[0].draw(true);
			tank[1].draw(true);
			
			glutSwapBuffers();
			basicBomb->erase(gameGlobals::time - 0.1);
		}
		else
		{
			if (tank[0].isDead())
				gameGlobals::winner = 2;
			else if (tank[1].isDead())
				gameGlobals::winner = 1;
			if(gameGlobals::winner != -1)
			{
				std::cout << "died";
				gameGlobals::gamePart = END_GAME;
				glutPostRedisplay();
			}
				

			PlaySound(TEXT("explode.wav"), NULL, SND_ASYNC);
			basicBomb->explodeAnime(gameGlobals::time);
			glutSwapBuffers();

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

void powerSelector(int t)
{
	if (gameGlobals::state != SELECT_POWER)
		return;
	mountain.draw();

	tank[0].draw(true);
	tank[1].draw(true);

	gameGlobals::selectedPower = t % 200;
	powerBar.setFill(gameGlobals::selectedPower / 2);
	powerBar.draw();

	glutSwapBuffers();
	glutTimerFunc(17, powerSelector, t + 4);
}

void mouseMove(int x, int y)
{
	if (gameGlobals::state ==  SELECT_ANGLE)
	{
		tank[gameGlobals::turn].erase();
		tank[gameGlobals::turn].updateAngle(x, y);
		
		mountain.draw();

		tank[0].draw(true);
		tank[1].draw(true);

		glutSwapBuffers();	
	}
}

void mouseClick(int button, int s, int x, int y)
{
	if (s == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (gameGlobals::state == SHOOT)
			return;

		gameGlobals::state = (gameGlobals::state + 1) % 3;

		if (gameGlobals::state == SELECT_POWER)
			glutTimerFunc(17, powerSelector, 0);
		
		if (gameGlobals::state == SHOOT)
		{
			basicBomb = tank[gameGlobals::turn].createWeapon(gameGlobals::selectedPower);
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