#include "raylib.h"

const int screenWidth = 1200;
const int screenHeight = 800;


typedef struct {
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    Texture2D textura;
    Texture2D textura_left;
    Texture2D textura_idle;
    Texture2D textura_jump;
    Texture2D textura_background;
    Rectangle sourceRec;
    Rectangle sourceRec_idle;
    Rectangle sourceRec_jump;
    Rectangle sourceRec_left;
    int frameAtual;
    int altura;
    int largura;
    float scrollingBack;
}PERSONAGEM;

typedef struct {
    Vector2 pos_obs;
    Texture2D textura_obs;
    int altura_obs;
    int largura_obs;
    Vector2 pos_obs1;
    Texture2D textura_obs1;
    int altura_obs1;
    int largura_obs1;
    Vector2 pos_obs2;
    Texture2D textura_obs2;
    int altura_obs2;
    int largura_obs2;
    Vector2 pos_obs_arvore;
    Texture2D textura_obs_arvore;
    int altura_obs_arvore;
    int largura_obs_arvore;
}OBSTACULO;

typedef struct {
    Vector2 pos_bola;
    Texture2D textura_bola;
    int altura_bola;
    int largura_bola;
}BOLA;

typedef struct
{
    Vector2 pos_vida;
    Texture2D textura_vida4;
    Texture2D textura_vida3;
    Texture2D textura_vida2;
    Texture2D textura_vida1;
    Texture2D textura_vida0;
    int altura_vida;
    int largura_vida;
}VIDA;

void initVida(VIDA* vida){
    vida->pos_vida.x = 0;
    vida->pos_vida.y = 20;
    vida->altura_vida;
    vida->largura_vida;
    vida->textura_vida4 = LoadTexture("./vida/hearts4.png");
    vida->textura_vida3 = LoadTexture("./vida/hearts3.png");
    vida->textura_vida2 = LoadTexture("./vida/hearts2.png");
    vida->textura_vida1 = LoadTexture("./vida/hearts1.png");
    vida->textura_vida0 = LoadTexture("./vida/hearts0.png");

}

void initBola (BOLA* bola) {
    bola->pos_bola.x = 650;
    bola->pos_bola.y = 670;
    bola->altura_bola;
    bola->largura_bola;
    bola->textura_bola = LoadTexture("./bola/bola.png");
}

void initObstaculo(OBSTACULO* obstaculo){
    obstaculo->pos_obs.x = 0;
    obstaculo->pos_obs.y = 690;
    obstaculo->altura_obs;
    obstaculo->largura_obs;
    obstaculo->textura_obs = LoadTexture("./obstaculos/plataforma1.png");
    obstaculo->pos_obs1.x = 480;
    obstaculo->pos_obs1.y = 690;
    obstaculo->altura_obs1;
    obstaculo->largura_obs1;
    obstaculo->textura_obs1 = LoadTexture("./obstaculos/plataforma1.png");
    obstaculo->pos_obs2.x = 800;
    obstaculo->pos_obs2.y = 690;
    obstaculo->altura_obs2;
    obstaculo->largura_obs2;
    obstaculo->textura_obs2 = LoadTexture("./obstaculos/plataforma1.png");
    obstaculo->pos_obs_arvore.x = 600;
    obstaculo->pos_obs_arvore.y = 420;
    obstaculo->altura_obs_arvore;
    obstaculo->largura_obs_arvore;
    obstaculo->textura_obs_arvore = LoadTexture("./obstaculos/arvore.png");

}

