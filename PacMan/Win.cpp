// ---------------------------------------------------------------------------------
// PACMAN
// TELA DO VENCEDOR
// ---------------------------------------------------------------------------------

#include "Engine.h"
#include "Win.h"
#include "Home.h"

// ------------------------------------------------------------------------------
bool contWIN = true;
float sleepWIN = 10;
int moveWIN = 400;

void Win::Init()
{

    setGameState(WIN);                                   // indica em qual tela está
    backg = new Sprite("Resources/Winner.png");          // Sprite a definir
    mensagem = new Sprite("Resources/mensagem.png");
}

// ------------------------------------------------------------------------------

void Win::Finalize()
{
    delete backg;
    delete mensagem;
}

// ------------------------------------------------------------------------------

void Win::Update()
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

    // retorna para a tela HOME com a tecla ENTER
    if (window->KeyDown(VK_RETURN))
        Engine::Next<Home>();

    if (contWIN) {
        if (sleepWIN == 0) {
            if (moveWIN == 0) {
                contWIN = false;
            }
            else
            {
                posicaoMensagem -= 0.09f;
                moveWIN--;
            }
        }
        else
            sleepWIN--;
    }
    else {
        if (sleepWIN == 10)
        {
            if (moveWIN == 400) {
                contWIN = true;
            }
            else {
                posicaoMensagem += 0.09f;
                moveWIN++;
            }
        }
        else
            sleepWIN++;
    }

}

// ------------------------------------------------------------------------------

void Win::Draw()
{
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    mensagem->Draw(481.93, posicaoMensagem, Layer::BACK);
}

// ------------------------------------------------------------------------------