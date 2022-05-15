#include "render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* blockTexture;
SDL_Surface * blockSurface;

SDL_Texture* bgTexture;
SDL_Surface * bgSurface;

SDL_Texture* trophyTexture;
SDL_Surface * trophySurface;

SDL_Texture* TPTexture;
SDL_Surface * TPSurface;

SDL_Texture* semiblockTexture;
SDL_Surface * semiblockSurface;

SDL_Surface * spriteSurface[25];
SDL_Texture * spriteTexture[25];

SDL_Surface * spriteRUNSurface[25];
SDL_Texture * spriteRUNTexture[25];

SDL_Surface * spriteJUMPSurface[50];
SDL_Texture * spriteJUMPTexture[50];

SDL_Surface * spriteJUMPGOLDENSurface[25];
SDL_Texture * spriteJUMPGOLDENTexture[25];

SDL_Surface * spriteFALLSurface[25];
SDL_Texture * spriteFALLTexture[25];

SDL_Surface * spriteFALLGOLDENSurface[25];
SDL_Texture * spriteFALLGOLDENTexture[25];

SDL_Surface * monsterIDLESurface[25];
SDL_Texture * monsterIDLETexture[25];

SDL_Surface * monsterRUNSurface[25];
SDL_Texture * monsterRUNTexture[25];


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
                        if (map[offset_y][offset_x] == 1){
                          SDL_RenderCopy(renderer, blockTexture, NULL, &rect);
                        }
                        if (map[offset_y][offset_x] == 2){
                          SDL_RenderCopy(renderer, semiblockTexture, NULL, &rect);
                        }
                        if (map[offset_y][offset_x] == 4){
                          SDL_RenderCopy(renderer, TPTexture, NULL, &rect);
                        }
                        if (map[offset_y][offset_x] == 8){
                          SDL_RenderCopy(renderer, trophyTexture, NULL, &rect);
                        }
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
    if (player->isGrounded){
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
    else {
      if (player->ySpeed > 0){
          rect.w *= 1.53;
          rect.h *= 1.38;
          rect.y -= 60;
        SDL_RenderCopyEx(renderer, spriteJUMPTexture[12 + (SDL_GetTicks()/50)%14], NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL * (1 - player->direction));
      }else {
          rect.w *= 1.53;
          rect.h *= 1.38;
          rect.y -= 60;
        SDL_RenderCopyEx(renderer, spriteJUMPTexture[(SDL_GetTicks()/50)%20], NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL * (1 - player->direction));
      }

    }

}

