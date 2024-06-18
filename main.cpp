#include <iostream>
#include "Game.h"
#include "level.h"
#include <fstream>
#include <sstream>
#include <string>
#include "game_from_file.h"
#include "silence_game.h"
#include <cstring>
//Names:Netanel Mirel,Albe Alrod


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "ERROR! please enter user paramter";
        return 1;
    }
     if (strcmp(argv[1] ,"thunderbirds.exe")==0) {
        Game theGame;
        theGame.init();
        theGame.set_record_mode(false);
        theGame.menu();
    }
     else if (strcmp(argv[1],"thunderbirds.exe-save")==0) {
        Game theGame;
        theGame.init();
        theGame.set_record_mode(true);
        theGame.menu();
    }
    
       
       else if (strcmp(argv[1], "thunderbirds.exe-load") == 0) {
           Game_From_File gff("tb01.steps.txt");
           gff.running_game();
       }
       else if (strcmp(argv[1], "thunderbirds.exe-silent") == 0) {
           silence_game sc;
           sc.check_result();
       }
       else
           std::cerr << "ERROR the only user parameters which allowed are:\nthunderbirds.exe\nthunderbirds.exe -load\nthunderbirds.exe -save\nthunderbirds.exe -silent" << std::endl;
        
    return 0;
}








