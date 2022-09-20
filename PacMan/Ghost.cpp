// ---------------------------------------------------------------------------------
// PACMAN
// INIMIGOS DO PLAYER, AO INCOSTAR MATAM OU MORREM
// ---------------------------------------------------------------------------------

#include "PacMan.h"
#include "Player.h"
#include "Ghost.h"
#include "Pivot.h"

// ---------------------------------------------------------------------------------

Ghost::Ghost(Player * p, float X, float Y, float time, uint enemy)
{
    // Inimigo deve movimentar-se em rela��o a tal player
    player = p;

    // Sprites a definir
	switch (enemy) {
	case PINK: {
		spriteL = new Sprite("Resources/fantPinkL.png");
		spriteR = new Sprite("Resources/fantPinkR.png");
		spriteU = new Sprite("Resources/fantPinkU.png");
		spriteD = new Sprite("Resources/fantPinkD.png");
		fleeL = new Sprite("Resources/FantShockL.png");
		fleeR = new Sprite("Resources/FantShockR.png");
		fleeU = new Sprite("Resources/FantShockU.png");
		fleeD = new Sprite("Resources/FantShockD.png");
		break;
	}
	case ORANGE: {
		spriteL = new Sprite("Resources/fantOrangeL.png");
		spriteR = new Sprite("Resources/fantOrangeR.png");
		spriteU = new Sprite("Resources/fantOrangeU.png");
		spriteD = new Sprite("Resources/fantOrangeD.png");
		fleeL = new Sprite("Resources/FantShockL.png");
		fleeR = new Sprite("Resources/FantShockR.png");
		fleeU = new Sprite("Resources/FantShockU.png");
		fleeD = new Sprite("Resources/FantShockD.png");
		break;
	}
	case RED: {
		spriteL = new Sprite("Resources/fantRedL.png");
		spriteR = new Sprite("Resources/fantRedR.png");
		spriteU = new Sprite("Resources/fantRedU.png");
		spriteD = new Sprite("Resources/fantRedD.png");
		fleeL = new Sprite("Resources/FantShockL.png");
		fleeR = new Sprite("Resources/FantShockR.png");
		fleeU = new Sprite("Resources/FantShockU.png");
		fleeD = new Sprite("Resources/FantShockD.png");
		break;
	}
	default: {
		spriteL = new Sprite("Resources/fantBlueL.png");
		spriteR = new Sprite("Resources/fantBlueR.png");
		spriteU = new Sprite("Resources/fantBlueU.png");
		spriteD = new Sprite("Resources/fantBlueD.png");
		fleeL = new Sprite("Resources/FantShockL.png");
		fleeR = new Sprite("Resources/FantShockR.png");
		fleeU = new Sprite("Resources/FantShockU.png");
		fleeD = new Sprite("Resources/FantShockD.png");
	}
	}

    // imagem do player � 48 por 48 (com borda transparente de W pixels)
    bbox = new Rect(-20, -20, 20, 20);
    MoveTo(X, Y);
    type = GHOST;

	stateTime = time;
	pauseTime = time;
	origemX = X;
	origemY = Y;
}

// ---------------------------------------------------------------------------------

Ghost::~Ghost()
{
	delete fleeL;
	delete fleeR;
	delete fleeU;
	delete fleeD;

    delete spriteL;
    delete spriteR;
    delete spriteU;
    delete spriteD;
    delete bbox;
}

// ---------------------------------------------------------------------------------

void Ghost::Stop() {
    velX = 0;
    velY = 0;
}

void Ghost::Up()
{
	if (state == PURSUE) {
		velX = 0;
		velY = -115.0f;
	}
	if (state == FLEE) {
		velX = 0;
		velY = -85.0f;
	}
    
}
void Ghost::Down()
{
	if (state == PURSUE) {
		velX = 0;
		velY = 115.0f;
	}
	if (state == FLEE) {
		velX = 0;
		velY = 85.0f;
	}
}

