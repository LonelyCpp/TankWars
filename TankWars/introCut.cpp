

#include "introCut.h"
#include <Windows.h>
#include <mmsystem.h>

IntroCut::Tank leftTank(0, 0), rightTank(500, 0);
IntroCut::Shoot leftBomb, rightBomb, last;

int height = -200, width = -430;
int xl = 0, yl = 0, xr = 500, yr = 0;
int j = 0, k = 0;
bool once = true;

int GameState = 0; // 0 -> move tank. 1 -> shoot
int stop = 0;
int done = 0;


IntroCut::Tank::Tank(int xpos, int ypos)

{
	x = xpos;
	y = ypos;
}

void IntroCut::Tank::tank_base()
{
	glColor3ub(51, 78, 4);
	glBegin(GL_POLYGON);
	glVertex2f(x, y + 232);
	glVertex2f(x, y + 237);
	glVertex2f(x + 5, y + 242);
	glColor3ub(106, 127, 60);
	glVertex2f(x + 25, y + 242);
	glVertex2f(x + 30, y + 237);
	glVertex2f(x + 30, y + 232);
	glVertex2f(x + 25, y + 227);
	glVertex2f(x + 5, y + 227);
	glVertex2f(x, y + 237);
	glEnd();

	//layer 3
	glColor3ub(2, 81, 38);
	glBegin(GL_POLYGON);
	glVertex2f(x, y + 228);
	glVertex2f(x + 30, y + 228);
	glVertex2f(x + 30, y + 224);
	glVertex2f(x, y + 224);
	glEnd();


	//layer 2
	glColor3ub(77, 93, 48);
	glBegin(GL_POLYGON);
	glVertex2f(x + 8, y + 229);
	glVertex2f(x + 23, y + 229);
	glVertex2f(x + 23, y + 226);
	glVertex2f(x + 8, y + 226);
	glEnd();


	//layer 4

	glColor3ub(40, 62, 23);
	glBegin(GL_POLYGON);
	glVertex2f(x + 7.5, y + 224);
	glVertex2f(x + 24, y + 224);
	glVertex2f(x + 24, y + 217);
	glVertex2f(x + 7.5, y + 217);
	glEnd();
	//layer 5, top 2nd


	glColor3ub(44, 68, 13);
	glBegin(GL_POLYGON);
	glVertex2f(x + 11, y + 217);
	glVertex2f(x + 20, y + 217);
	glVertex2f(x + 20, y + 213);
	glVertex2f(x + 11, y + 213);
	glEnd();


	// layer 6, top 1st


	glColor3ub(41, 69, 20);
	glBegin(GL_POLYGON);
	glVertex2f(x + 11, y + 213);
	glVertex2f(x + 20, y + 213);
	glVertex2f(x + 18.3, y + 211.5);
	glVertex2f(x + 13.3, y + 211.5);
	glEnd();


	//Point tires 
	glColor3f(0, 0, 0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(x + 7, y + 234);
	glVertex2f(x + 15, y + 234);
	glVertex2f(x + 23, y + 234);
	glEnd();

	//glFlush();
}

void IntroCut::Tank::tank_turret(char dir)

{
	glBegin(GL_POLYGON);
	if (dir == 'l')
	{
		glVertex2f(x + 20, y + 215.5);
		glVertex2f(x + 26, y + 216.5);
		glVertex2f(x + 26, y + 213);
		glVertex2f(x + 20, y + 213);

		glEnd();


		glBegin(GL_POLYGON);			//gun
		glVertex2f(x + 26, y + 213);
		glVertex2f(x + 35, y + 213);
		glVertex2f(x + 35, y + 214.8);
		glVertex2f(x + 26, y + 214.8);


	}
	else
	{
		glVertex2f(x + 11, y + 215.5);
		glVertex2f(x + 5, y + 216.5);
		glVertex2f(x + 5, y + 213);
		glVertex2f(x + 11, y + 213);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(x + 5, y + 213);
		glVertex2f(x - 4, y + 213);
		glVertex2f(x - 4, y + 214.8);
		glVertex2f(x + 5, y + 214.8);

	}
	glEnd();

}

void IntroCut::Tank::draw(char dir)
{
	tank_base();
	tank_turret(dir);

}

void IntroCut::Tank::moveTank(float displacement)
{
	x += displacement;
}

void IntroCut::track()
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0, 250);
	glVertex2f(500, 250);
	glEnd();
}

