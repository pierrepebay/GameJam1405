#include "render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void createWindow(){
    SDL_DisplayMode ScreenDisplay;
    SDL_GetCurrentDisplayMode(0, &ScreenDisplay);
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    // Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenDisplay.w, ScreenDisplay.h, SDL_WINDOW_SHOWN);
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


void MainDrawLoop(){
    createWindow();
    printf("Hello World!\n");
}



