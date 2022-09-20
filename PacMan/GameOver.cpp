// ---------------------------------------------------------------------------------
// PACMAN
// TELA DE GAMEOVER
// ---------------------------------------------------------------------------------

#include "Engine.h"
#include "GameOver.h"
#include "Home.h"

// ------------------------------------------------------------------------------
bool contr = true;
float sleepGO = 10;
int moveGO = 400;

void GameOver::Init()
{

    setGameState(GAMEOVER);                                   // indica em qual tela está
    backg = new Sprite("Resources/GameOver.png");             // Sprite
    mensagem = new Sprite("Resources/mensagem.png");
}

// ------------------------------------------------------------------------------

void GameOver::Finalize()
{
    delete backg;
    delete mensagem;
}

// ------------------------------------------------------------------------------

void GameOver::Update()
{
    // sai do jogo com a tecla ESC
    if (ctrlKeyESC && window->KeyDown(VK_ESCAPE))
    {
        ctrlKeyESC = false;
        window->Close();
    }
    else if (window->KeyUp(VK_ESCAPE))
    {
        ctrlKeyESC = true;
    }

    // passa ao primeiro nível com ENTER
    if (window->KeyDown(VK_RETURN))
        Engine::Next<Home>();

    if (contr) {
        if (sleepGO == 0) {
            if (moveGO == 0) {
                contr = false;
            }
            else
            {
                posicaoMensagem -= 0.09f;
                moveGO--;
            }
        }
        else
            sleepGO--;
    }
    else {
        if (sleepGO == 10)
        {
            if (moveGO == 400) {
                contr = true;
            }
            else {
                posicaoMensagem += 0.09f;
                moveGO++;
            }
        }
        else
            sleepGO++;
    }
}

// ------------------------------------------------------------------------------

void GameOver::Draw()
{
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    mensagem->Draw(481.93, posicaoMensagem, Layer::BACK);
}

// ------------------------------------------------------------------------------