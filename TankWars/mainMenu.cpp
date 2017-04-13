#include <GL/glut.h>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <time.h>
#include<Windows.h>
#include<mmsystem.h>
#include "Tank.h"
#include "color.h"
#include "mainMenu.h"

int scrollPos = 500;
int x = 80, y = 0;
int optionClicked = -1;

bool optionToFill[3] = { false, false, false };

void MainMenu::Stars()
{
	srand(time(NULL));
	glColor3f(1, 1, 1);
	for (int i = 0; i < 600; i++)
	{
		glPointSize(1 + rand() % 4);
		glBegin(GL_POINTS);
		glVertex2f(rand() % 1920, rand() % 1000);
		glEnd();
	}
}

void MainMenu::TANKWARS()
{
	glLineWidth(3);
	glColor3f(1, 1, 0);
	int x = 0;

	glBegin(GL_LINE_LOOP);		//T
	glVertex2f(510 + x, 150 + y);
	glVertex2f(510 + x, 100 + y);
	glVertex2f(485 + x, 100 + y);
	glVertex2f(485 + x, 75 + y);
	glVertex2f(560 + x, 75 + y);
	glVertex2f(560 + x, 100 + y);
	glVertex2f(535 + x, 100 + y);
	glVertex2f(535 + x, 150 + y);
	glEnd();



	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(555 + x, 150 + y);
	glVertex2f(575 + x, 75 + y);
	glVertex2f(610 + x, 75 + y);
	glVertex2f(630 + x, 150 + y);
	glVertex2f(610 + x, 150 + y);
	glVertex2f(605 + x, 140 + y);
	glVertex2f(580 + x, 140 + y);
	glVertex2f(575 + x, 150 + y);
	glEnd();

	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(580 + x, 123 + y);
	glVertex2f(592 + x, 85 + y);
	glVertex2f(605 + x, 123 + y);
	glEnd();




	glBegin(GL_LINE_LOOP);		//N
	glVertex2f(640 + x, 150 + y);
	glVertex2f(640 + x, 75 + y);
	glVertex2f(660 + x, 75 + y);
	glVertex2f(700 + x, 120 + y);
	glVertex2f(700 + x, 75 + y);
	glVertex2f(720 + x, 75 + y);
	glVertex2f(720 + x, 150 + y);
	glVertex2f(700 + x, 150 + y);
	glVertex2f(660 + x, 100 + y);
	glVertex2f(660 + x, 150 + y);
	glEnd();



	glBegin(GL_LINE_LOOP);		//K
	glVertex2f(730 + x, 150 + y);
	glVertex2f(730 + x, 75 + y);
	glVertex2f(750 + x, 75 + y);
	glVertex2f(750 + x, 110 + y);
	glVertex2f(780 + x, 75 + y);
	glVertex2f(805 + x, 75 + y);
	glVertex2f(767 + x, 117 + y);
	glVertex2f(805 + x, 150 + y);
	glVertex2f(780 + x, 150 + y);
	glVertex2f(750 + x, 125 + y);
	glVertex2f(750 + x, 150 + y);
	glEnd();




	glBegin(GL_LINE_LOOP);		//W
	glVertex2f(500 + x, 235 + y);
	glVertex2f(485 + x, 160 + y);
	glVertex2f(505 + x, 160 + y);
	glVertex2f(515 + x, 190 + y);
	glVertex2f(525 + x, 160 + y);
	glVertex2f(545 + x, 160 + y);
	glVertex2f(555 + x, 190 + y);
	glVertex2f(565 + x, 160 + y);
	glVertex2f(585 + x, 160 + y);
	glVertex2f(570 + x, 235 + y);
	glVertex2f(550 + x, 235 + y);
	glVertex2f(535 + x, 195 + y);
	glVertex2f(520 + x, 235 + y);
	glEnd();



	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(580 + x, 235 + y);
	glVertex2f(600 + x, 160 + y);
	glVertex2f(635 + x, 160 + y);
	glVertex2f(655 + x, 235 + y);
	glVertex2f(635 + x, 235 + y);
	glVertex2f(630 + x, 225 + y);
	glVertex2f(605 + x, 225 + y);
	glVertex2f(600 + x, 235 + y);
	glEnd();

	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(605 + x, 208 + y);
	glVertex2f(617 + x, 170 + y);
	glVertex2f(627 + x, 208 + y);
	glEnd();




	glBegin(GL_LINE_LOOP);		//R,S
	glVertex2f(665 + x, 235 + y);
	glVertex2f(665 + x, 160 + y);
	glVertex2f(720 + x, 160 + y);
	glVertex2f(720 + x, 200 + y);
	glVertex2f(710 + x, 200 + y);
	glVertex2f(713 + x, 215 + y);

	glVertex2f(767 + x, 215 + y);
	glVertex2f(730 + x, 160 + y);
	glVertex2f(805 + x, 160 + y);
	glVertex2f(805 + x, 180 + y);
	glVertex2f(767 + x, 180 + y);
	glVertex2f(805 + x, 235 + y);

	glVertex2f(700 + x, 235 + y);
	glVertex2f(685 + x, 200 + y);
	glVertex2f(685 + x, 235 + y);
	glEnd();


	glBegin(GL_LINE_LOOP);		//R
	glVertex2f(685 + x, 190 + y);
	glVertex2f(705 + x, 190 + y);
	glVertex2f(705 + x, 175 + y);
	glVertex2f(685 + x, 175 + y);
	glEnd();

	RenderString1(400, 280 + y, "The Infinite Annihilation");

	glColor3f(1, 1, 1);
	drawRect(500, 325, 805, 400, optionToFill[0]);	//option1
	RenderString1(550, 370, "PLAY",65);

	glColor3f(1, 1, 1);
	drawRect(500, 450, 805, 525, optionToFill[1]);	//option2
	RenderString1(550, 495, "INFO", 65);

	glColor3f(1, 1, 1);
	drawRect(500, 575, 805, 650, optionToFill[2]);	//option3
	RenderString1(550, 620, "EXIT", 65);

}

