#include "main.h"


int isRunning;
int GameOption;

int main(){


    isRunning = 1;
    GameOption = 0;

    initMap();
    printMap();
    player = initPlayer(20, 10);
    MainDrawLoop();
}