#pragma once
#define STARTING_MINUTE 3
#define STARTING_SECOND 0
#include <iostream>
using namespace std;
class Timer {
	int minute;
	int second;
	int mili_second;
public:
	Timer() {

		minute = STARTING_MINUTE;
		second = STARTING_SECOND;
		mili_second = 0;
	}
	void init(int min1, int second1, int mili_second1) {
		minute = min1;
		second = second1;
		mili_second = mili_second1;
	}
	void set_second(int second1) {
		second = second1;
	}
	void set_mili_second(int mili_second1) {
		mili_second = mili_second1;
	}
	void set_minute(int minute1) {
		minute = minute1;
	}
	int get_second() {
		return second;
	}
	int get_mili_second() {
		return mili_second;
	}
	int get_minute() {
		return minute;
	}

	void print_timer() {
		gotoxy(9, 2);
		cout << minute << ":" << second << ":" << mili_second << std::endl;

	}
	bool time_is_over() {
		return (minute == 0 && second == 0 && mili_second == 0);
	}
	void reset_to_start() {
		minute = STARTING_MINUTE;
		second = STARTING_SECOND;
		mili_second = 0;
	}
	bool reduceTime() {
		
		mili_second -= 100;
		if (mili_second < 0) {
			mili_second += 1000;
			second--;
		}

		if (second < 0) {
			second += 60;
			minute--;
		}
		return (minute > 0 || second > 0 || mili_second > 0);
	}
	bool reduce_mili_second() {
		if (second == 0 && minute == 0 && mili_second == 0)
			return false;
		else if (second == 0 && mili_second == 0) {
			second = 59;
			minute--;
			mili_second = 900;
		}
		else if (mili_second <= 0) {
			mili_second = 900;
			second--;
		}
		else {
			mili_second -= 100;
		}
		return true;
	}
	

};