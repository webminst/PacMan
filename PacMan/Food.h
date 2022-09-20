/**********************************************************************************
// Food (Arquivo de Cabe�alho)
//
// Cria��o:     03 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Comida do PacMan
//
**********************************************************************************/

#ifndef PACMAN_FOOD_H_
#define PACMAN_FOOD_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "PacMan.h"


// ---------------------------------------------------------------------------------

class Food : public Object
{
private:
	Sprite* sprite = nullptr;			// sprite da comida

public:
	Food(Image* img);                   // construtor
	~Food();                            // destrutor


	void Update();                      // atualiza��o do objeto
	void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Food::Draw()
{
	sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------


#endif