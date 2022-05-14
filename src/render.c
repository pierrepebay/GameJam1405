#include "render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* blockTexture;
SDL_Surface * blockSurface;

SDL_Surface * spriteSurface[25];
SDL_Texture * spriteTexture[25];

int WindowWidth = 1520;
int WindowHeight = 800;

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

void quitSdl(){
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    // Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
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
                offset_x = x + player->x;
                offset_y = y + player->y - 3;
                
                if (offset_y >= 0 && offset_y < MAP_H && offset_x >= 0 && offset_x < MAP_W){
                    if(map[offset_y][offset_x] == 1){
                        // create texture from blockSurface
                        SDL_RenderCopy(renderer, blockTexture, NULL, &rect);
                    }
                }
                rect.x = rect.x + rect.w;
            }
        rect.x = -side_padding * rect.w;
        rect.y = rect.y + rect.h;
        //rect.y = 0;// top_padding * rect.h;
    }
}

void drawPlayer(){
    SDL_Rect rect;
    rect.w = player->w * TILE_SIZE * 4;
    rect.h = player->h * TILE_SIZE * 4;
    // player is centered on screen
    rect.x = WindowWidth/2 - rect.w/2;
    rect.y = WindowHeight/2 - rect.h/2;
    // draw player


    SDL_RenderCopy(renderer, spriteTexture[(SDL_GetTicks()/50)%24], NULL, &rect);
    
}

void DrawBackground(){
    SDL_Rect rect;
    rect.w = WindowWidth;
    rect.h = WindowHeight;
    rect.x = 0;
    rect.y = 0;
    // fill rectangle with red
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // draw filled rectangle
    SDL_RenderFillRect(renderer, &rect);
}


void AffichageNormal(){
    DrawBackground();
    DrawMap();
    drawPlayer();
    SDL_RenderPresent(renderer);
}


void * BoucleGestInput(void * arg){
    while (isRunning)
    {
        gestInput();
        playerMoveX();
    }
    return NULL;
}


void MainDrawLoop(){
    createWindow();
    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;


    blockSurface = IMG_Load("../ground_1_true.png");
    blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
    SDL_FreeSurface(blockSurface);

    for (int i = 0; i < 10; i++)
    {
        char filename[50];
        sprintf(filename, "../idle_1/hat/idle_hat000%d.png", i);
        spriteSurface[i] = IMG_Load(filename);
        spriteTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteSurface[i]);
        SDL_FreeSurface(spriteSurface[i]);
    }

    for (int i = 10; i < 24; i++)
    {
        char filename[50];
        sprintf(filename, "../idle_1/hat/idle_hat00%d.png", i);
        spriteSurface[i] = IMG_Load(filename);
        spriteTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteSurface[i]);
        SDL_FreeSurface(spriteSurface[i]);
    }

    pthread_t threadGest;
    pthread_create(&threadGest, NULL, BoucleGestInput, NULL);

    while (isRunning){
        a = SDL_GetTicks();
        delta += a - b;
        if (delta > 1000/60.0){
            PlayerMoveY();
            switch (GameOption)
            {
            case 0:
                // Draw the map
                AffichageNormal();
                break;
            
            default:
                break;
            }
            delta = 0;
        }
        b = SDL_GetTicks();
    }
    quitSdl();
}



