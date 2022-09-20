// ---------------------------------------------------------------------------------
// PACMAN
// TELA INICIAL
// ---------------------------------------------------------------------------------


#ifndef PACMAN_HOME_H_
#define PACMAN_HOME_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Home : public Game
{
private:
    Sprite * backg = nullptr;       // pano de fundo
    Sprite * mensagem = nullptr;    // pano de fundo
    float posicaoMensagem = 364.58;
    bool ctrlKeyESC = false;        // controle do ESC
    bool ctrlKeyENTER = false;      // controle do ENTER

public:

    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

// -----------------------------------------------------------------------------

#endif