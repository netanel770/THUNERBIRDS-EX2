#pragma once

#include "point.h"
#include "ship.h"
#include "block.h"
#include <iostream>
#include <cstring>
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include <iostream>
#include <cstring>
#include "io_utils.h"
class Ship;
class Board {
	 int num_of_blocks;
public:
	constexpr static size_t WIDTH = 80;
	constexpr static size_t HEIGHT = 25;
	constexpr static size_t NUM_SHIPS = 2;
	constexpr static size_t NUM_BLOCKS = 6;
	// the original board that will be copied to the actual board
	/*char original_board[HEIGHT][WIDTH + 1] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W                                                                              W", // 1
			"W        &                                                                     W", // 2
			"W                                                                              W", // 3
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 4
			"W@@                                                                            W", // 5
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W", // 6
			"W##  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W", // 7
			"W##  W     WW   WW                                                          W  W", // 8
			"W    W    WWWWWWWWW         W    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW      W  W", // 9
			"W    W      WWWWW           W    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW      W  W", // 10
			"W    W        W                                   WW                        W  W", // 11
			"W    W                                                                      W  W", // 12
			"W    W    W              WWWWWWWWWW            W  22                 W      W  W", // 13
			"W    W    WWWWWWWWWWWWWWW         WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW      W  W", // 14
			"W    W    W         WW                                                      W  W", // 15
			"W    W    W         11                                                      W  W", // 16
			"W    W    W      W  11         WWWWWWWWWWWWWWWWWWWWWWWWW                 WWWW  W", // 17
			"W    W    W      WWWWWWWWWWWWWWW          WWWWWWW      WWWWWWWWWWWWWWWWWW      W", // 18
			"W    W    W                  00                                                W", // 19
			"W    W X  W                  00       W      44                             W  W", // 20
			"W    WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW  W", // 21
			"W                                                                              W", // 22
			"W                                                                         33   W", // 23
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};*/
	// the actual board that will be modified
	char original_board[HEIGHT][WIDTH + 1];
	char board[HEIGHT][WIDTH + 1];
	Ship ships[NUM_SHIPS];
	Ship org_small;
	Ship org_big;
	Block* blocks;
	Block* org_blocks;
	Point legend_pos;
	Point exit_pos;

