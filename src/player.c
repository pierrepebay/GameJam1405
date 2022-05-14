#include "player.h"
#include "gest_event.h"

player_t * player;

player_t * initPlayer(float x, float y) {
  player_t* player = (player_t*)malloc(sizeof(player_t));
  if(!player) {
    printf("Player initalization failed.\n");
    exit(ALLOCATION_FAILURE);
  }
  else {
    player->x = x;
    player->y = y;

    player->xSpeed = 0;
    player->ySpeed = 0;

    player->health = 100;

    player->direction = 1;
    player->isGrounded = 0;
    player->isJumping = 0;
    player->isAttacking = 0;
    player->isFalling = 0;
    player->isTakingDmg = 0;
  }
  return player;
}

int checkCollisionX(){
  int case_right = ceilf(player->x);
  int case_left = floorf(player->x);
  int case_bot = floorf(player->y) + player->h;
  int case_top = case_bot - 1;

  if (map[case_bot][case_right] || map[case_top][case_right]){
    player->xSpeed = 0;
    return 2;
  }

  if (map[case_bot][case_left] || map[case_top][case_left]){
    player->xSpeed = 0;
    return 1;
  }
}

int playerMoveX(){
  switch (checkCollisionX()) {
    case 0: // no collisions
      if (fabs(player->xSpeed) < PLAYER_MAX_SPEED_X){
        player->xSpeed += MOVEMENT_SPEED * (Keys[1] - Keys[3]);
      }
      int signe = 1;
      if (player->xSpeed > 0){
        signe = -1;
      }
      player->xSpeed += signe * FRICTION;
      break;

    case 1: // left side collided
      player->xSpeed +=MOVEMENT_SPEED * Keys[1];
      player->x += player->xSpeed;
      break;

    case 2: // right side collided
      player->xSpeed +=MOVEMENT_SPEED * Keys[3];
      player->x += player->xSpeed;
      break;
  }
}

void gestPhysique(){
  playerMoveX();
}


void updatePlayerState(player_t * player) {
  int i = player->y / 2 + 1;
  int j = player->x / 2 + 1;
  if(map[i + 1][j]) {
    player->isGrounded = 1;
    player->isFalling = 0;
    player->isJumping = 0;
  }
  else {
    if(player->ySpeed > 0) {
      player->isFalling = 1;
      player->isJumping = 0;
    }
    else {
      player->isFalling = 0;
      player->isJumping = 1;
    }
    player->isGrounded = 0;
  }
}

void updatePlayer(player_t * player) {
  int i = player->y / 2 + 1;
  int j = player->x / 2 + 1;
  if(player->xSpeed > 0) {
    if (map[i, j+1]) {
      player->xSpeed = 0;
    }
    else {
      player->x += player->xSpeed;
    }
  }
  else {

  }
}
