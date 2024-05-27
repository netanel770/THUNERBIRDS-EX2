#pragma once
#define MAX_LIFE 3 
class Player {
	int life;
public:
	
	int get_life() {
		return life;
	}
	void set_life(int life1) {
		life = life1;
	}
	void init() {
		life = MAX_LIFE;
	}
	void reduce_life() {
		life--;
	}
	void print_life() {
		gotoxy(18, 2);
		cout << "Current life is:" << life;
	}
};

