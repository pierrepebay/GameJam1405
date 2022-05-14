#ifndef _MOB_HEADER_
#define _MOB_HEADER_

#define ALLOCATION_FAILURE 1

#define MAX_MOB_N 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "map.h"
#include "player.h"

typedef struct mob{
    float x;
    float y;

    float xSpeed;
    float ySpeed;

    float xHitbox; // taille de la hitbox
    float yHitbox;

    int w; // offset entre x et le coin de la hitbox
    int h;

    int health;

    int direction;

    int isGrounded;
    int isFalling;
    int isAttacking;
    int isCharging;
    int isTakingDmg;
}mob_t;

mob_t * mobsList[MAX_MOB_N];

mob_t * initMob(float x, float y);
void initMobs(int n);
void moveMobs(player_t * player);
void updateMobsState();

#endif
