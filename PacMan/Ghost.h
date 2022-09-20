// ---------------------------------------------------------------------------------
// PACAMAN
// INIMIGO DO PLAYER
// ---------------------------------------------------------------------------------


#ifndef PACMAN_GHOST_H_
#define PACMAN_GHOST_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "Player.h"                     // jogador do PacMan

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados poss�veis para os inimigos;
enum ENEMYTYPE  { BLUE, ORANGE, PINK, RED };

class Ghost : public Object
{
private:
    Sprite* fleeL = nullptr;            // sprite de fuga do inimigo
    Sprite* fleeR = nullptr;            // sprite de fuga do inimigo
    Sprite* fleeU = nullptr;            // sprite de fuga do inimigo
    Sprite* fleeD = nullptr;            // sprite de fuga do inimigo

    Sprite * spriteL = nullptr;         // sprite do inimigo
    Sprite* spriteR = nullptr;          // sprite do inimigo
    Sprite* spriteU = nullptr;          // sprite do inimigo
    Sprite* spriteD = nullptr;          // sprite do inimigo
    Player * player = nullptr;          // ponteiro para jogador
    float distX = 0;                    // dist�ncia do inimigo em rela��o ao jogador pelo eixo X
    float distY = 0;                    // dist�ncia do inimigo em rela��o ao jogador pelo eixo Y

public:
    float stateTime = 0;                // cron�metro para sa�da do fantasma do covil
    bool gameStart = false;             // indica se o jogo j� come�ou
    float velX = 0;                     // velocidade horizontal
    float velY = 0;                     // velocidade vertical

    float origemX = 0;
    float origemY = 0;
    float pauseTime = 0;

    uint state = PURSUE;                // estado de movimentos do inimigo em rela��o ao jogador
    uint currentMove = STOPED;          // movimento atual do inimigo
    uint nextMove = STOPED;             // pr�ximo movimento do inimigo

    Ghost(Player* p, float X, float Y, float time = 0, uint enemy = BLUE);   // construtor
    ~Ghost();                                                                 // destrutor

    void Stop();                        // p�ra jogador
    void Up();                          // muda dire��o para cima
    void Down();                        // muda dire��o para baixo
    void Left();                        // muda dire��o para esquerda
    void Right();                       // muda dire��o para direita

    void OnCollision(Object* obj);		// resolu��o da colis�o
    void PivotCollision(Object* obj);	// resolve colis�o com piv�
    void GhostCollision(Object* obj);	// Colisao com ghost

    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif