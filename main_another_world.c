/*******************************************************************************************
*
*   raylib [textures] example - Background scrolling
*
*   This example has been created using raylib 2.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2019 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

typedef struct {
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    int largura;
    int altura;
}PLAYER;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Another World");
    
    PLAYER jogador;
    
    jogador.altura = 30;
    jogador.largura = 20;
    jogador.pos.x = 0;
    jogador.pos.y = jogador.altura;
    jogador.vel.x = 0;
    jogador.vel.y = 0;
    jogador.acc.x = 0;
    jogador.acc.y = 0.2;

    // NOTE: Be careful, background width must be equal or bigger than screen width
    // if not, texture should be draw more than two times for scrolling effect
    Texture2D background = LoadTexture("C:/Users/elly/Pictures/forest.png");
    Texture2D sprite = LoadTexture("C:/Users/elly/Pictures/scarfy2.png");



    float scrollingBack = 0.0f;


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
void DrawPlayer(PLAYER* jogador) {
        DrawRectangle(jogador->pos.x, jogador->pos.y, jogador->largura, jogador->altura, LIGHTGRAY);
    }
    
    void UpdatePlayer(PLAYER* jogador) {
        
        if(IsKeyDown(KEY_D)) jogador->pos.x += 7;
        if(IsKeyDown(KEY_A)) jogador->pos.x -= 7;
       
        if(IsKeyPressed(KEY_SPACE) && jogador->pos.y == screenHeight - jogador->altura) {
            jogador->vel.y = -8;
        }
        
        
        jogador->vel.x += jogador->acc.x;
        jogador->vel.y += jogador->acc.y;
        
        jogador->pos.x += jogador->vel.x;
        jogador->pos.y += jogador->vel.y;
        
        if(jogador->pos.x < 0) jogador->pos.x = 0;
        if(jogador->pos.x + jogador->largura > screenWidth) jogador->pos.x = screenWidth - jogador->largura;
        if(jogador->pos.y < 0) jogador->pos.y = 0;
        if(jogador->pos.y + jogador->altura > screenHeight) jogador->pos.y = screenHeight - jogador->altura;
    }
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 0.3f;
       

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
      
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw background image twice
            // NOTE: Texture is scaled twice its size
            DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
            UpdatePlayer(&jogador);
            DrawPlayer(&jogador);
            
            //Sprite Texture
            DrawTexture(sprite, 300, 300, WHITE);

       
            
            
           

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(background);  // Unload background texture
    UnloadTexture(sprite);
   

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}