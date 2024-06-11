#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
#include <string>
#include <iostream>
class GameConfig
{
	
public:
	enum class eKeys {
		LEFT = 'a', UPPER_LEFT = 'A', UPPER_RIGHT = 'D', RIGHT = 'd', UP = 'w', UPPER_UP = 'W', DOWN = 'x'
		, UPPER_DOWN = 'X', ESC = 27, UPPER_SMALL_SHIP = 'S', SMALL_SHIP = 's', UPPER_BIG_SHIP = 'B', BIG_SHIP = 'b',MINX=0,MINY=0
	};
	static constexpr int GAME_WIDTH = 20;
	static constexpr int GAME_HEIGHT = 20;
	static const int COLORS[];
	static const int NUM_OF_COLORS;
	static bool charInString(std::string str, char ch) {
		for (char c : str) {
			if (c == ch||ch==27) {
				return true;
			}
		}
		return false;
	}
	void static show_menu() {
		std::cout << "Menu\n\n\n\n";
		std::cout << "(1) Start a new game without colors\n";
		std::cout << "(2) Start a new game with colors\n";
		std::cout << "(3) Choose a specific level with colors\n";
		std::cout << "(4) Choose a specific level without colors\n";
		std::cout << "(8) Present instructions and keys\n";
		std::cout << "(9) EXIT\n";
	}
	void static show_levels_menu() {
		std::cout << "levels menu\n\n\n\n";
		std::cout << "(1) level 1\n";
		std::cout << "(2) level 2\n";
		std::cout << "(3) level 3\n";
	}
	static void print_instructions() {
		std::cout << "Purpose of the game : Reach the endpoint(x) with both spaceships.\n\nSmall spacecraft : --\nLarge spacecraft : ++\nblocks are symbolds by numbers between a to e or blue blocks\nTo reach the endpoint, navigate through the maze and move blocks if necessary.Remember :\n\nSmall spaceship can move blocks of size 2 or smaller.\nLarge spaceship can move blocks of size 6 or smaller.\nPress 'S' to control the small spaceship, and 'B' for the large spaceship.\nMovement controls :\nTo move right : press 'd'\nTo move left : press 'a'\nTo move down : press 'x'\nTo move up : press 'w'\n to pause press esc\nGood luck!\n";
	}
	static bool is_down(char c) {
		return(c == (char)GameConfig::eKeys::DOWN || c == (char)GameConfig::eKeys::UPPER_DOWN);
	}
	static bool is_up(char c) {
		return(c == (char)GameConfig::eKeys::UP || c == (char)GameConfig::eKeys::UPPER_UP);
	}

	static bool is_left(char c) {
		return(c == (char)GameConfig::eKeys::LEFT || c == (char)GameConfig::eKeys::UPPER_LEFT);
	}
	static bool is_right(char c) {
		return(c == (char)GameConfig::eKeys::RIGHT || c == (char)GameConfig::eKeys::UPPER_RIGHT);
	}
	static void print_char(const char c,bool color_on) {
		if (color_on)
		{
			if (c == 'W') {
				std::cout << "\033[37;47m□\033[0m";
			}
			else if (std::isdigit(c)) {
				std::cout << "\033[30;44m" << " " << "\033[0m";
			}
			else
				if (c == '@') {
					std::cout << "\033[30;45m" << "-" << "\033[0m";
				}
				else if (c == '#') {
					std::cout << "\033[30;41m" << "+" << "\033[0m";
				}
				else {
					std::cout << c;
				}
		}
		else {
			if (c == '0') {
				std::cout << "a";
			}
			else if (c == '1') {
				std::cout << "b";
			}
			else if (c == '2') {
				std::cout << "c";
			}
			else if (c == '3') {
				std::cout << "c";
			}
			else if (c == '4') {
				std::cout << "d";
			}
			else
				if (c == '@') {
					std::cout <<  "-";
				}
				else if (c == '#') {
					std::cout << "+";
				}
			else {
				std::cout << c;
			}
		}
	}
};
#endif
