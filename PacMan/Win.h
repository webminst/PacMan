// ---------------------------------------------------------------------------------
// PACMAN
// TELA  DE WIN
// ---------------------------------------------------------------------------------

#ifndef PACMAN_WIN_H_
#define PACMAN_WIN_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Win : public Game
{
private:
    Sprite* backg = nullptr;        // pano de fundo
    Sprite* mensagem = nullptr;
    float posicaoMensagem = 620.00;
    bool ctrlKeyESC = false;        // controle do ESC

public:

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif
