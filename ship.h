#pragma once

#include "Point.h"


class Ship {
	constexpr static size_t MAX_SHIP_SIZE = 4;
	size_t size = 0;
	char ship_shape;
	bool is_finish = false;
public:
	
	Point pos[MAX_SHIP_SIZE];
	void init() {

	}
	void addPoint(int x, int y) {
		pos[size++].set(x, y);
	}
	size_t getSize() const {
		return size;
	}
	Point getPos(size_t i) const {
		return pos[i];
	}
	bool get_is_finish() {
		return is_finish;
	}
	void set_is_finish(bool new_finish) {
		is_finish = new_finish;
	}
	void print_ship(bool is_color)
	{
		if (ship_shape == '@')
		{
			for (int i = 0; i < 2; i++)
			{
				gotoxy(pos[i].getX(), pos[i].getY());
				GameConfig::print_char(ship_shape, is_color);
				
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				gotoxy(pos[i].getX(), pos[i].getY());
				GameConfig::print_char(ship_shape, is_color);
			}
		}

	}
	void set_locations_big_ship(int num1,int num2,int num3,int num4,int num5,int num6, int num7, int num8) {
		pos[0].set(num1, num2);
		pos[1].set(num3, num4);
		pos[2].set(num5, num6);
		pos[3].set(num7, num8);
		is_finish = false;
	}
	void set_locations_small_ship(int num1, int num2, int num3, int num4) {
		pos[0].set(num1, num2);
		pos[1].set(num3, num4);
		is_finish = false;
	}
	void reset_big_ship(Ship org) {
		for (int i = 0; i < 4; i++)
			pos[i].set(org.getPos(i).getX(), org.getPos(i).getY());
		is_finish = false;
	}
	
	void reset_small_ship(Ship org) {
		for(int i=0;i<2;i++)
		pos[i].set(org.getPos(i).getX(), org.getPos(i).getY());
		is_finish = false;
	}
	void set_shape(char shape)
	{
		ship_shape = shape;
	}
	

};