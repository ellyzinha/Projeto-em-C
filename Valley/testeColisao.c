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
    Vector2 pos_ini;
    Vector2 vel_ini;
    Vector2 acc_ini;
    Texture2D textura_ini;
    Rectangle sourceRec_ini;
    int altura_ini;
    int largura_ini;
}ENEMY;

typedef struct {
    Vector2 pos_obs;
    Texture2D textura_obs;
    int altura_obs;
    int largura_obs;
}OBSTACULO;

void initObstaculo(OBSTACULO* obstaculo){
    obstaculo->pos_obs.x = 400;
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

void initEnemy(ENEMY* enemy) {
    enemy->pos_ini.x = 600;
    enemy->pos_ini.y = 600;
    enemy->vel_ini.y = 0;
    enemy->vel_ini.x = 0;
    enemy->acc_ini.y = 0;
    enemy->acc_ini.x = 0;
    enemy->altura_ini;
    enemy->largura_ini;
    enemy->textura_ini = LoadTexture("./Personagens/noface.png");
    Rectangle sr_ini = {0.0f, 0.0f, enemy->textura_ini.width, enemy->textura_ini.height};
    enemy->sourceRec_ini = sr_ini;
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

//Função que desenha o inimigo
void drawEnemy(ENEMY* enemy) {
    DrawTextureV(enemy->textura_ini, enemy->pos_ini, WHITE);
}

//Função que verifica a colisão do personagem com o inimigo

Rectangle boxCollision = {0};
bool collision = false;
void checkColisao(PERSONAGEM* personagem, ENEMY* enemy){
    collision = CheckCollisionRecs(personagem->sourceRec, enemy->sourceRec_ini);
    
}

int main(void){
    
    InitWindow(screenWidth, screenHeight, "Valley");
    SetTargetFPS(60);
    
    //Textura do Cenário
    Texture2D background = LoadTexture("./background/level1/forest.png");
    
    float scrollingBack = 0.0f;
    
    SetTargetFPS(60);
    
    PERSONAGEM personagem;
    initPersonagem(&personagem);
    
    OBSTACULO obstaculo;
    initObstaculo(&obstaculo);
    
    ENEMY enemy;
    initEnemy(&enemy);
    
    while(!WindowShouldClose()) {
        
        scrollingBack -= 0.1f;
        
         
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
      
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
         
        DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
         DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
        
        updatePersonagem(&personagem);
        drawPersonagem(&personagem);
        drawObstaculo(&obstaculo);
        drawEnemy(&enemy);
        checkColisao(&personagem, &enemy);
        if(collision){
        DrawText("COLLISION!", GetScreenWidth()/2 - MeasureText("COLLISION!", 20)/2, screenHeight/2 - 10, 20, BLACK);
    }
        
        EndDrawing();
    }
    
    UnloadTexture(background);  // Unload background texture
     
    
    CloseWindow();
}