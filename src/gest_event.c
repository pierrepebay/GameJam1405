#include "gest_event.h"

int Keys[10];

void * gestInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_z:
                    Keys[0] = 1;
                    printf("pressed z\n");
                    break;

                case SDLK_d:
                    printf("player pos: %f, %f\n", player->x, player->y);
                    Keys[1] = 1;
                    break;

                case SDLK_s:
                    Keys[2] = 1;
                    break;

                case SDLK_q:
                    Keys[3] = 1;
                    break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                case SDLK_z:
                    Keys[0] = 0;
                    break;

                case SDLK_d:
                    Keys[1] = 0;
                    break;

                case SDLK_s:
                    Keys[2] = 0;
                    break;

                case SDLK_q:
                    Keys[3] = 0;
                    break;
            }
            break;

        case SDL_QUIT:
            isRunning = 0;
            break;

        default:
            break;
        }
    }
    return NULL;
}
