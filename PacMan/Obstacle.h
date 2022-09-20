// ---------------------------------------------------------------------------------
// PACMAN
// OBJETOS QUE ATRAPALHAM O PLAYER
// ---------------------------------------------------------------------------------


#ifndef PACMAN_OBSTACLE_H_
#define PACMAN_OBSTACLE_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites
#include "PacMan.h"


// ---------------------------------------------------------------------------------

class Obstacle : public Object
{
private:
	Sprite* sprite = nullptr;			// sprite da comida

public:
	Obstacle();							// construtor
	~Obstacle();                        // destrutor


	void Update();                      // atualização do objeto
	void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Obstacle::Draw()
{
	sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------


#endif