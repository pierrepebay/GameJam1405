#include "main.h"


int isRunning;
int GameOption;

int main(){


    isRunning = 1;
    GameOption = 0;

    initMap();
    //printMap();
    player = initPlayer(10, 10);
    initMobs();
    MainDrawLoop();
}