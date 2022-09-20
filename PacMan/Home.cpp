// ---------------------------------------------------------------------------------
// PACMAN
// TELA INICIAL
// ---------------------------------------------------------------------------------


#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"

// ------------------------------------------------------------------------------
bool cont = true;
float sleep = 20;
int move = 400;

void Home::Init()
{

    setGameState(HOME);                                   // indica em qual tela 
    backg = new Sprite("Resources/Home.png");             // Sprite da tela
    mensagem = new Sprite("Resources/mensagem.png");
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
    delete mensagem;
}

// ------------------------------------------------------------------------------

void Home::Update()
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

    // passa ao primeiro nível 1 com ENTER
    if (ctrlKeyENTER && window->KeyDown(VK_RETURN))
    {
        ctrlKeyENTER = false;
        Engine::Next<Level1>();
    }
    else if (window->KeyUp(VK_RETURN))
    {
        ctrlKeyENTER = true;
    }

    // passa ao primeiro nível 2 com NUMPAD 1
    if (window->KeyDown(VK_NUMPAD1))
        Engine::Next<Level2>();

    if (cont) {
        if (sleep == 0) {
            if (move == 0) {
                cont = false;
            }
            else
            {
                posicaoMensagem -= 0.09f;
                move--;
            }
        }
        else
            sleep--;
    }
    else {
        if (sleep == 20)
        {
            if (move == 400) {
                cont = true;
            }
            else {
                posicaoMensagem += 0.09f;
                move++;
            }
        }
        else
            sleep++;
    }

}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    mensagem->Draw(481.93, posicaoMensagem, Layer::BACK);
}

// ------------------------------------------------------------------------------