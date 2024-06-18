#pragma once
#include "board.h"
#include "timer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class level {
	
	Timer timer;
public:
    Board board;
	void bulid_board_from_file(string file_name) {
        std::ifstream file(file_name);
        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            exit(0);
        }
        std::stringstream part1, part2;
        bool isPart1 = true;
        char ch;

        while (file.get(ch)) {
            if (ch == 'W' && isPart1) {
                isPart1 = false;
            }
            if (isPart1) {
                part1 << ch;
            }
            else {
                part2 << ch;
            }
        }

        file.close();
        std::string part1Str = part1.str();
        std::string part2Str = part2.str();
        copy_board(part2Str);
        while (!part1Str.empty() && std::isspace(part1Str.back())) {
            part1Str.pop_back();
        }
     
        bulid_obj_from_string(part1Str);
	}
    std::vector<int> getNumbersFromString(const std::string& str) {
        std::vector<int> numbers;
        std::stringstream ss(str);
        std::string temp;
        int number;
        // Use stringstream to extract numbers separated by spaces
        while (ss >> temp) {
            try {
                number = std::stoi(temp); // Convert string to int
                numbers.push_back(number);
            }
            catch (std::invalid_argument&) {
                // Ignore non-numeric words
            }
        }
        return numbers;
    }
    
    void bulid_block_from_vector(std::vector<int>info) {
        int info_index = 14;
        int size_of_block = info[info_index];
        for (int i = 0; i <info[13] ; i++) {
            size_of_block = info[info_index];
            info_index++;
            board.blocks[i].set_size(size_of_block);
            board.org_blocks[i].set_size(size_of_block);
            for (int j = 0; j < size_of_block; j++) {
                board.blocks[i].pos[j].set(info[info_index], info[info_index+1]);
                board.org_blocks[i].pos[j].set(info[info_index], info[info_index + 1]);
                info_index += 2;
            }
        }
    }
    Timer get_timer()const {
        return timer;
    }
    void reset_timer_to_start() {
        timer.reset_to_start();
    }
    bool reduce_second_for_timer() {
       return  timer.reduce_mili_second();
    }
    void bulid_obj_from_string(const std::string& str) {
        int i = 0;
        std::vector<int>info = getNumbersFromString(str);
        board.set_num_of_blocks(info[13]);
        board.init();
        timer.update_time_from_file(info[0]);
        board.ships[1].set_locations_big_ship(info[1], info[2], info[3], info[4], info[5], info[6], info[7], info[8]);
        board.ships[0].set_locations_small_ship(info[9], info[10], info[11], info[12]);
        board.org_big.set_locations_big_ship(info[1], info[2], info[3], info[4], info[5], info[6], info[7], info[8]);
        board.org_small.set_locations_small_ship(info[9], info[10], info[11], info[12]);
        bulid_block_from_vector(info);
       
    }
    
    void copy_board(const std::string& str) {
        int row = 0;
        int col = 0;
        for (char ch : str) {
            if (ch == '\n') {
                col = 0;
                row++;
            }
            else {
                if (row < Board::HEIGHT && col < Board::WIDTH) {
                    board.board[row][col] = ch;
                    board.original_board[row][col] = ch;
                    col++;
                }
            }
        }
    }

	
    Board get_board()const {
        return board;
    }
};
