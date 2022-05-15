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
    int case_left = floorf(mob->x - 2/16); 
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
                }
                else if (map[case_bot][case_right]){
                    map[case_bot][case_right] = 0;
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
                }
                else if (map[case_bot][case_left]){
                    map[case_bot][case_left] = 0;
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

int MobcheckCollisionY(mob_t * mob) {

    int case_x = floorf(mob->x + mob->w); ;

    int case_y = floorf(mob->y + mob->ySpeed );

        if (map[case_y][case_x]){

            mob->ySpeed = 0;
            mob->isGrounded = 1;
            return 1;
        }
        else {
            mob->isGrounded = 0;
        }

    return 0;
}

int MobcheckCollisionY2(mob_t * mob) {

    int case_x = floorf(mob->x + mob->w/4);

    int case_y = floorf(mob->y + mob->ySpeed );

    int case_y2 = case_y - 1.5;

        if (map[case_y2][case_x]) {
          mob->ySpeed = 0;
          mob->isGrounded = 0;
          return 1;
        }

    return 0;
}

void moveMobY(mob_t * mob) {

    if (!MobcheckCollisionY(mob)){
      MobcheckCollisionY2(mob);
      if(!mob->isGrounded) {
        mob->ySpeed += GRAVITY;
      }
    }
   mob->y += mob->ySpeed;
}

void moveMobs(player_t * player) {
    for (int i = 0; i < nbMobs; i++){
        mob_t * curMob = mobsList[i];
        moveMobY(curMob);
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
        if(fabs((curMob->x - player->x) ) < 8) {
            if(fabs((curMob->x - player->x) ) < 4) 
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