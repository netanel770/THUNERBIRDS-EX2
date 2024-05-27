#pragma once
#include "board.h"
#include "timer.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class level {
	Board board;
	Timer timer;
	void init() {
		board.init();
	}
public:
	void update_data_members_from_file(string file_name) {
		std::ifstream file(file_name);
		string line;
		//getline(file, line);
		while (getline(file, line)) {
			std::cout << line << std::endl; // Read and print each line
		}
		file.close();
	
	}


};
