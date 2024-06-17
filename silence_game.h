#pragma once
#include "game_from_file.h"
#include "timer.h"
class silence_game :Game_From_File {
	int results_life_from_file[num_of_levels];
	Timer results_time_from_file[num_of_levels];
	int results_life_from_game[num_of_levels];
	Timer results_time_from_game[num_of_levels];


public:
	silence_game() {
		string current_file_name;
		silent_mode = true;
		move_index = 0;
		Game::record_mode = false;
		Game::game_from_keyboard = false;
		player.set_life(3);
		init();
		int minute, second, mili;
		current_level_index = 0;
			for (int i = 0; i < num_of_levels; i++) {
				current_file_name = build_steps_file_name(".results");
				std::ifstream file(current_file_name);
				if (file >> results_life_from_file[i] >> minute >> second >> mili) {
					results_time_from_file[i].set_minute(minute);
					results_time_from_file[i].set_second(second);
					results_time_from_file[i].set_mili_second(mili);
					current_level_index++;
				}
				file.close();
			}
			set_file_name("tb01.steps.txt");
			build_vectors_from_file();
			set_file_name("tb02.steps.txt");
			build_vectors_from_file();
			set_file_name("tb03.steps.txt");
			build_vectors_from_file();
			for(int i=0;i<num_of_levels;i++)
				levels_arr[i].board.reset_board();
		
	}
	
	
	void show_board()override {

	}
	void check_result() {
		int res;
		current_level_index = 0;
		res=running_game();
		if (res == 0) {
			current_level_index++;
			res = running_game();
		}
		if (res == 0) {
			current_level_index++;
			res = running_game();
		}
		for (int i = 0; i < 3; i++) {
			if (results_life_from_game[i] != results_life_from_file[i] ||
				results_time_from_game[i].compare(results_time_from_file[i]) == false) {
				gotoxy(1, 1);
				cout << "test failed!";
				return;
			}
		}
		gotoxy(1, 1);
		cout << "test succeeded!";
	}
	
	void write_to_result_file (bool is_won) override {
		if (is_won) {
			results_life_from_game[current_level_index] = player.get_life();
			results_time_from_game[current_level_index].set_minute(levels_arr[current_level_index].get_timer().get_minute());
			results_time_from_game[current_level_index].set_second(levels_arr[current_level_index].get_timer().get_second());
			results_time_from_game[current_level_index].set_mili_second(levels_arr[current_level_index].get_timer().get_mili_second());
		}
		else {
			results_life_from_game[current_level_index] = 0;
			results_time_from_game[current_level_index].set_minute(0);
			results_time_from_game[current_level_index].set_second(0);
			results_time_from_game[current_level_index].set_minute(0);
		}
	}
	 void Sleeping() override {
		 //Sleep(1);
	}

};