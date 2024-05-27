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
	void reset_big_ship() {
		pos[0].set(1, 7);
		pos[1].set(2, 7);
		pos[2].set(1, 8);
		pos[3].set(2, 8);
		is_finish = false;
	}
	void reset_small_ship() {
		pos[0].set(1, 5);
		pos[1].set(2, 5);
		is_finish = false;
	}
	void set_shape(char shape)
	{
		ship_shape = shape;
	}

};