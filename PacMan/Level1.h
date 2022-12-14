// ---------------------------------------------------------------------------------
// PACMAN
// NIVEL 1
// ---------------------------------------------------------------------------------


#ifndef PACMAN_LEVEl1_H_
#define PACMAN_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus?es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"
// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    Sprite * backg = nullptr;       // background
    Image * foodSprite = nullptr;   // comidas
    Image* specialSprite = nullptr; // comidas especiais

    Player* player = nullptr;

    bool viewBBox = false;          // habilita visualiza??o da bounding box
    bool ctrlKeyB = false;          // controle da tecla B

public:
    static Scene  * scene;          // gerenciador de cena

    void Init();                    // inicializa jogo
    void Update();                  // atualiza l?gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
    void nextLvl();
    void restartLvl();
    void home();
    
};

// -----------------------------------------------------------------------------

#endif