void IntroCut::splash()
{
		glClearColor(1, 0, 1, 1);

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClearColor(0, 0, 1, 1);

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClearColor(1, 0, 0, 1);

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClearColor(0.23, 0.5, 0, 0);

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClearColor(0.23, 0.5, 0.4, 0);

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClearColor(0.56, 0.2, 0.6, 0);

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClearColor(1, 0.5, 0, 0);

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();

	
}

void IntroCut::heading()
{

		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT);
		//glutSwapBuffers();
		glClearColor(0, 0, 0, 1);
		glLineWidth(3);
		glColor3f(1, 1, 0);

		glBegin(GL_LINE_LOOP);		//T
		glVertex2f(width + 160 + 350, height + 150);
		glVertex2f(width + 160 + 350, height + 100);
		glVertex2f(width + 135 + 350, height + 100);
		glVertex2f(width + 135 + 350, height + 75);
		glVertex2f(width + 210 + 350, height + 75);
		glVertex2f(width + 210 + 350, height + 100);
		glVertex2f(width + 185 + 350, height + 100);
		glVertex2f(width + 185 + 350, height + 150);
		glEnd();



		glBegin(GL_LINE_LOOP);		//A
		glVertex2f(width + 205 + 350, height + 150);
		glVertex2f(width + 225 + 350, height + 75);
		glVertex2f(width + 260 + 350, height + 75);
		glVertex2f(width + 280 + 350, height + 150);
		glVertex2f(width + 260 + 350, height + 150);
		glVertex2f(width + 255 + 350, height + 140);
		glVertex2f(width + 230 + 350, height + 140);
		glVertex2f(width + 225 + 350, height + 150);
		glEnd();

		glBegin(GL_LINE_LOOP);		//A
		glVertex2f(width + 230 + 350, height + 123);
		glVertex2f(width + 242 + 350, height + 85);
		glVertex2f(width + 255 + 350, height + 123);
		glEnd();




		glBegin(GL_LINE_LOOP);		//N
		glVertex2f(width + 290 + 350, height + 150);
		glVertex2f(width + 290 + 350, height + 75);
		glVertex2f(width + 310 + 350, height + 75);
		glVertex2f(width + 350 + 350, height + 120);
		glVertex2f(width + 350 + 350, height + 75);
		glVertex2f(width + 370 + 350, height + 75);
		glVertex2f(width + 370 + 350, height + 150);
		glVertex2f(width + 350 + 350, height + 150);
		glVertex2f(width + 310 + 350, height + 100);
		glVertex2f(width + 310 + 350, height + 150);
		glEnd();



		glBegin(GL_LINE_LOOP);		//K
		glVertex2f(width + 380 + 350, height + 150);
		glVertex2f(width + 380 + 350, height + 75);
		glVertex2f(width + 400 + 350, height + 75);
		glVertex2f(width + 400 + 350, height + 110);
		glVertex2f(width + 430 + 350, height + 75);
		glVertex2f(width + 455 + 350, height + 75);
		glVertex2f(width + 417 + 350, height + 117);
		glVertex2f(width + 455 + 350, height + 150);
		glVertex2f(width + 430 + 350, height + 150);
		glVertex2f(width + 400 + 350, height + 125);
		glVertex2f(width + 400 + 350, height + 150);
		glEnd();




		glBegin(GL_LINE_LOOP);		//W
		glVertex2f(width + 150 + 350, height + 235);
		glVertex2f(width + 135 + 350, height + 160);
		glVertex2f(width + 155 + 350, height + 160);
		glVertex2f(width + 165 + 350, height + 190);
		glVertex2f(width + 175 + 350, height + 160);
		glVertex2f(width + 195 + 350, height + 160);
		glVertex2f(width + 205 + 350, height + 190);
		glVertex2f(width + 215 + 350, height + 160);
		glVertex2f(width + 235 + 350, height + 160);
		glVertex2f(width + 220 + 350, height + 235);
		glVertex2f(width + 200 + 350, height + 235);
		glVertex2f(width + 185 + 350, height + 195);
		glVertex2f(width + 170 + 350, height + 235);
		glEnd();



		glBegin(GL_LINE_LOOP);		//A
		glVertex2f(width + 230 + 350, height + 235);
		glVertex2f(width + 250 + 350, height + 160);
		glVertex2f(width + 285 + 350, height + 160);
		glVertex2f(width + 305 + 350, height + 235);
		glVertex2f(width + 285 + 350, height + 235);
		glVertex2f(width + 280 + 350, height + 225);
		glVertex2f(width + 255 + 350, height + 225);
		glVertex2f(width + 255 + 350, height + 235);
		glEnd();

		glBegin(GL_LINE_LOOP);		//A
		glVertex2f(width + 255 + 350, height + 208);
		glVertex2f(width + 267 + 350, height + 170);
		glVertex2f(width + 277 + 350, height + 208);
		glEnd();




		glBegin(GL_LINE_LOOP);		//R,S
		glVertex2f(width + 315 + 350, height + 235);
		glVertex2f(width + 315 + 350, height + 160);
		glVertex2f(width + 370 + 350, height + 160);
		glVertex2f(width + 370 + 350, height + 200);
		glVertex2f(width + 360 + 350, height + 200);
		glVertex2f(width + 363 + 350, height + 215);

		glVertex2f(width + 417 + 350, height + 215);
		glVertex2f(width + 380 + 350, height + 160);
		glVertex2f(width + 455 + 350, height + 160);
		glVertex2f(width + 455 + 350, height + 180);
		glVertex2f(width + 417 + 350, height + 180);
		glVertex2f(width + 455 + 350, height + 235);

		glVertex2f(width + 350 + 350, height + 235);
		glVertex2f(width + 335 + 350, height + 200);
		glVertex2f(width + 335 + 350, height + 235);
		glEnd();


		glBegin(GL_LINE_LOOP);		//R
		glVertex2f(width + 335 + 350, height + 190);
		glVertex2f(width + 355 + 350, height + 190);
		glVertex2f(width + 355 + 350, height + 175);
		glVertex2f(width + 335 + 350, height + 175);
		glEnd();


		height += 5;
}