void Ghost::Left()
{
	if (state == PURSUE) {
		velX = -115.0f;
		velY = 0;
	}
	if (state == FLEE) {
		velX = -85.0f;
		velY = 0;
	}
}

void Ghost::Right()
{
	if (state == PURSUE) {
		velX = 115.0f;
		velY = 0;
	}
	if (state == FLEE) {
		velX = 85.0f;
		velY = 0;
	}
}

// ---------------------------------------------------------------------------------

void Ghost::OnCollision(Object* obj)
{
	if (obj->Type() == PIVOT)
		PivotCollision(obj);
	if (obj->Type() == GHOST)
		GhostCollision(obj);
}

void Ghost::PivotCollision(Object* obj)
{
	Pivot* p = (Pivot*)obj;
	distX = player->X() - x;
	distY = player->Y() - y;

	//EXISTEM O ESTADO DO PLAYER PURSUE E FLEE QUE DEFINIEM SE ELE ESTA SENDO PERSEGUIDO OU PERSEGUINDO
	if (state == PURSUE) {
		if (distX > 25.0f || distX < -25.0f) {
			if (distX < 0)
			{
				nextMove = LEFT;

				if (currentMove == RIGHT || currentMove == STOPED)
				{
					currentMove = LEFT;
					Left();
				}
			}
			else {
				if (distX > 0)
				{
					nextMove = RIGHT;

					if (currentMove == LEFT || currentMove == STOPED)
					{
						currentMove = RIGHT;
						Right();
					}
				}
			}
		}
		else {
			if (distY < 0)
			{
				nextMove = UP;

				if (currentMove == DOWN || currentMove == STOPED)
				{
					currentMove = UP;
					Up();
				}
			}
			else {
				if (distY > 0)
				{
					nextMove = DOWN;

					if (currentMove == UP || currentMove == STOPED)
					{
						currentMove = DOWN;
						Down();
					}
				}
			}
		}
	}

	switch (currentMove)
	{
	case STOPED:
		// -----------------------
		// CurrentMove == STOPED
		// -----------------------

		switch (nextMove)
		{
		case LEFT:
			if (p->left)
			{
				currentMove = LEFT;
				Left();
			}
			break;
		case RIGHT:
			if (p->right)
			{
				currentMove = RIGHT;
				Right();
			}

			break;
		case UP:
			if (p->up)
			{
				currentMove = UP;
				Up();
			}
			break;
		case DOWN:
			if (p->down)
			{
				currentMove = DOWN;
				Down();
			}
			break;
		}
		break;

	case LEFT:
		// -----------------------
		// CurrentMove == LEFT
		// -----------------------

		if (x < p->X())
		{
			if (!p->left)
			{
				MoveTo(p->X(), Y());
				currentMove = STOPED;
				Stop();
				if (p->down) {
					currentMove = DOWN;
					Down();
				}
				else if (p->up){
					currentMove = UP;
					Up();
				}
				else {
					currentMove = RIGHT;
					Right();
				}
			}
		}

		switch (nextMove)
		{
		case LEFT:
			if (x < p->X())
			{
				if (!p->left)
				{
					MoveTo(p->X(), Y());
					currentMove = STOPED;
					Stop();
					if (p->down) {
						currentMove = DOWN;
						Down();
					}
					else if (p->up){
						currentMove = UP;
						Up();
					}
					else {
						currentMove = RIGHT;
						Right();
					}
				}
			}
			break;
		case RIGHT:
			currentMove = RIGHT;
			Right();

			break;
		case UP:
			if (x < p->X())
			{
				if (p->up)
				{
					MoveTo(p->X(), Y());
					currentMove = UP;
					Up();
				}
			}
			break;
		case DOWN:
			if (x < p->X())
			{
				if (p->down)
				{
					MoveTo(p->X(), Y());
					currentMove = DOWN;
					Down();
				}
			}
			break;
		}
		break;

	case RIGHT:
		// -----------------------
		// CurrentMove == RIGHT
		// -----------------------

		if (x > p->X())
		{
			if (!p->right)
			{
				MoveTo(p->X(), Y());
				currentMove = STOPED;
				Stop();
				if (p->down) {
					currentMove = DOWN;
					Down();
				}
				else if(p->up){
					currentMove = UP;
					Up();
				}
				else {
					currentMove = LEFT;
					Left();
				}
			}
		}

		switch (nextMove)
		{
		case LEFT:
			currentMove = LEFT;
			Left();
			break;
		case RIGHT:
			if (x > p->X())
			{
				if (!p->right)
				{
					MoveTo(p->X(), Y());
					currentMove = STOPED;
					Stop();
					if (p->down) {
						currentMove = DOWN;
						Down();
					}
					else if (p->up){
						currentMove = UP;
						Up();
					}
					else {
						currentMove = LEFT;
						Left();
					}
				}
			}

			break;
		case UP:
			if (x > p->X())
			{
				if (p->up)
				{
					MoveTo(p->X(), Y());
					currentMove = UP;
					Up();
				}
			}
			break;
		case DOWN:
			if (x > p->X())
			{
				if (p->down)
				{
					MoveTo(p->X(), Y());
					currentMove = DOWN;
					Down();
				}
			}
			break;
		}
		break;

	case UP:
		// -----------------------
		// CurrentMove == UP
		// -----------------------

		if (y < p->Y())
		{
			if (!p->up)
			{
				MoveTo(p->X(), Y());
				currentMove = STOPED;
				Stop();
				if (p->right) {
					currentMove = RIGHT;
					Right();
				}
				else if (p->left){
					currentMove = LEFT;
					Left();
				}
				else {
					currentMove = DOWN;
					Down();
				}
			}
		}

		switch (nextMove)
		{
		case LEFT:
			if (y < p->Y())
			{
				if (p->left)
				{
					MoveTo(x, p->Y());
					currentMove = LEFT;
					Left();
				}
			}
			break;
		case RIGHT:
			if (y < p->Y())
			{
				if (p->right)
				{
					MoveTo(x, p->Y());
					currentMove = RIGHT;
					Right();
				}
			}
			break;
		case UP:
			if (y < p->Y())
			{
				if (!p->up)
				{
					MoveTo(p->X(), Y());
					currentMove = STOPED;
					Stop();
					if (p->right) {
						currentMove = RIGHT;
						Right();
					}
					else if (p->left){
						currentMove = LEFT;
						Left();
					}
					else {
						currentMove = DOWN;
						Down();
					}
				}
			}
			break;
		case DOWN:
			currentMove = DOWN;
			Down();
			break;
		}
		break;

	case DOWN:
		// -----------------------
		// CurrentMove == DOWN
		// -----------------------

		if (y > p->Y())
		{
			if (!p->down)
			{
				MoveTo(p->X(), Y());
				currentMove = STOPED;
				Stop();
				if (p->right) {
					currentMove = RIGHT;
					Right();
				}
				else if (p->left){
					currentMove = LEFT;
					Left();
				}
				else {
					currentMove = UP;
					Up();
				}
			}
		}

		switch (nextMove)
		{
		case LEFT:
			if (y > p->Y())
			{
				if (p->left)
				{
					MoveTo(x, p->Y());
					currentMove = LEFT;
					Left();
				}
			}
			break;
		case RIGHT:
			if (y > p->Y())
			{
				if (p->right)
				{
					MoveTo(x, p->Y());
					currentMove = RIGHT;
					Right();
				}
			}
			break;
		case UP:
			currentMove = UP;
			Up();
			break;
		case DOWN:
			if (y > p->Y())
			{
				if (!p->down)
				{
					MoveTo(p->X(), Y());
					currentMove = STOPED;
					Stop();
					if (p->right) {
						currentMove = RIGHT;
						Right();
					}
					else if (p->left){
						currentMove = LEFT;
						Left();
					}
					else {
						currentMove = UP;
						Up();
					}
				}
			}
			break;
		}
		break;
	}

}

