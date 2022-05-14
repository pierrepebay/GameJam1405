#ifndef _RENDER_H
#define _RENDER_H

#include "main.h"
#include "map.h"
#include "player.h"
#include "gest_event.h"
#include "mob.h"

// include pthread
#include <pthread.h>
//include unistd
#include <unistd.h>

#define TILE_SIZE 24

#define NB_TO_SHOW_X 10
#define NB_TO_SHOW_Y 5

// include SDL2 libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


void MainDrawLoop();



#endif