	void init() {
		std::memcpy(board, original_board, sizeof(original_board));
		blocks = new Block[num_of_blocks];
		org_blocks = new Block[num_of_blocks];
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (board[i][j] == '&') {
					legend_pos.set(j, i);
				}
				else if (board[i][j] == '@') {
					ships[0].addPoint(j, i);
				}
				else if (board[i][j] == '#') {
					ships[1].addPoint(j, i);
				}
				else if (board[i][j] >= '0' && board[i][j] <= '9') {
					size_t block_index = board[i][j] - '0';
					blocks[block_index].addPoint(j, i);
				}
				else if (board[i][j] == 'X') {
					exit_pos.set(j, i);
				}
			}
		}
		ships[0].set_shape('@');
		ships[1].set_shape('#');
		ships[0].reset_small_ship(org_small);
		ships[1].reset_big_ship(org_big);
		for (int i = 0; i < num_of_blocks; i++) {
			if (i > 1)
				blocks[i].set_size(2);
			else
				blocks[i].set_size(4);
		}
	}
	~Board()
	{
		delete org_blocks;
		delete blocks;
	}
	void reset_board() {
		std::memcpy(board, original_board, sizeof(original_board));
		ships[0].reset_small_ship(org_small);
		ships[1].reset_big_ship(org_big);
		reset_blocks();
	}
	void show(bool is_color) {
		gotoxy(0, 0);
		for (int i = 0; i < HEIGHT; i++) {
			for(int j = 0; j < WIDTH; j++)
				GameConfig::print_char(board[i][j],is_color);
			std::cout << endl;
		}
	}
	int get_num_of_blocks() {
		return num_of_blocks;
	}
	void reset_blocks() {
		for (int i = 0; i < num_of_blocks; i++)
		{
			for (int j = 0; j < blocks[i].getSize(); j++)
			{
				blocks[i].pos[j].set(org_blocks[i].pos[j].getX(), org_blocks[i].pos[j].getY());
			}
		}
		
		return;
	}
	void update_char_in_board(Point point1, char c) {
		board[point1.getY()][point1.getX()] = c;
	}
	bool can_i_move_the_block(char block_shape, char ship_shape)
	{
		bool res = true;
		if (ship_shape == 's')
		{
			if (block_shape < '2')
				res = false;
		}
		return res;
	}
	int is_available(Point point1, Point point2, char current_shape) {
		if ((board[point1.getY()][point1.getX()] == 'W' || board[point2.getY()][point2.getX()] == 'W') || (board[point1.getY()][point1.getX()] == '#'
			|| board[point2.getY()][point2.getX()] == '#') || (board[point1.getY()][point1.getX()] == '@' || board[point2.getY()][point2.getX()] == '@'))
			return 0;
		if ((is_block(board[point1.getY()][point1.getX()]) || (is_block(board[point2.getY()][point2.getX()])))) {
			if (!can_i_move_the_block(board[point1.getY()][point1.getX()], current_shape)&& !can_i_move_the_block(board[point2.getY()][point2.getX()], current_shape)
				||(board[point1.getY()][point1.getX()] == 'W' || board[point2.getY()][point2.getX()] == 'W'))
				return 0;
			return 2;
		}

		return 1;
	}
	bool is_exit_point(Point point1, Point point2,char current_ship) {
		
		if ((board[point1.getY()][point1.getX()] == 'X' || board[point2.getY()][point2.getX()] == 'X')) {
			int index=1;
			if (current_ship == 's')
				index = 0;
			ships[index].set_is_finish(true);
			return true;
		}
		return false;
	}
	void move_down_the_ship(char ship_shape) {
		Point point1, point2;
		if (ship_shape == '@')
		{
			point1 = ships[0].pos[0];
			point1.sety(point1.getY() + 1);
			point2 = ships[0].pos[1];
			point2.sety(point2.getY() + 1);
			for (int i = 0; i < 2; i++)
			{
				ships[0].pos[i].sety(ships[0].pos[i].getY() + 1);
				update_char_in_board(ships[0].pos[i], ship_shape);
			}
		}

		else
		{
			for (int i = 0; i < 4; i++)
			{
				ships[1].pos[i].sety(ships[1].pos[i].getY() + 1);
				update_char_in_board(ships[1].pos[i], ship_shape);
			}
		}

	}
	void move_up_the_ship(char ship_shape) {
		if (ship_shape == '@')
		{
			for (int i = 0; i < 2; i++)
			{
				ships[0].pos[i].sety(ships[0].pos[i].getY() - 1);
				update_char_in_board(ships[0].pos[i], ship_shape);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				ships[1].pos[i].sety(ships[1].pos[i].getY() - 1);
				update_char_in_board(ships[1].pos[i], ship_shape);
			}
		}

	}
	void move_right_the_ship(char ship_shape) {
		if (ship_shape == '@')
		{
			for (int i = 0; i < 2; i++)
			{
				ships[0].pos[i].setx(ships[0].pos[i].getX() + 1);
				update_char_in_board(ships[0].pos[i], ship_shape);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				ships[1].pos[i].setx(ships[1].pos[i].getX() + 1);
				update_char_in_board(ships[1].pos[i], ship_shape);
			}
		}

	}
	void move_left_the_ship(char ship_shape) {
		if (ship_shape == '@')
		{
			for (int i = 0; i < 2; i++)
			{
				ships[0].pos[i].setx(ships[0].pos[i].getX() - 1);
				update_char_in_board(ships[0].pos[i], ship_shape);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				ships[1].pos[i].setx(ships[1].pos[i].getX() - 1);
				update_char_in_board(ships[1].pos[i], ship_shape);
			}
		}

	}
	void delete_ship_from_screen(char ship_shape)
	{
		if (ship_shape == '@')
		{
			for (int i = 0; i < 2; i++)
			{
				gotoxy(ships[0].pos[i].getX(), ships[0].pos[i].getY());
				update_char_in_board(ships[0].pos[i], ' ');
				cout << " ";
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				gotoxy(ships[1].pos[i].getX(), ships[1].pos[i].getY());
				update_char_in_board(ships[1].pos[i], ' ');
				cout << " ";
			}
		}
	}
	void move_down_the_block(char block) {
		Point point1, point2;
		int block_index = block - '0';
		if (block_index>1)
		{
			point1 = blocks[block_index].pos[0];
			point1.sety(point1.getY() + 1);
			point2 = blocks[block_index].pos[1];
			point2.sety(point2.getY() + 1);
			for (int i = 0; i < 2; i++)
			{
				blocks[block_index].pos[i].sety(ships[0].pos[i].getY() + 1);
				update_char_in_board(blocks[block_index].pos[i],block);
			}
		}

		else
		{
			for (int i = 0; i < 4; i++)
			{
				blocks[block_index].pos[i].sety(blocks[block_index].pos[i].getY() + 1);
				update_char_in_board(blocks[block_index].pos[i], block);
			}
		}

	}
	void move_up_the_block(char block) {
		int block_index = block - '0';
		if (block_index>1)
		{
			for (int i = 0; i < 2; i++)
			{
				blocks[block_index].pos[i].sety(blocks[block_index].pos[i].getY() - 1);
				update_char_in_board(blocks[block_index].pos[i],block);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				blocks[block_index].pos[i].sety(blocks[block_index].pos[i].getY() - 1);
				update_char_in_board(blocks[block_index].pos[i],block);
			}
		}

	}
	void move_right_the_block(char block) {
		int block_index = block - '0';
		if (block_index > 1)
		{
			for (int i = 0; i < 2; i++)
			{
				blocks[block_index].pos[i].setx(blocks[block_index].pos[i].getX() + 1);
				update_char_in_board(blocks[block_index].pos[i], block);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				blocks[block_index].pos[i].setx(blocks[block_index].pos[i].getX() + 1);
				update_char_in_board(blocks[block_index].pos[i], block);
			}
		}

	}
	void move_left_the_block(char block) {
		int block_index = block - '0';
		if (block_index > 1)
		{
			for (int i = 0; i < 2; i++)
			{
				blocks[block_index].pos[i].setx(blocks[block_index].pos[i].getX() - 1);
				update_char_in_board(blocks[block_index].pos[i], block);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				blocks[block_index].pos[i].setx(blocks[block_index].pos[i].getX() - 1);
				update_char_in_board(blocks[block_index].pos[i], block);
			}
		}

	}
	void delete_block_from_screen(char block)
	{
		int block_index = block - '0';
		if (block_index > 1)
		{
			for (int i = 0; i < 2; i++)
			{
				gotoxy(blocks[block_index].pos[i].getX(), blocks[block_index].pos[i].getY());
				update_char_in_board(blocks[block_index].pos[i], ' ');
				cout << " ";
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				gotoxy(blocks[block_index].pos[i].getX(), blocks[block_index].pos[i].getY());
				update_char_in_board(blocks[block_index].pos[i], ' ');
				cout << " ";
			}
		}
	}
	void set_num_of_blocks(int n) {
		num_of_blocks = n;
	}
}; 
