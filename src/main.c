#include "main.h"


int isRunning;
int GameOption;

int main(){


    isRunning = 1;
    GameOption = 0;

    //initMap();
    //printMap();
    readMap();
    player = initPlayer(6,66);
    initMobs();
    MainDrawLoop();
}
