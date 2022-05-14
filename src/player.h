#ifndef _PLAYER_HEADER_
#define _PLAYER_HEADER_

#define ALLOCATION_FAILURE 1

#define MOVEMENT_SPEED 0.000002
#define PLAYER_MAX_SPEED_X 0.000002
#define PLAYER_MAX_SPEED_Y 0.000002

#define PLAYER_MAX_ACCEL_X 1
#define GRAVITY 9.81
#define JUMP 0.7
#define FRICTION 0.000001

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
    int isJumping;
    int isFalling;
    int isAttacking;
    int isTakingDmg;
}player_t;

extern player_t * player;

player_t * initPlayer(float x, float y);
int checkCollisionX();
int playerMoveX();
void gestPhysique();

void updatePlayerState(player_t * player);
void updatePlayer(player_t * player);


#endif
