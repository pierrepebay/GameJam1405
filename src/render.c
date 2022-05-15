#include "render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* blockTexture;
SDL_Surface * blockSurface;

SDL_Surface * spriteSurface[25];
SDL_Texture * spriteTexture[25];

SDL_Surface * spriteRUNSurface[25];
SDL_Texture * spriteRUNTexture[25];

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
                offset_x = x + player->x - 7;
                offset_y = y + player->y - 5;
                
                if (offset_y >= 0 && offset_y < MAP_H && offset_x >= 0 && offset_x < MAP_W){
                    if(map[offset_y][offset_x]){
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
    rect.y = WindowHeight/2 - rect.h/2 + 20;
    // draw player
    if (fabs(player->xSpeed) < 0.0000001){
        SDL_RenderCopyEx(renderer, spriteTexture[(SDL_GetTicks()/50)%24], NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL * (1 - player->direction));
    }
    else{
        rect.w *= 1.536;
        rect.h *= 1.35;
        rect.y -= 60;
        SDL_RenderCopyEx(renderer, spriteRUNTexture[(SDL_GetTicks()/50)%23], NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL * (1 - player->direction));
    }
    
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

void DrawEnnemies(mob_t * Ennemy){
    int tick = SDL_GetTicks()/500;
    SDL_Rect rect;
    rect.w = player->w * TILE_SIZE * 4;
    rect.h = player->h * TILE_SIZE * 4;
    rect.x = WindowWidth/2 + (Ennemy->x - player->x) * MAP_W/2;
    rect.y = WindowHeight/2 - rect.h/2 + (Ennemy->y - player->y) * MAP_H * TILE_SIZE/4.8 + 20;
    // fill rectangle with red
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // draw filled rectangle
    SDL_RenderCopy(renderer, blockTexture, NULL, &rect);

}


void AffichageNormal(){
    DrawBackground();
    DrawMap();
    drawPlayer();
    DrawEnnemies(mobsList[0]);
    DrawEnnemies(mobsList[1]);
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


    blockSurface = IMG_Load("../assets/ground_1_true.png");
    blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
    SDL_FreeSurface(blockSurface);

    for (int i = 0; i < 10; i++)
    {
        char filename[50];
        sprintf(filename, "../assets/idle_1/hat/idle_hat000%d.png", i);
        spriteSurface[i] = IMG_Load(filename);
        spriteTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteSurface[i]);
        SDL_FreeSurface(spriteSurface[i]);
        sprintf(filename, "../assets/run/run_hat/run_hat000%d.png", i);
        spriteRUNSurface[i] = IMG_Load(filename);
        spriteRUNTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteRUNSurface[i]);
        SDL_FreeSurface(spriteRUNSurface[i]);
    }

    for (int i = 10; i < 24; i++)
    {
        char filename[50];
        sprintf(filename, "../assets/idle_1/hat/idle_hat00%d.png", i);
        spriteSurface[i] = IMG_Load(filename);
        spriteTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteSurface[i]);
        SDL_FreeSurface(spriteSurface[i]);
    }

    for (int i = 10; i < 23; i++)
    {
        char filename[50];
        sprintf(filename, "../assets/run/run_hat/run_hat00%d.png", i);
        spriteRUNSurface[i] = IMG_Load(filename);
        spriteRUNTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteRUNSurface[i]);
        SDL_FreeSurface(spriteRUNSurface[i]);
    }

    pthread_t threadGest;
    pthread_create(&threadGest, NULL, BoucleGestInput, NULL);

    while (isRunning){
        a = SDL_GetTicks();
        delta += a - b;
        if (delta > 1000/60.0){
            PlayerMoveY();
            moveMobs(player);
            updateMobsState(); 
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