void initPersonagem(PERSONAGEM* personagem){
    personagem->pos.x = 0;
    personagem->pos.y = 650;
    personagem->vel.y = 0;
    personagem->vel.x = 0;
    personagem->acc.y = 0.2;
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
    personagem->textura_left = LoadTexture("./pink_monster/monstrograndeconceito1.png");
    Rectangle sr_left = {0.0f, 0.0f, personagem->textura_left.width/6, personagem->textura_left.height};
    personagem->sourceRec_left = sr_left;
    personagem->textura_background = LoadTexture("./background/level1/forest.png");
    personagem->scrollingBack = 0.0f;
    
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
        personagem->scrollingBack -= 0.6f;
        personagem->pos.x += 1;
        personagem->sourceRec.x = personagem->frameAtual*personagem->textura.width/6;
        
        if ( personagem->scrollingBack <= -(personagem->textura_background.width*2))  personagem->scrollingBack = 0;
        
    }
    if (IsKeyDown(KEY_LEFT))
    {
         personagem->scrollingBack += 0.6f;
        personagem->pos.x -= 1;
        personagem->sourceRec_left.x = personagem->frameAtual*personagem->textura_left.width/6;
        
        if ( personagem->scrollingBack <= -(personagem->textura_background.width*2))  personagem->scrollingBack = 0;
    }
    if (IsKeyPressed(KEY_UP) && personagem->pos.y == screenHeight - personagem->textura.height)
    {
        personagem->vel.y = -7;
        personagem->sourceRec_jump.x = personagem->frameAtual*personagem->textura_jump.width/8;
    }
    
    personagem->vel.x += personagem->acc.x;
    personagem->vel.y += personagem->acc.y;
        
    personagem->pos.x += personagem->vel.x;
    personagem->pos.y += personagem->vel.y;
    
    if(personagem->pos.x < 0) personagem->pos.x = 0;
    if(personagem->pos.x > 1150) personagem->pos.x = 1150;
    if(personagem->pos.y < 0) personagem->pos.y = 0;
    if(personagem->pos.y + personagem->textura.height > screenHeight) personagem->pos.y = screenHeight - personagem->textura.height;
    
    
    personagem->sourceRec_idle.x = personagem->frameAtual*personagem->textura_idle.width/4;
}

//Função que desenha o personagem.
void drawPersonagem(PERSONAGEM* personagem) {
    
    DrawTextureEx(personagem->textura_background, (Vector2){personagem->scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(personagem->textura_background, (Vector2){personagem->textura_background.width*2 + personagem->scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
    if(IsKeyDown(KEY_RIGHT))
    {
        DrawTextureRec(personagem->textura, personagem->sourceRec, personagem->pos, WHITE);
    }else if(IsKeyDown(KEY_LEFT))
    {
        DrawTextureRec(personagem->textura_left, personagem->sourceRec_left, personagem->pos, WHITE);
    }else if(IsKeyDown(KEY_UP))
    {
        DrawTextureRec(personagem->textura_jump, personagem->sourceRec_jump, personagem->pos, WHITE);
    }else
    {
        DrawTextureRec(personagem->textura_idle, personagem->sourceRec_idle, personagem->pos, WHITE);
    }
    
}

//Função que desenha os obstaculos durante o cenário.
void drawObstaculo(OBSTACULO* obstaculo) {
    DrawTextureV(obstaculo->textura_obs, obstaculo->pos_obs, WHITE);
    DrawTextureV(obstaculo->textura_obs1, obstaculo->pos_obs1, WHITE);
    DrawTextureV(obstaculo->textura_obs2, obstaculo->pos_obs2, WHITE);
    DrawTextureV(obstaculo->textura_obs_arvore, obstaculo->pos_obs_arvore, WHITE);
}

void drawVida(VIDA* vida) {
    DrawTextureV(vida->textura_vida4, vida->pos_vida, WHITE);
}

void drawBola(BOLA* bola) {
    DrawTextureV(bola->textura_bola, bola->pos_bola, WHITE);
}

int main(void){
    
    InitWindow(screenWidth, screenHeight, "Valley");
    SetTargetFPS(60);
    
    PERSONAGEM personagem;
    initPersonagem(&personagem);
    
    OBSTACULO obstaculo;
    initObstaculo(&obstaculo);
    
    VIDA vida;
    initVida(&vida);
    
    BOLA bola;
    initBola(&bola);
    
    while(!WindowShouldClose()) {
        
         
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        updatePersonagem(&personagem);
        drawPersonagem(&personagem);
        drawObstaculo(&obstaculo); 
        drawVida(&vida);
        drawBola(&bola);
        
        EndDrawing();
    }
    
    
    CloseWindow();
}