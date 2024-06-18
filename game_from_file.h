#pragma once
#include "Game.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <Windows.h>
class Game_From_File : public Game {
protected:
    std::fstream file_ptr;
    int move_index;
    std::vector<Timer> timers;
    std::vector<char> chars;
public:

    Game_From_File(const std::string& filename){
        Game::record_mode = false;
        Game::game_from_keyboard = false;
        silent_mode = false;
        move_index = 0;
        player.set_life(3);
        init();
        set_file_name(filename);
        file_ptr.open(file_name, std::ios::in | std::ios::out);
        if (!file_ptr.is_open()) {
            std::cerr << "Unable to open file: " << file_name << std::endl;
            exit(0);
        }
        current_level_index = getStepNumber() - 1;
        build_vectors_from_file();
        levels_arr[current_level_index].board.reset_board();
        //levels_arr[current_level_index].board.show(is_color)   
        show_board();
    }
    Game_From_File() {
        Game::record_mode = false;
        Game::game_from_keyboard = false;
        move_index = 0;
        player.set_life(3);
        init();
        set_file_name("tb01.steps");
        current_level_index =0;
        build_vectors_from_file();
        levels_arr[current_level_index].board.reset_board();
        
    }
    virtual void show_board_to_user()const {
        levels_arr[current_level_index].board.show(is_color);
    }
    virtual void write_to_result_file(bool is_won) {

    }

    void build_vectors_from_file() override{
        std::ifstream file(file_name);
        if (file.is_open()) {
            std::string firstLine;
            std::getline(file, firstLine);
            std::string firstLineDigits;
            for (char c : firstLine) {
                if (std::isdigit(c)) {
                    firstLineDigits += c;
                }
                else {
                    cout << "Error in file openning";
                    exit(0);
                }
            }
            // Convert the firstLineDigits string to an integer
            int firstLineValue = std::stoi(firstLineDigits);
            is_color = GameConfig::char_as_bool(firstLineValue);
            int minute, second, millisecond;
            int charCode;
            while (file >> minute >> second >> millisecond >> charCode) {
                timers.emplace_back(minute, second, millisecond);
                chars.push_back(static_cast<char>(charCode));
            }
            file.close();
        }
        else {
            return;
        }
    }
    int getStepNumber() {
        std::string suffix = ".steps";
        size_t pos = file_name.rfind(suffix);
        if (pos != std::string::npos) {
            std::string numStr;
            for (int i = pos - 1; i >= 0; i--) {
                if (std::isdigit(file_name[i])) {
                    numStr = file_name[i] + numStr;
                }
                else {
                    break;
                }
            }
            if (!numStr.empty()) {
                return std::stoi(numStr);
            }
        }
        return -1;
    }
    virtual void Sleeping() const override {
        Sleep(2);
    }
    // Destructor
    ~Game_From_File() {
        if (file_ptr.is_open()) {
            file_ptr.close();
        }
        
    }

    // Method to get the current file name
    std::string getfile_name() const {
        return file_name;
    }

    char char_from_keyboard() override {
        move_index++;
       if((move_index-1)<chars.size())
        return chars[move_index - 1];
        return '\0';
    }
    void update_file_name ()override {
        string res = "tb0";
        res.append(std::to_string(current_level_index + 1));
        res.append(".steps");
        res.append(".txt");
        file_name = res;
    }
    
    int char_is_pressed() const override  {
        if(move_index<timers.size())
        return timers[move_index].compare(levels_arr[current_level_index].get_timer());
        return false;
    }
    bool is_esc()override {
        gotoxy(9, 1);
        cout << "press 9 to exit and escape to resume";
        char temp = _getch();
        while (temp != 27 && temp != '9')
        {
            temp = _getch();
        }
        if (temp == '9') {
            clrscr();
            return true;
        }
        gotoxy(9, 1);
        cout << "                                    ";
        return false;
    }
};