#include "mob.h"

mob_t * mob;
mob_t * mobsList[MAX_MOB_N];

int nbMobs = 10;

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

void initMobs() {
  for(int k = 0; k < MAX_MOB_N; k++) {
    mobsList[k] = NULL;
  }
  for(int i = 0; i < nbMobs; i++) {
    mobsList[i] = initMob(20, 10);
  }
}

void moveMobs(player_t * player) {
    for (int i = 0; i < nbMobs; i++){
        mob_t * curMob = mobsList[i];
        if ((player->x - curMob->x) < 0) {
            curMob->direction = -1;
        }
        else {
            curMob->direction = 1;
        }
        if(curMob->isAttacking) {
            if(curMob->isCharging) {
                curMob->xSpeed += 0.008 * curMob->direction;
            }
            else {
                curMob->xSpeed += 0.0002 * curMob->direction;
            }
        }
        curMob->x += curMob->xSpeed;
    }
}

void updateMobsState() {
    for (int i = 0; i < nbMobs; i++){
        mob_t * curMob = mobsList[i];
        if(fabs((curMob->x - player->x) ) < 4) {
            if(fabs((curMob->x - player->x) ) < 3) 
            {
                curMob->isCharging = 1;
            }
            curMob->isAttacking = 1;
        }
        
        else {
            curMob->isAttacking = 0;
            curMob->xSpeed = 0;
        }  
    }          
}