void Ghost::GhostCollision(Object* obj)
{
	Ghost* g = (Ghost*)obj;
	if (x <= g->X() && (currentMove == RIGHT && g->currentMove == RIGHT))
		MoveTo(g->X() - spriteR->Width(), Y());
	if (x >= g->X() && (currentMove == LEFT && g->currentMove == LEFT))
		MoveTo(g->X() + spriteL->Width(), Y());
	if (y <= g->Y() && (currentMove == DOWN && g->currentMove == DOWN))
		MoveTo(X(), g->Y() - spriteD->Height());
	if (y >= g->Y() && (currentMove == UP && g->currentMove == UP))
		MoveTo(X(), g->Y() + spriteU->Height());
}

// ---------------------------------------------------------------------------------

void Ghost::Update()
{
	state = !player->state;

	if (state == FLEE && gameStart) {
		if (distX > distY || player->Y() == y) {
			if (distX < 0)
			{
				nextMove = RIGHT;

				if (currentMove == LEFT || currentMove == STOPED)
				{
					currentMove = RIGHT;
					Right();
				}
			}
			else {
				if (distX > 0)
				{
					nextMove = LEFT;

					if (currentMove == RIGHT || currentMove == STOPED)
					{
						currentMove = LEFT;
						Left();
					}
				}
			}
		}
		else {
			if (distY < 0)
			{
				nextMove = DOWN;

				if (currentMove == UP || currentMove == STOPED)
				{
					currentMove = DOWN;
					Down();
				}
			}
			else {
				if (distY > 0)
				{
					nextMove = UP;

					if (currentMove == DOWN || currentMove == STOPED)
					{
						currentMove = UP;
						Up();
					}
				}
			}
		}
   }

    // atualiza posi��o
    Translate(velX * gameTime, velY * gameTime);

    // mant�m player dentro da tela
    if (x + 20 < 0)
        MoveTo(window->Width() + 20.f, Y());

    if (x - 20 > window->Width())
        MoveTo(-20.0f, Y());

    if (Y() + 20 < 0)
        MoveTo(x, window->Height() + 20.0f);

    if (Y() - 20 > window->Height())
        MoveTo(x, -20.0f);

	if (state == PURSUE) {
		stateTime -= gameTime;
	}

	if (stateTime <= 0 && !gameStart) {
		MoveTo(455.0f, 313.0f);
		Up();
		gameStart = !gameStart;
	}
}

