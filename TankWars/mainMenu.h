#pragma once
#include <string>
namespace MainMenu
{
	void display();
	void TANKWARS();
	void Stars();
	void RenderString(float x, float y, std::string str);
	void RenderString1(float x, float y, std::string str, float width = 20);
	void drawRect(float sx, float sy, float ex, float ey, bool solid = false);
	void mouseMove(int x, int y);
	void animate(int t);
	void mouseClick(int button, int s, int x, int y);
	bool isDone();
	void scrollCredits(int y);
}
