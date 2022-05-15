#include "map.h"

int map[MAP_H][MAP_W];

void initMap(){
    int i;
    int j;
    for (i=0; i<MAP_H; ++i){
        for (j=0; j<MAP_W; ++j){
            map[i][j] = 0;
        }
    }
    for (i=MAP_H/2; i < MAP_H; ++i){
        for (j= 0; j < MAP_W; ++j){
            map[i][j] = 1;
        }
    }
    for (int i=0; i < MAP_H; i++){
        map[i][0] = 1;
        map[i][1] = 1;
        map[i][MAP_W-2] = 1;
        map[i][MAP_W-1] = 1;
    }
    for (int i = 0; i < MAP_W; i++){
        map[0][i] = 1;
        map[1][i] = 1;
    }
    map[7][20] = 2;
    map[7][21] = 2;
    map[8][21] = 2;
    map[9][21] = 2;
}

void printMap(){
    for (int i = 0; i < MAP_H; i++){
        for (int j = 0; j < MAP_W; j++){
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}