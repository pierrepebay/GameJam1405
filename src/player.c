#include "player.h"


void initPlayer(float x, float y)
{
  player_t* player = (player_t*)malloc(sizeof(player_t));
  if(!player)
  {
    printf("Player initalization failed.\n");
    exit(ALLOCATION_FAILURE);
  }
  else
  {
    player->x = x;
    player->y = y;

    player->xSpeed = 0;
    player->ySpeed = 0;

    player->health = 100;

    player->direction = 1;
    player->isGrounded = 0;
    player->isAttacking = 0;
    player->isFalling = 0;
    player->isTakingDmg = 0;
  }
}
