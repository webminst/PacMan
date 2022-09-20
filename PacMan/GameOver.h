// ---------------------------------------------------------------------------------
// PACMAN
// TELA DE GAMEOVER
// ---------------------------------------------------------------------------------

#ifndef PACMAN_GAMEOVER_H_
#define PACMAN_GAMEOVER_H_

// ------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class GameOver : public Game
{
private:
    Sprite* backg = nullptr;        // pano de fundo
    Sprite * mensagem = nullptr;
    float posicaoMensagem = 620.00;
    bool ctrlKeyESC = false;        // controle do ESC

public:

    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

// -----------------------------------------------------------------------------

#endif