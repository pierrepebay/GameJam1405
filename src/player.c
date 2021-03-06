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

    player->w = 1;
    player->h = 2;

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


int checkCollisionY(){

    int case_x = floorf(player->x + player->w); ;

    int case_y = floorf(player->y + player->ySpeed );

        if (map[case_y][case_x]){

            player->ySpeed = 0;
            player->isGrounded = 1;
            return 1;
        }
        else {
            player->isGrounded = 0;
        }

    return 0;
}

int checkCollisionY2(){

    int case_x = floorf(player->x + player->w/4);

    int case_y = floorf(player->y + player->ySpeed );

    int case_y2 = case_y - 1.5;

        if (map[case_y2][case_x]) {
          player->ySpeed = 0;
          player->isGrounded = 0;
          return 1;
        }

    return 0;
}

int PlayerMoveY(){
    if (checkCollisionY(player)){
        player->ySpeed = -JUMP * (Keys[0]);
    }
    else{
      //checkCollisionY2();
      if(!player->isGrounded) {
        player->ySpeed += GRAVITY;
      }
    }
   player->y += player->ySpeed;
    return 1;
}

int checkTP() {
  if((fabs(player->x - 140) < 0.2) && (fabs(player->y - 45) < 0.2)) {
    player->x = 158;
    player->y = 37;
    player->xSpeed = 0;
    player->ySpeed = 0;
  }
  if((fabs(player->x - 160) < 0.2) && (fabs(player->y - 37) < 0.2)) {
    player->x = 142;
    player->y = 45;
    player->xSpeed = 0;
    player->ySpeed = 0;
  }
  if((fabs(player->x - 111) < 0.2) && (fabs(player->y - 31) < 0.2)) {
    player->x = 99;
    player->y = 13;
    player->xSpeed = 0;
    player->ySpeed = 0;
  }
  if((fabs(player->x - 97) < 0.2) && (fabs(player->y - 13) < 0.2)) {
    player->x = 113;
    player->y = 31;
    player->xSpeed = 0;
    player->ySpeed = 0;
  }
}

void checkEnd() {
  if(fabs(player->x - 115) < 0.8 && fabs(player->y - 13) < 0.8) {
    int * a = NULL;
    *a = 5;
  }
}

int checkCollisionX(){
  checkEnd();
    int case_right = ceilf(player->x + 2/16);
    int case_left = floorf(player->x);
    int case_bot = floorf(player->y - 2.6) + 2;
    int case_top = case_bot - 1;


    if (case_right >= 0 && case_right < MAP_W && case_top >= 0 && case_top < MAP_H && case_bot >= 0 && case_bot < MAP_H){
        if(map[case_top][case_right]|| map[case_bot][case_right] ){
          if(map[case_top][case_right] == 4 || map[case_bot][case_right] == 4) {
            player->xSpeed = player->xSpeed;
          }
          else {
            player->xSpeed = -0.05;
          }
          return 2;
        }
        if (map[case_bot][case_left]|| map[case_top][case_left]){
          if(map[case_bot][case_left] == 4 || map[case_top][case_left] == 4) {
            player->xSpeed = player->xSpeed;
          }
          else{
            player->xSpeed = 0.05;
          }
            return 1;
        }
    }
    return 0;
}

int playerMoveX(){
  checkTP();
  //printf(" checkCollisionX : %d\n", checkCollisionX());
  switch (checkCollisionX()) {
    case 0: // no collisions
      if (fabs(player->xSpeed) < PLAYER_MAX_SPEED_X){
        player->xSpeed += MOVEMENT_SPEED * (Keys[1] - Keys[3]);
      }
      int signe = 1;

      player->xSpeed *= 0.8;

      break;

    case 1: // left side collided
      player->xSpeed +=MOVEMENT_SPEED * Keys[1];
      break;

    case 2: // right side collided
      player->xSpeed +=MOVEMENT_SPEED * Keys[3];
      break;
  }
    player->x += player->xSpeed;
}

void gestPhysique(){
  //printf("player pos: %f, %f\n", player->x, player->y);
  playerMoveX();
  PlayerMoveY();
}


void updatePlayerState(player_t * player) {
  int i = player->y / TILE_SIZE + 1;
  int j = player->x / TILE_SIZE + 1;
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
  int i = player->y / TILE_SIZE + 1;
  int j = player->x / TILE_SIZE + 1;
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
