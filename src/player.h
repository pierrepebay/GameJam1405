#ifndef _PLAYER_HEADER_
#define _PILE_HEADER_

#define ALLOCATION_FAILURE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct player{
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
    int isTakingDmg;
}player_t;

void initPlayer(float x, float y);


#endif
