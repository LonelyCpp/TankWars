#pragma once

#include <iostream>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

namespace IntroCut
{
	class Tank
	{

	public:
		float x, y;

		Tank(int xpos, int ypos);

		void tank_base();

		void tank_turret(char dir = 'l');



		void draw(char dir);

		void moveTank(float displacement);

	};
	
	void track();

	class Shoot
	{
	public:

		float x, y;

		void setpos(float sx, float sy);

		void bullet(float radius, int x1, int y1);

		void move_and_draw(char dir = 'l');

		void shoot_multiple();
	};
	
	void  splash();

	void heading();

	void animate(int t);

	void display();

	bool isDone();
}