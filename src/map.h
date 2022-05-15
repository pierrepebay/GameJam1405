#ifndef _MAP_H_
#define _MAP_H_

#define MAP_W  208
#define MAP_H  80

#include <stdio.h>

extern int map[MAP_H][MAP_W];


void initMap();

void printMap();

void readMap();


#endif