void MainMenu::animate(int t)
{
	display();
	if (optionClicked == 1)
		return;
	glutTimerFunc(1000, animate, 0);
}

void MainMenu::display()
{
	glClearColor(gameGlobals::backColor.r / 255.0, gameGlobals::backColor.g / 255.0, gameGlobals::backColor.b / 255.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	Stars();

	TANKWARS();

	Tank TankL(20, 500);
	Tank TankR(1200, 500);

	TankL.updateAngle(300, 300);
	TankR.updateAngle(1000, 300);

	TankL.draw();
	TankR.draw();

	glutSwapBuffers();
}

void MainMenu::RenderString(float x, float y, std::string str)
{
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;

	glColor3f(1, 1, 0);

	int WIDTH = 15;


	for (int i = 0; i < str.length(); i++)
	{
		glRasterPos2f(x + i * WIDTH, y);
		glutBitmapCharacter(font, str[i]);
	}

}

void MainMenu::RenderString1(float x, float y, std::string str, float width)
{
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;

	glColor3f(1, 1, 0);

	float WIDTH = width;


	for (float i = 0; i < str.length(); i++)
	{
		glRasterPos2f(x + i * WIDTH, y);
		glutBitmapCharacter(font, str[(int)i]);
	}

}

void MainMenu::drawRect(float sx, float sy, float ex, float ey, bool solid)
{
	if (solid == false)
	{
		glBegin(GL_LINE_LOOP);
	}
	else
	{
		glBegin(GL_POLYGON);
		glColor3ub(15, 15, 15);
	}

	glVertex2f(sx, sy);
	glVertex2f(ex, sy);
	glVertex2f(ex, ey);
	glVertex2f(sx, ey);

	glEnd();

}

void MainMenu::mouseMove(int x, int y)
{
	if (x > 500 && x < 805)
	{
		if (y > 325 && y < 400)
		{
			if (optionToFill[0] != true)
			{
				optionToFill[0] = true;
				glutPostRedisplay();
			}
		}
		else
		{
			if (optionToFill[0] != false)
			{
				optionToFill[0] = false;
				glutPostRedisplay();
			}

		}

		if (y > 450 && y < 525)
		{
			if (optionToFill[1] != true)
			{
				optionToFill[1] = true;
				glutPostRedisplay();
			}
		}
		else
		{
			if (optionToFill[1] != false)
			{

				optionToFill[1] = false;
				glutPostRedisplay();
			}
		}
		if (y > 575 && y < 650)
		{
			if (optionToFill[2] != true)
			{

				optionToFill[2] = true;
				glutPostRedisplay();
			}
		}
		else
		{
			if (optionToFill[2] != false)
			{
				optionToFill[2] = false;
				glutPostRedisplay();
			}
		}
	}
}

void MainMenu::mouseClick(int button, int s, int x, int y)
{
	if (s == GLUT_DOWN)
		if (x > 500 && x < 805)
		{
			if (y > 325 && y < 400)
			{
				optionClicked = 1;
				glutPostRedisplay();
			}

			else if (y > 450 && y < 525)
			{
				PlaySound(TEXT("credit.wav"), NULL, SND_ASYNC);

				for (int s = 700; s > -1500; s--)
				{
					glClear(GL_COLOR_BUFFER_BIT);
					MainMenu::Stars();
					scrollCredits(s);
					for (double i = 0; i < 1000000; i++);

				}
				PlaySound(TEXT("starwars.wav"), NULL, SND_ASYNC);

				MainMenu::display();
			}
			else if (y > 575 && y < 650)
				exit(0);
		}
}

bool MainMenu::isDone()
{
	if (optionClicked == 1)
		return true;

	return false;
}

void MainMenu::scrollCredits(int y)
{
	glLineWidth(3);
	glColor3f(1, 1, 0);

	glBegin(GL_LINE_LOOP);		//T
	glVertex2f(510 + x, 150 + y);
	glVertex2f(510 + x, 100 + y);
	glVertex2f(485 + x, 100 + y);
	glVertex2f(485 + x, 75 + y);
	glVertex2f(560 + x, 75 + y);
	glVertex2f(560 + x, 100 + y);
	glVertex2f(535 + x, 100 + y);
	glVertex2f(535 + x, 150 + y);
	glEnd();



	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(555 + x, 150 + y);
	glVertex2f(575 + x, 75 + y);
	glVertex2f(610 + x, 75 + y);
	glVertex2f(630 + x, 150 + y);
	glVertex2f(610 + x, 150 + y);
	glVertex2f(605 + x, 140 + y);
	glVertex2f(580 + x, 140 + y);
	glVertex2f(575 + x, 150 + y);
	glEnd();

	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(580 + x, 123 + y);
	glVertex2f(592 + x, 85 + y);
	glVertex2f(605 + x, 123 + y);
	glEnd();




	glBegin(GL_LINE_LOOP);		//N
	glVertex2f(640 + x, 150 + y);
	glVertex2f(640 + x, 75 + y);
	glVertex2f(660 + x, 75 + y);
	glVertex2f(700 + x, 120 + y);
	glVertex2f(700 + x, 75 + y);
	glVertex2f(720 + x, 75 + y);
	glVertex2f(720 + x, 150 + y);
	glVertex2f(700 + x, 150 + y);
	glVertex2f(660 + x, 100 + y);
	glVertex2f(660 + x, 150 + y);
	glEnd();



	glBegin(GL_LINE_LOOP);		//K
	glVertex2f(730 + x, 150 + y);
	glVertex2f(730 + x, 75 + y);
	glVertex2f(750 + x, 75 + y);
	glVertex2f(750 + x, 110 + y);
	glVertex2f(780 + x, 75 + y);
	glVertex2f(805 + x, 75 + y);
	glVertex2f(767 + x, 117 + y);
	glVertex2f(805 + x, 150 + y);
	glVertex2f(780 + x, 150 + y);
	glVertex2f(750 + x, 125 + y);
	glVertex2f(750 + x, 150 + y);
	glEnd();




	glBegin(GL_LINE_LOOP);		//W
	glVertex2f(500 + x, 235 + y);
	glVertex2f(485 + x, 160 + y);
	glVertex2f(505 + x, 160 + y);
	glVertex2f(515 + x, 190 + y);
	glVertex2f(525 + x, 160 + y);
	glVertex2f(545 + x, 160 + y);
	glVertex2f(555 + x, 190 + y);
	glVertex2f(565 + x, 160 + y);
	glVertex2f(585 + x, 160 + y);
	glVertex2f(570 + x, 235 + y);
	glVertex2f(550 + x, 235 + y);
	glVertex2f(535 + x, 195 + y);
	glVertex2f(520 + x, 235 + y);
	glEnd();



	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(580 + x, 235 + y);
	glVertex2f(600 + x, 160 + y);
	glVertex2f(635 + x, 160 + y);
	glVertex2f(655 + x, 235 + y);
	glVertex2f(635 + x, 235 + y);
	glVertex2f(630 + x, 225 + y);
	glVertex2f(605 + x, 225 + y);
	glVertex2f(600 + x, 235 + y);
	glEnd();

	glBegin(GL_LINE_LOOP);		//A
	glVertex2f(605 + x, 208 + y);
	glVertex2f(617 + x, 170 + y);
	glVertex2f(627 + x, 208 + y);
	glEnd();




	glBegin(GL_LINE_LOOP);		//R,S
	glVertex2f(665 + x, 235 + y);
	glVertex2f(665 + x, 160 + y);
	glVertex2f(720 + x, 160 + y);
	glVertex2f(720 + x, 200 + y);
	glVertex2f(710 + x, 200 + y);
	glVertex2f(713 + x, 215 + y);

	glVertex2f(767 + x, 215 + y);
	glVertex2f(730 + x, 160 + y);
	glVertex2f(805 + x, 160 + y);
	glVertex2f(805 + x, 180 + y);
	glVertex2f(767 + x, 180 + y);
	glVertex2f(805 + x, 235 + y);

	glVertex2f(700 + x, 235 + y);
	glVertex2f(685 + x, 200 + y);
	glVertex2f(685 + x, 235 + y);
	glEnd();


	glBegin(GL_LINE_LOOP);		//R
	glVertex2f(685 + x, 190 + y);
	glVertex2f(705 + x, 190 + y);
	glVertex2f(705 + x, 175 + y);
	glVertex2f(685 + x, 175 + y);
	glEnd();
	RenderString(550, 280 + y, "The Infinite Annihilation");


	int sx=200,sx1=120;

	RenderString(25 + sx, 400 + y, "Tank wars is a war game where two players play against each other.");

	RenderString(190 + sx, 450 + y, "Each player gets a tank loaded with weapons.");

	RenderString(25 + sx, 500 + y, "The gameplay requires each player to target and hit the opponents");

	RenderString(350 + sx, 550 + y, "tank, placed around the arena.");

	RenderString(50 + sx, 600 + y, "The turret of the tank is to be positioned in a way that it can");

	RenderString(190 + sx, 650 + y, "target the opponent tank and fire through the barrel.");

	RenderString(65 + sx, 700 + y, "The aim is to score maximum points by attacking the enemy tank.");

	RenderString(170 + sx, 750 + y, "The game concludes when all the weapons get exhausted.");

	RenderString(25 + sx, 800 + y, "Based on points earned by the end of the game, a winner is decided.");

	RenderString(550 + sx1, 900 + y, "CREATED BY :");

	RenderString(525 + sx1, 950 + y, "AKSHAY SAXENA");

	RenderString(550 + sx1, 1000 + y, "ALOK M RAO");

	RenderString(500 + sx1, 1050 + y, "ANANTHU P KANIVE");

	RenderString(520 + sx1, 1100 + y, "ARJUN S NAYAK");

	RenderString(530 + sx1, 1200 + y, "SUBMITTED TO :");

	RenderString(505 + sx1, 1250 + y, "MRS. SHILPA M K");

	glutSwapBuffers();
}
