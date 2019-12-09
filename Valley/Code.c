#include "raylib.h"

const int screenWidth = 1200;
const int screenHeight = 800;


typedef struct {
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    Texture2D textura;
    Texture2D textura_idle;
    Texture2D textura_jump;
    Rectangle sourceRec;
    Rectangle sourceRec_idle;
    Rectangle sourceRec_jump;
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
    obstaculo->pos_obs.y = 600;
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
    personagem->textura_idle = LoadTexture("./pink_monster/pink_monster.png");
    Rectangle sr_idle = {0.0f, 0.0f, personagem->textura_idle.width/4, personagem->textura_idle.height};
    personagem->sourceRec_idle = sr_idle;
    personagem->textura = LoadTexture("./pink_monster/monstrograndeconceito.png");
    Rectangle sr = {0.0f, 0.0f, personagem->textura.width/6, personagem->textura.height};
    personagem->sourceRec = sr;
    personagem->textura_jump = LoadTexture("./pink_monster/pink_monster_jump.png");
    Rectangle sr_jump = {0.0f, 0.0f, personagem->textura_jump.width/8, personagem->textura_jump.height};
    personagem->sourceRec_jump = sr_jump;
    
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
        personagem->sourceRec.x = personagem->frameAtual*personagem->textura.width/6;
        
    }
    if (IsKeyDown(KEY_LEFT))
    {
        personagem->pos.x -= 2;
        personagem->sourceRec.x = personagem->frameAtual*personagem->textura.width/6;
    }
    if (IsKeyDown(KEY_UP) && (personagem->pos.y > 500) )
    {
        personagem->vel.y = -5;
        personagem->sourceRec_jump.x = personagem->frameAtual*personagem->textura_jump.width/8;
    }
    
    personagem->vel.x += personagem->acc.x;
    personagem->vel.y += personagem->acc.y;
        
    personagem->pos.x += personagem->vel.x;
    personagem->pos.y += personagem->vel.y;
    
    if(personagem->pos.x < 0) personagem->pos.x = 0;
    if(personagem->pos.x > 1150) personagem->pos.x = 1150;
    if(personagem->pos.y < 0) personagem->pos.y = 0;
    if(personagem->pos.y  > 650) personagem->pos.y = 650;
    
    
    personagem->sourceRec_idle.x = personagem->frameAtual*personagem->textura_idle.width/4;
}

//Função que desenha o personagem.
void drawPersonagem(PERSONAGEM* personagem) {
    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)){
        DrawTextureRec(personagem->textura, personagem->sourceRec, personagem->pos, WHITE);
    }else if(IsKeyDown(KEY_UP)){
        DrawTextureRec(personagem->textura_jump, personagem->sourceRec_jump, personagem->pos, WHITE);
    }else{
        DrawTextureRec(personagem->textura_idle, personagem->sourceRec_idle, personagem->pos, WHITE);
    }
    
}

//Função que desenha os obstaculos durante o cenário.
void drawObstaculo(OBSTACULO* obstaculo) {
    DrawTextureV(obstaculo->textura_obs, obstaculo->pos_obs, WHITE);
}

int main(void){
    
    InitWindow(screenWidth, screenHeight, "Valley");
    SetTargetFPS(60);
    
    //Cenário
    Texture2D background = LoadTexture("./background/level1/forest.png");
    
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