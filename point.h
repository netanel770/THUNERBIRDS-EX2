#pragma once
#define MIN_X 0
#define MIN_Y 0
#include <iostream>
#include <Windows.h>
#include "general.h"
#include "GameConfig.h"
#include "point.h"




using namespace std;
class Point {
	int x = 1, y = 1;
public:
	
	void set(int x1, int y1) {
		x = x1;
		y = y1;
	}
	void setx(int x1) {
		x = x1;
	}
	void sety(int y1) {
		y = y1;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void draw(char ch, int backcolor)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
		gotoxy(x + MIN_X - 1, y + MIN_Y - 1);
		cout << ch;
	}
	void move (GameConfig::eKeys key)
	{
		switch (key)
		{
		case GameConfig::eKeys::LEFT:
			 x--;
			break;
		case GameConfig::eKeys::RIGHT:
			x++;
			break;
		case GameConfig::eKeys::UP:
			y--;
			break;
		case GameConfig::eKeys::DOWN:
			y++;
			break;
		}
		if (x > GameConfig::GAME_WIDTH)
			x = 1;
		else if (x == 0)
			x = GameConfig::GAME_WIDTH;

		if (y > GameConfig::GAME_HEIGHT)
			y = 1;
		else if (y == 0)
			y = GameConfig::GAME_HEIGHT;
	}
	void print_point() {
		cout << "x is " << x << "y is : " << y;
	}
	
};