// ---------------------------------------------------------------------------------

void Ghost::Draw()
{
	if (state == PURSUE)
		switch (currentMove)
		{
		case STOPED: spriteD->Draw(x, y, Layer::UPPER); break;
		case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
		case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
		case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
		case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
		default:
			switch (nextMove)
			{
			case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
			case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
			case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
			case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
			default:    spriteL->Draw(x, y, Layer::UPPER);
			}
		}
	if (state == FLEE)
		switch (currentMove)
		{
		case STOPED: fleeD->Draw(x, y, Layer::UPPER); break;
		case LEFT:  fleeL->Draw(x, y, Layer::UPPER); break;
		case RIGHT: fleeR->Draw(x, y, Layer::UPPER); break;
		case UP:    fleeU->Draw(x, y, Layer::UPPER); break;
		case DOWN:  fleeD->Draw(x, y, Layer::UPPER); break;
		default:
			switch (nextMove)
			{
			case LEFT:  fleeL->Draw(x, y, Layer::UPPER); break;
			case RIGHT: fleeR->Draw(x, y, Layer::UPPER); break;
			case UP:    fleeU->Draw(x, y, Layer::UPPER); break;
			case DOWN:  fleeD->Draw(x, y, Layer::UPPER); break;
			default:    fleeL->Draw(x, y, Layer::UPPER);
			}
		}
    
}