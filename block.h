#pragma once

#include "Point.h"
class Board;

class Block {
	constexpr static size_t MAX_BlOCK_SIZE = 6;
	size_t size = 0;
	Board* board = nullptr; // pointer to the board
public:
	Point pos[MAX_BlOCK_SIZE];
	void setBoard(Board* board) {
		this->board = board;
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
	void set_size(int newsize) {
		size = newsize;
	}
	void print_block(char c,bool is_color) {
				for (int i = 0; i < size; i++)
				{
					gotoxy(pos[i].getX(), pos[i].getY());
					GameConfig::print_char(c, is_color);
				}
			
	}

};