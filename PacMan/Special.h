// ---------------------------------------------------------------------------------
// PACMAN
// COMIDAS ESPECIAIS RESPONSAVEIS POR MUDAR O COMPORTAMENTO DOS FANTASMAS
// ---------------------------------------------------------------------------------

#ifndef PACMAN_SPECIAL_H_
#define PACMAN_SPECIAL_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "PacMan.h"


// ---------------------------------------------------------------------------------

class Special : public Object
{
private:
	Sprite* sprite = nullptr;			// sprite da comida

public:
	Special(Image* img);                // construtor
	~Special();                         // destrutor


	void Update();                      // atualiza��o do objeto
	void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Special::Draw()
{
	sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------


#endif
