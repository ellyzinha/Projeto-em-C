#include "raylib.h"

const int screenWidth = 1200;
const int screenHeight = 800;

typedef struct {
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    Texture2D textura;
    Rectangle sourceRec;
    int frameAtual;
    int altura;
    int largura;
}PERSONAGEM;

typedef struct {
    Vector2 pos_obs;
    Texture2D textura_obs;
    int altura_obs;
    int largura_obs;
}OBSTACULO;

void initObstaculo(OBSTACULO* obstaculo){
    obstaculo->pos_obs.x = 600;
    obstaculo->pos_obs.y = 400;
    obstaculo->altura_obs;
    obstaculo->largura_obs;
    obstaculo->textura_obs = LoadTexture("./obstaculos/brown_on.png");

}

void initPersonagem(PERSONAGEM* personagem){
    personagem->pos.x = 0;
    personagem->pos.y = 650;
    personagem->vel.y = 0;
    personagem->vel.x = 0;
    personagem->acc.y = 0.5;
    personagem->acc.x = 0;
    personagem->altura;
    personagem->largura;
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
    if (IsKeyDown(KEY_RIGHT))
    {
        personagem->pos.x += 2;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        personagem->pos.x -= 2;
    }
    if (IsKeyDown(KEY_UP))
    {
        personagem->vel.y = -5;
    }
    
    personagem->vel.x += personagem->acc.x;
    personagem->vel.y += personagem->acc.y;
        
    personagem->pos.x += personagem->vel.x;
    personagem->pos.y += personagem->vel.y;
    
    if(personagem->pos.x < 0) personagem->pos.x = 0;
    if(personagem->pos.x > 1150) personagem->pos.x = 1150;
    if(personagem->pos.y < 0) personagem->pos.y = 0;
    if(personagem->pos.y  > 650) personagem->pos.y = 650;
    
    
    personagem->sourceRec.x = personagem->frameAtual*personagem->textura.width/6;
}

//Função que desenha o personagem.
void drawPersonagem(PERSONAGEM* personagem) {
    DrawTextureRec(personagem->textura, personagem->sourceRec, personagem->pos, WHITE);
}

//Função que desenha os obstaculos durante o cenário.
void drawObstaculo(OBSTACULO* obstaculo) {
    DrawTextureV(obstaculo->textura_obs, obstaculo->pos_obs, WHITE);
}

int main(void){
    
    InitWindow(screenWidth, screenHeight, "Valley");
    SetTargetFPS(60);
    
    //Cenário
    Texture2D background = LoadTexture("./background/forest.png");
    
    float scrollingBack = 0.0f;
    
    SetTargetFPS(60);
    
    PERSONAGEM personagem;
    initPersonagem(&personagem);
    
    OBSTACULO obstaculo;
    initObstaculo(&obstaculo);
    
    while(!WindowShouldClose()) {
        
        scrollingBack -= 0.3f;
         
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
         
        DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        updatePersonagem(&personagem);
        drawPersonagem(&personagem);
        drawObstaculo(&obstaculo);
        
        EndDrawing();
    }
    
    UnloadTexture(background);
    
    CloseWindow();
}