#pragma once

#include <iostream>
using namespace std;
class Timer {
	int minute;
	int second;
	int org_minute;
	int org_second;
	int mili_second;
public:
	Timer() {

		minute = 0;
		second = 0;
		mili_second = 0;
		org_minute = 0;
		org_second = 0;
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
		minute =org_minute;
		second = org_second;
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
	void update_time_from_file(int num) {
		minute = num / 1000;
		second = (num%1000)/10;
		mili_second = 0;
		org_second = second;
		org_minute = minute;
	}
	

};