void IntroCut::animate(int t)
{
		if (GameState == 0)	// moving tank
		{
			glClear(GL_COLOR_BUFFER_BIT);

			leftTank.moveTank(1.5);
			rightTank.moveTank(-1.5);

			leftTank.draw('l');
			rightTank.draw('r');

			track();


			//stop code
			if (leftTank.x > 130)
			{
				GameState++;		//stop moving and start shooting

				leftBomb.setpos(leftTank.x, 214);
				rightBomb.setpos(rightTank.x, 214);
			}

			glutSwapBuffers();
		}

		else if (GameState == 1)		//shoot animation
		{
			glClear(GL_COLOR_BUFFER_BIT);

			leftTank.draw('l');
			rightTank.draw('r');

			leftBomb.move_and_draw('l');
			rightBomb.move_and_draw('r');

			if (leftBomb.x >= rightTank.x)
			{
				rightTank.x += 10;

			}

			if (leftBomb.x >= rightBomb.x && rightBomb.x >= 110)
			{
				splash();

			}

			if (stop == 0)
			{
				if (rightBomb.x <= 0)
				{
					last.setpos(leftTank.x + 40, 214);
					leftTank.x += 2;

					if (leftTank.x >= 320)
					{
						stop = 1;
					}

				}
			}

			if (stop == 1)
			{
				last.shoot_multiple();

				if (last.x >= 500)
					leftTank.x += 15;

				if (done == 0)
				{
					if (leftTank.x > 500)
						heading();

					if (height >= 50)
					{
						done = 1;
						glutPostRedisplay();
						return;
					}
						
				}
			}

			glutSwapBuffers();
		}
		glutTimerFunc(8, animate, 0);
	
}

void IntroCut::display()
{

	PlaySound(TEXT("starwars.wav"), NULL, SND_ASYNC);
	glutTimerFunc(20, animate, 0);
}

bool IntroCut::isDone()
{
	if (done == 1)
		return true;
	return false;
}

void IntroCut::Shoot::setpos(float sx, float sy)
{
	x = sx;
	y = sy;
}

void IntroCut::Shoot::bullet(float radius, int x1, int y1)
{
	for (int i = 0; i < 360; i++)
	{
		x1 = radius*cos(i);
		y1 = radius*sin(i);
	}
}

void IntroCut::Shoot::move_and_draw(char dir)
{
	glPointSize(5);

	glBegin(GL_POINTS);

	if (dir == 'l')
		glVertex2f(x += 1.7, y);
	else
		glVertex2f(x -= 1.7, y);

	glEnd();

}

void IntroCut::Shoot::shoot_multiple()
{
	glPointSize(5);

	glBegin(GL_POINTS);
	glVertex2f(x + 1.7, y);
	glVertex2f(x + 10, y);
	glVertex2f(x + 20, y);
	glVertex2f(x + 30, y);
	glVertex2f(x + 40, y);
	glVertex2f(x + 50, y);

	for (double i = 0; i < 10000000; i++);
	x += 10;

	glEnd();
}