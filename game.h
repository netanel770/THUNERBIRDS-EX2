#pragma once
#include<iostream>
#include "Board.h"
#include "player.h"
#include "timer.h"
#include <Windows.h>
#include <conio.h>
#include "io_utils.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "level.h"
class Game {
    constexpr static size_t num_of_levels = 3;
    Timer timer;
    Player player;
    char current_ship = 'b';
    bool is_color;
    level levels_arr[num_of_levels];
public:
    void init() {
        levels_arr[0].bulid_board_from_file("tb1.screen.txt");
        //levels_arr[0].get_board().init();
    }
    void set_is_color(bool n) {
        is_color = n;
    }
    void menu() {
        GameConfig::show_menu();
        bool is_exit = false;
        int choice = 0;
        char back_to_menu;
        while (true) {
            std::cin >> choice;
            switch (choice) {
            case 1:
                std::cout << "Starting a new game without colors...\n";
                levels_arr[0].get_board().reset_board();
                is_color = false;
                levels_arr[0].get_board().show(is_color);
                is_exit = running_game();
                clrscr();
                GameConfig::show_menu();
                break;
            case 2:
                std::cout << "Starting a new game with colors...\n";
                levels_arr[0].get_board().reset_board();
                is_color = true;
                levels_arr[0].get_board().show(is_color);
                is_exit = running_game();
                clrscr();
                GameConfig::show_menu();
                break;
            case 8:
                clrscr();
                GameConfig::print_instructions();
                std::cout << "\n\nPress enter to continue...\n";
                back_to_menu = _getch();
                while (back_to_menu != 13)
                    back_to_menu = _getch();
                clrscr();
                GameConfig::show_menu();
                break;
            case 9:
                return; // Exit the program
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
                break;
            }
        }

    }
    void set_current_ship(char ch) {
        current_ship = ch;
    }
    bool matchesPattern(const std::string& filename) {
        const std::string prefix = "tb";
        const std::string suffix = ".screen.txt";
        return filename.size() >= prefix.size() + suffix.size() &&
            filename.compare(0, prefix.size(), prefix) == 0 &&
            filename.compare(filename.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
    std::string readFileContent(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf(); // Read the file content into the stringstream
        file.close();
        return buffer.str(); // Convert stringstream to string and return
    }

    bool checking_game_details() {
        if (timer.time_is_over() && player.get_life() > 0)
        {
            levels_arr[0].get_board().reset_board();
            levels_arr[0].get_board().show(is_color);
            player.reduce_life();
            timer.reset_to_start();
            return true;
        }
        return false;
    }
    void print_current_ship() {
        gotoxy(60, 2);
        cout << "current ship:"<<current_ship;
    }
    char updating_current_ship(char current_ship, char pressed_char) {
        if (current_ship == (char)GameConfig::eKeys::SMALL_SHIP ||
            current_ship == (char)GameConfig::eKeys::UPPER_SMALL_SHIP) {
            if (pressed_char == (char)GameConfig::eKeys::BIG_SHIP ||
                pressed_char == (char)GameConfig::eKeys::UPPER_BIG_SHIP)
                current_ship = (char)GameConfig::eKeys::BIG_SHIP;
        }
        if (current_ship == (char)GameConfig::eKeys::BIG_SHIP ||
            current_ship == (char)GameConfig::eKeys::UPPER_BIG_SHIP) {
            if (pressed_char == (char)GameConfig::eKeys::SMALL_SHIP ||
                pressed_char == (char)GameConfig::eKeys::UPPER_SMALL_SHIP)
                current_ship = (char)GameConfig::eKeys::SMALL_SHIP;
        }
        print_current_ship();
        return current_ship;
    }
    // File containing the list of filenames
    void get_levels_details() {
        std::ifstream fileList("file_list.txt");

        // Check if the file_list.txt file opened successfully
        if (!fileList) {
            std::cerr << "Unable to open file_list.txt" << std::endl;
            return;
        }

        // Vector to store matching file names
        std::vector<std::string> matchingFiles;
        std::string filename;

        // Read file names from the text file
        while (std::getline(fileList, filename)) {
            if (matchesPattern(filename)) {
                matchingFiles.push_back(filename);
            }
        }

        // Close the file list input file stream
        fileList.close();

        // Sort the file names lexicographically
        std::sort(matchingFiles.begin(), matchingFiles.end());

        // Read and print files in lexicographical order
        for (const auto& fname : matchingFiles) {
            std::string content = readFileContent(fname);
            if (!content.empty()) {
                std::cout << "Contents of file: " << fname << std::endl;
                std::cout << content << std::endl;
            }
            else {
                std::cerr << "Failed to read the content of the file: " << fname << std::endl;
            }
        }
    }
    bool is_esc() {
        char temp;
        clrscr();
        gotoxy(1, 1);
        std::cout << "Game paused, press ESC again to continue or 9 to Exit";
        temp = _getch();
        while (temp != 27 && temp != '9')
            temp = _getch();
        if (temp == '9')
            return true;
        clrscr();
        levels_arr[0].get_board().show(is_color);
        return false;
    }
    int left_or_right(char pressed_char, int index, char current_ship_shape) {
        Point point1, point2;
        if (current_ship == 's') {
            int direction = 1;
            int pos_index = 1;
            if (GameConfig::is_left(pressed_char)) {
                direction = -1;
                pos_index = 0;
            }
            point2.set(levels_arr[0].get_board().ships[index].getPos(pos_index).getX() + direction, levels_arr[0].get_board().ships[0].getPos(pos_index).getY());
            point1.set(1, 1);
        }
        else {
            int direction = 1;
            int first_index = 1;
            int second_index = 3;
            if (GameConfig::is_left(pressed_char)) {
                direction = -1;
                first_index = 0;
                second_index = 2;
            }
            point1.set(levels_arr[0].get_board().ships[index].getPos(first_index).getX() + direction, levels_arr[0].get_board().ships[index].getPos(first_index).getY());
            point2.set(levels_arr[0].get_board().ships[index].getPos(second_index).getX() + direction, levels_arr[0].get_board().ships[index].getPos(second_index).getY());
        }
        int isAvalable = levels_arr[0].get_board().is_available(point1, point2, current_ship);
        if (levels_arr[0].get_board().is_exit_point(point1, point2, current_ship)) {
            levels_arr[0].get_board().delete_ship_from_screen(current_ship_shape);
            if (levels_arr[0].get_board().ships[0].get_is_finish() && levels_arr[0].get_board().ships[1].get_is_finish())
                return 1;
        }
        else if (isAvalable && !levels_arr[0].get_board().ships[index].get_is_finish()) {
            if (isAvalable == 1) {
                levels_arr[0].get_board().delete_ship_from_screen(current_ship_shape);
                if (GameConfig::is_left(pressed_char))
                    levels_arr[0].get_board().move_left_the_ship(current_ship_shape);
                else
                    levels_arr[0].get_board().move_right_the_ship(current_ship_shape);
                levels_arr[0].get_board().ships[index].print_ship(is_color);
            }
            if (isAvalable == 2)
            {
                char block_shape = levels_arr[0].get_board().board[point2.getY()][point2.getX()];
                if (block_shape > '1')
                {
                    if (GameConfig::is_left(pressed_char))
                        point2.set(levels_arr[0].get_board().blocks[block_shape - '0'].getPos(0).getX() - 1, levels_arr[0].get_board().blocks[block_shape - '0'].getPos(0).getY());
                    else
                        point2.set(levels_arr[0].get_board().blocks[block_shape - '0'].getPos(1).getX() + 1, levels_arr[0].get_board().blocks[block_shape - '0'].getPos(1).getY());
                    point1.set(1, 1);

                }
                else {
                    if (GameConfig::is_left(pressed_char)) {
                        point1.set(levels_arr[0].get_board().blocks[block_shape - '0'].getPos(0).getX() - 1, levels_arr[0].get_board().blocks[block_shape - '0'].getPos(0).getY());
                        point2.set(levels_arr[0].get_board().blocks[block_shape - '0'].getPos(2).getX() - 1, levels_arr[0].get_board().blocks[block_shape - '0'].getPos(2).getY());
                    }
                    else {
                        point1.set(levels_arr[0].get_board().blocks[block_shape - '0'].getPos(1).getX() + 1, levels_arr[0].get_board().blocks[block_shape - '0'].getPos(1).getY());
                        point2.set(levels_arr[0].get_board().blocks[block_shape - '0'].getPos(3).getX() + 1, levels_arr[0].get_board().blocks[block_shape - '0'].getPos(3).getY());
                    }
                }
                if (levels_arr[0].get_board().is_available(point1, point2, block_shape) == 1) {
                    levels_arr[0].get_board().delete_block_from_screen(block_shape);
                    if (GameConfig::is_left(pressed_char))
                        levels_arr[0].get_board().move_left_the_block(block_shape);
                    else
                        levels_arr[0].get_board().move_right_the_block(block_shape);
                    levels_arr[0].get_board().blocks[block_shape - '0'].print_block(block_shape, is_color);
                    levels_arr[0].get_board().delete_ship_from_screen(current_ship_shape);
                    if (GameConfig::is_left(pressed_char))
                        levels_arr[0].get_board().move_left_the_ship(current_ship_shape);
                    else
                        levels_arr[0].get_board().move_right_the_ship(current_ship_shape);
                    levels_arr[0].get_board().ships[index].print_ship(is_color);
                }
            }
        }
        return 0;
    }
    int up_or_down(char pressed_char, int index, char current_ship_shape) {
        Point point1, point2;
        int direction = -1;
        if (GameConfig::is_down(pressed_char))
            direction = 1;
        if (current_ship == 's' || GameConfig::is_up(pressed_char)) {
            point1.set(levels_arr[0].get_board().ships[index].getPos(0).getX(), levels_arr[0].get_board().ships[index].getPos(0).getY() + direction);
            point2.set(levels_arr[0].get_board().ships[index].getPos(1).getX(), levels_arr[0].get_board().ships[index].getPos(1).getY() + direction);
        }
        else
        {
            point1.set(levels_arr[0].get_board().ships[index].getPos(2).getX(), levels_arr[0].get_board().ships[index].getPos(2).getY() + direction);
            point2.set(levels_arr[0].get_board().ships[index].getPos(3).getX(), levels_arr[0].get_board().ships[index].getPos(3).getY() + direction);
        }
        if (levels_arr[0].get_board().is_exit_point(point1, point2, current_ship)) {
            levels_arr[0].get_board().delete_ship_from_screen(current_ship_shape);
            if (levels_arr[0].get_board().ships[0].get_is_finish() && levels_arr[0].get_board().ships[1].get_is_finish())
                return 1;
        }
        else if ((levels_arr[0].get_board().is_available(point1, point2, current_ship) == 1) && !levels_arr[0].get_board().ships[index].get_is_finish())
        {
            levels_arr[0].get_board().delete_ship_from_screen(current_ship_shape);
            if (GameConfig::is_down(pressed_char))
                levels_arr[0].get_board().move_down_the_ship(current_ship_shape);
            else
                levels_arr[0].get_board().move_up_the_ship(current_ship_shape);
            levels_arr[0].get_board().ships[index].print_ship(is_color);
        }
        return 0;
    }
    int running_game()
    {
        print_current_ship();
        char current_ship_shape;
        player.init();
        timer.reset_to_start();
        char pressed_char = 'b';
        int index;
        while (timer.reduce_mili_second() && player.get_life() != 0) {
            hideCursor();
            Point point1, point2;
            if (checking_game_details()) {
                pressed_char = 'b';
                current_ship = 'b';
                current_ship_shape = '#';
            }
            timer.print_timer();
            player.print_life();
            gotoxy(18, 2);
            cout << "asdadsadsa";
            Sleep(100);
            if (_kbhit()) {
                gotoxy(85, 1);
                char temp = _getch();
                if (GameConfig::charInString("AWDXSBawdsxb", temp))
                    pressed_char = temp;
                if (pressed_char == 27)
                {
                    if (is_esc())
                        return 1;
                }
                current_ship = updating_current_ship(current_ship, pressed_char);
            }
            if (current_ship == 's') {
                index = 0;
                current_ship_shape = '@';
            }
            else {
                index = 1;
                current_ship_shape = '#';
            }
            if (GameConfig::is_up(pressed_char) || GameConfig::is_down(pressed_char))
            {
                if (up_or_down(pressed_char, index, current_ship_shape))
                    return 1;
            }

            if (GameConfig::is_left(pressed_char) || (GameConfig::is_right(pressed_char)))
            {
                if (left_or_right(pressed_char, index, current_ship_shape))
                    return 1;
            }
        }
    return 0;
}
    
};
