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
    mobsList[i] = initMob(25, 10);
  }
}

int MobcheckCollisionX(mob_t * mob) {
    int case_right = ceilf(mob->x + 2/16);
    int case_left = floorf(mob->x);
    int case_bot = floorf(mob->y - 2.6) + 2;
    int case_top = case_bot - 1;



    if (case_right >= 0 && case_right < MAP_W && case_top >= 0 && case_top < MAP_H && case_bot >= 0 && case_bot < MAP_H){
        if(map[case_top][case_right] == 1 || map[case_bot][case_right] == 1){
            mob->xSpeed = 0;
            return 2;
        }
        if(map[case_top][case_right] == 2 || map[case_bot][case_right] == 2) {
            if (mob->isCharging) {
                if (map[case_top][case_right]){
                    map[case_top][case_right] = 0;
                    printf("boom");
                }
                else if (map[case_bot][case_right]){
                    map[case_bot][case_right] = 0;
                    printf("boom");
                }
            }
            else {
                return 0;
            }
            return 1;
        }
        if (map[case_bot][case_left] == 1 || map[case_top][case_left] == 1){
            mob->xSpeed = 0;
            return 0;
        }
        if(map[case_top][case_left] == 2 || map[case_bot][case_left] == 2) {
            if (mob->isCharging) {
                if (map[case_top][case_left]){
                    map[case_top][case_left] = 0;
                    printf("boom");
                }
                else if (map[case_bot][case_left]){
                    map[case_bot][case_left] = 0;
                    printf("boom");
                }
            }
            else {
                mob->xSpeed = 0;
            }
            return 1;
        }
    }
    return 1;
}

void moveMobs(player_t * player) {
    for (int i = 0; i < nbMobs; i++){
        mob_t * curMob = mobsList[i];
        printf("mob pos: %f %f\n", curMob->x, curMob->y);
        int coeff = MobcheckCollisionX(curMob);
        if ((player->x - curMob->x) < 0) {
            curMob->direction = -1;
        }
        else {
            curMob->direction = 1;
        }
        if(curMob->isAttacking) {
            if(curMob->isCharging) {
                curMob->xSpeed += 0.008 * curMob->direction * coeff;
            }
            else {
                curMob->xSpeed += 0.0002 * curMob->direction * coeff;
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