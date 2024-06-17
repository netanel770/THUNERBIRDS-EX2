#include <iostream>
#include "Game.h"
#include "level.h"
#include <fstream>
#include <sstream>
#include <string>
#include "game_from_file.h"
#include "silence_game.h"
//Names:Netanel Mirel,Albe Alrod

int main() {
    Game theGame;
    theGame.init();
    theGame.menu();
    //Game_From_File gff("tb02.steps.txt");
    //gff.running_game();
    //gff.get_levels_arr()[2].board.reset_board();
    //gff.get_levels_arr()[2].board.show(false);
    //level l;
    //l.bulid_board_from_file("tb1.screen.txt");
    //l.get_board().show(false);
   // silence_game sc;
   // sc.check_result();
    return 0;
}