void DrawBackground(){
    SDL_Rect rect;
    rect.w = WindowWidth;
    rect.h = WindowHeight;
    rect.x = 0;
    rect.y = 0;
    // fill rectangle with red
    //SDL_SetRenderDrawColor(renderer, 166, 162, 152, 0xFF);
    // draw filled rectangle
    SDL_RenderCopyEx(renderer, bgTexture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void DrawEnnemies(mob_t * Ennemy){
    int tick = SDL_GetTicks()/500;
    SDL_Rect rect;
    rect.w = player->w * TILE_SIZE * 8;
    rect.h = player->h * TILE_SIZE * 4;
    rect.x = WindowWidth/2 + (Ennemy->x - player->x) * MAP_W/2;
    rect.y = WindowHeight/2 - rect.h/2 + (Ennemy->y - player->y) * MAP_H * 1.2 + 20;
    // fill rectangle with red
    // draw filled rectangle
    int direction = 1;
    if (Ennemy->x < player->x){
        direction = -1;
    }
    SDL_RenderCopyEx(renderer, monsterRUNTexture[(SDL_GetTicks()/50)%23], NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL * (player->direction));

}


void AffichageNormal(){
    DrawBackground();
    DrawMap();
    drawPlayer();
    for (int i = 0; i < nbMobs; i++){
        DrawEnnemies(mobsList[i]);
    }
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


    blockSurface = IMG_Load("../assets/ground_2.png");
    blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);

    trophySurface = IMG_Load("../assets/trophy.png");
    trophyTexture = SDL_CreateTextureFromSurface(renderer, trophySurface);

    bgSurface = IMG_Load("../assets/background.png");
    bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);

    semiblockSurface = IMG_Load("../ground_breackable.png");
    semiblockTexture = SDL_CreateTextureFromSurface(renderer, semiblockSurface);

    TPSurface = IMG_Load("../assets/portal.png");
    TPTexture = SDL_CreateTextureFromSurface(renderer, TPSurface);

    SDL_FreeSurface(blockSurface);
    SDL_FreeSurface(TPSurface);
    SDL_FreeSurface(semiblockSurface);

    for (int i = 0; i < 10; i++)
    {
        char filename[100];
        sprintf(filename, "../assets/idle_1/hat/idle_hat000%d.png", i);
        spriteSurface[i] = IMG_Load(filename);
        spriteTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteSurface[i]);
        SDL_FreeSurface(spriteSurface[i]);

        sprintf(filename, "../assets/monster/idle/monster_idle000%d.png", i);
        monsterIDLESurface[i] = IMG_Load(filename);
        monsterIDLETexture[i] = SDL_CreateTextureFromSurface(renderer, monsterIDLESurface[i]);
        SDL_FreeSurface(monsterIDLESurface[i]);


        sprintf(filename, "../assets/monster/run/monster_run000%d.png", i);
        monsterRUNSurface[i] = IMG_Load(filename);
        monsterRUNTexture[i] = SDL_CreateTextureFromSurface(renderer, monsterRUNSurface[i]);
        SDL_FreeSurface(monsterRUNSurface[i]);


        sprintf(filename, "../assets/run/run_hat/run_hat000%d.png", i);
        spriteRUNSurface[i] = IMG_Load(filename);
        spriteRUNTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteRUNSurface[i]);
        SDL_FreeSurface(spriteRUNSurface[i]);

        sprintf(filename, "../assets/jump/jump_hat/jump_hat000%d.png", i);
        spriteJUMPSurface[i] = IMG_Load(filename);
        spriteJUMPTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteJUMPSurface[i]);
        SDL_FreeSurface(spriteJUMPSurface[i]);
        sprintf(filename, "../assets/jump/jump_golden_hat/jump_golden_hat000%d.png", i);
        spriteJUMPGOLDENSurface[i] = IMG_Load(filename);
        spriteJUMPGOLDENTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteJUMPGOLDENSurface[i]);
        SDL_FreeSurface(spriteJUMPGOLDENSurface[i]);

    }

    for(int i = 10; i < 20; i++) {
      char filename[100];
      sprintf(filename, "../assets/jump/jump_hat/jump_hat00%d.png", i);
      spriteJUMPSurface[i] = IMG_Load(filename);
      spriteJUMPTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteJUMPSurface[i]);
      SDL_FreeSurface(spriteJUMPSurface[i]);
      sprintf(filename, "../assets/jump/jump_golden_hat/jump_golden_hat00%d.png", i);
      spriteJUMPGOLDENSurface[i] = IMG_Load(filename);
      spriteJUMPGOLDENTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteJUMPGOLDENSurface[i]);
      SDL_FreeSurface(spriteJUMPGOLDENSurface[i]);
    }

    for(int i = 12; i < 26; i++) {
      char filename[100];
      sprintf(filename, "../assets/jump/fall_hat/fall_hat00%d.png", i);
      spriteJUMPSurface[i] = IMG_Load(filename);
      spriteJUMPTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteJUMPSurface[i]);
      SDL_FreeSurface(spriteJUMPSurface[i]);
      sprintf(filename, "../assets/jump/fall_golden_hat/fall_golden_hat00%d.png", i);
      spriteFALLGOLDENSurface[i] = IMG_Load(filename);
      spriteFALLGOLDENTexture[i] = SDL_CreateTextureFromSurface(renderer, spriteFALLGOLDENSurface[i]);
      SDL_FreeSurface(spriteFALLGOLDENSurface[i]);
    }

    for (int i = 10; i < 23; i++)
    {
        char filename[50];
        sprintf(filename, "../assets/run/run_hat/run_hat00%d.png", i);
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

        sprintf(filename, "../assets/monster/idle/monster_idle00%d.png", i);
        monsterIDLESurface[i] = IMG_Load(filename);
        monsterIDLETexture[i] = SDL_CreateTextureFromSurface(renderer, monsterIDLESurface[i]);
        SDL_FreeSurface(monsterIDLESurface[i]);


        sprintf(filename, "../assets/monster/run/monster_run00%d.png", i);
        monsterRUNSurface[i] = IMG_Load(filename);
        monsterRUNTexture[i] = SDL_CreateTextureFromSurface(renderer, monsterRUNSurface[i]);
        SDL_FreeSurface(monsterRUNSurface[i]);
    }

    monsterRUNSurface[24] = IMG_Load("../assets/monster/run/monster_run0024.png");
    monsterRUNTexture[24] = SDL_CreateTextureFromSurface(renderer, monsterRUNSurface[24]);
    SDL_FreeSurface(monsterRUNSurface[24]);


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
