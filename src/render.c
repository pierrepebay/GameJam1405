#include "render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int WindowWidth = 1920;
int WindowHeight = 1080;

void createWindow(){
    SDL_DisplayMode ScreenDisplay;
    SDL_GetCurrentDisplayMode(0, &ScreenDisplay);
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }
    // Initialize renderer color
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // Get window size

    // Initialise Roboto font
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("Roboto-Black.ttf", 16);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(1);
    }
}


void DrawMap(){
    SDL_Rect rect;
    float side_padding = (player->x - (int)player->x);
    float top_padding = 1 - (player->y  -(int)player->y);
    rect.w = (WindowWidth/NB_TO_SHOW_X);
    rect.h = (WindowHeight/NB_TO_SHOW_Y);
    rect.x =  -side_padding * rect.w;
    rect.y = (top_padding- 1) * rect.h;
    int offset_y;
    int offset_x;
    for(int y = 0; y<NB_TO_SHOW_Y+2; y++){
            for (int x = 0; x < NB_TO_SHOW_X + 1; x++)
            {
                offset_x = x + player->x - 9;
                offset_y = y + player->y - 3;
                printf("offset_x = %d, offset_y = %d\n", offset_x, offset_y);
                printf("%d %d\n", rect.x, rect.y);
                
                if (offset_y >= 0 && offset_y < MAP_H && offset_x >= 0 && offset_x < MAP_W){
                    if(map[offset_y][offset_x] == 1){
                        // set draw color to white
                        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                        // draw filled rectangle
                        SDL_RenderFillRect(renderer, &rect);
                    }
                }
                rect.x = rect.x + rect.w;
            }
        rect.x = -side_padding * rect.w;
        rect.y = rect.y + rect.h;
        //rect.y = 0;// top_padding * rect.h;
    }
    SDL_RenderPresent(renderer);
}


void AffichageNormal(){
    DrawMap();
}


void MainDrawLoop(){
    createWindow();
    while (isRunning){
        switch (GameOption)
        {
        case 0:
            // Draw the map
            AffichageNormal();
            break;
        
        default:
            break;
        }
    }
}



