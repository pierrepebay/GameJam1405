#include "mob.h"

mob_t * mob;

mob_t * initMob(float x, float y) {
  mob_t * mob = (mob_t*)malloc(sizeof(mob_t));
  if(!mob) {
    printf("mob initalization failed.\n");
    exit(ALLOCATION_FAILURE);
  }
  else {
    mob->x = x;
    mob->y = y;

    mob->w = 1;
    mob->h = 2;

    mob->xSpeed = 0;
    mob->ySpeed = 0;

    mob->health = 100;

    mob->direction = 1;
    mob->isGrounded = 0;
    mob->isAttacking = 0;
    mob->isCharging = 0;
    mob->isFalling = 0;
    mob->isTakingDmg = 0;
  }
  return mob;
}

void initMobs(int n) {
  for(int k = 0; k < MAX_MOB_N; k++) {
    mobsList[k] = NULL;
  }
  for(int i = 0; i < n; i++) {
    mobsList[i] = initMob(rand() % MAP_W, rand() % MAP_H);
  }
}

void moveMobs(player_t * player) {
  int i = 0;
  mob_t * curMob;
  while(curMob != NULL) {
    curMob = mobsList[i];
    if(curMob->isAttacking) {
      if(curMob->isCharging) {
        curMob->xSpeed = 0.0002 * (player->x - curMob->x) / fabs(player->x - curMob->x);
      }
      else {
        curMob->xSpeed = 0.00002 * (player->x - curMob->x) / fabs(player->x - curMob->x);
      }
    }
    else {
      int r = rand() % 100; // Change mob movement 1 in 100 times
      if(r == 1) {
        switch (curMob->direction) {
          case 0:
            curMob->direction = 1;
            curMob->xSpeed = 0.00002;
            break;
          case 1:
            curMob->direction = 0;
            curMob->xSpeed = -0.00002;
            break;
        }
      }
    }
    i++;
  }
}

void updateMobsState() {
  int i = 0;
  mob_t * curMob;
  while(curMob != NULL) {
    curMob = mobsList[i];
    if(sqrt((curMob->x - player->x) * (curMob->x - player->x) + (curMob->y - player->y) * (curMob->y - player->y)) < 100) {
      if(sqrt((curMob->x - player->x) * (curMob->x - player->x) + (curMob->y - player->y) * (curMob->y - player->y)) < 30) {
        curMob->isCharging = 1;
      }
      curMob->isAttacking = 1;
    }
    else {
      curMob->isAttacking = 0;
    }
    i++;
  }
}
