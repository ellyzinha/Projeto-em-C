#include "raylib.h"

const int screenWidth = 1200;
const int screenHeight = 800;

typedef struct {
    Vector2 pos;
    Texture2D textura;
    Rectangle sourceRec;
    int frameAtual;
}PERSONAGEM;

void initPersonagem(PERSONAGEM* personagem){
    personagem->pos.x = 0;
    personagem->pos.y = 650;
    personagem->textura = LoadTexture("./pink_monster/monstrograndeconceito.png");
    Rectangle sr = {0, 0, personagem->textura.width/6, personagem->textura.height};
    personagem->sourceRec = sr;
    personagem->frameAtual = 0;
}

void updatePersonagem(PERSONAGEM* personagem) {
    static int frameCounter = 0;
    frameCounter++;
    if(frameCounter > 10) {
        frameCounter = 0;
        personagem->frameAtual++;
        
        if(personagem->frameAtual > 5) {
            personagem->frameAtual = 0;
        }
    }
    
    personagem->sourceRec.x = personagem->frameAtual*personagem->textura.width/6;
}

void drawPersonagem(PERSONAGEM* personagem) {
    DrawTextureRec(personagem->textura, personagem->sourceRec, personagem->pos, WHITE);
}

int main(void){
    
    InitWindow(screenWidth, screenHeight, "Monitoria");
    SetTargetFPS(60);
    
    //Cenário
    Texture2D background = LoadTexture("C:/Users/elly/Pictures/forest.png");
    
    float scrollingBack = 0.0f;
    
    SetTargetFPS(60);
    
    PERSONAGEM personagem;
    initPersonagem(&personagem);
    
    while(!WindowShouldClose()) {
        
        scrollingBack -= 0.3f;
         
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
         
        DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        updatePersonagem(&personagem);
        drawPersonagem(&personagem);
        
        EndDrawing();
    }
    
    UnloadTexture(background);
    
    CloseWindow();
}
