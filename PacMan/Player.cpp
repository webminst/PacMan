// ---------------------------------------------------------------------------------
// PACMAN
// ---------------------------------------------------------------------------------


#include "PacMan.h"
#include "Player.h"
#include "Pivot.h"
#include "Food.h"
#include "Special.h"
#include "Ghost.h"

// ---------------------------------------------------------------------------------
int cont = 0;
float velYU = -190.0f;
float velYD = 190.0f;
float velXL = -190.0f;
float velXR = 190.0f;

Scene* Player::scene = nullptr;
Player::Player()
{
	// Sprites do player
	spriteL = new Sprite("Resources/PacManLa.png");

	//definindo a bb
	bbox = new Rect(-20, -20, 20, 20);
	type = PLAYER;

	stateTime = 5;
}
Player::Player(Scene* sc)
{
	scene = sc;
	// Sprites do player:
	spriteL = new Sprite("Resources/PacManLa.png");

	//definindo bb
	bbox = new Rect(-20, -20, 20, 20);
	MoveTo(480.0f, 445.0f);
	type = PLAYER;

	stateTime = 5;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete spriteL;
	delete spriteR;
	delete spriteU;
	delete spriteD;
	delete bbox;
}

// ---------------------------------------------------------------------------------

void Player::Stop()
{
	velX = 0;
	velY = 0;
	ctrlWeb = true;
}

// ---------------------------------------------------------------------------------

void Player::Up()
{
	velX = 0;
	velY = velYU;
	ctrlWeb = true;
}

// ---------------------------------------------------------------------------------

void Player::Down()
{
	velX = 0;
	velY = velYD;
	ctrlWeb = true;
}

// ---------------------------------------------------------------------------------

void Player::Left()
{
	velX = velXL;
	velY = 0;
	ctrlWeb = true;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
	velX = velXR;
	velY = 0;
	ctrlWeb = true;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	//Testando quais objetos estao colidindo
	if (obj->Type() == PIVOT)
		PivotCollision(obj);
	if (obj->Type() == FOOD)
		foodCollision(obj);
	if (obj->Type() == SPECIAL)
		specialCollision(obj);
	if (obj->Type() == GHOST)
		ghostCollision(obj);
	if (obj->Type() == OBSTACLE)
		ObstacleCollision(obj);

}

// ---------------------------------------------------------------------------------
//COLISOES personalizadas 
void Player::foodCollision(Object* obj) {
	Food* fd = (Food*)obj;
	setScore(getScore() + 10);
	scene->Delete(fd, STATIC);
	scene->comidasTotais -= 1;
}

void Player::ghostCollision(Object* obj) {
	Ghost* g = (Ghost*)obj;
	if (state == FLEE) {
		//MoveTo(480.0f, 445.0f);
		game->setGameState(GAMEOVER);
	}
	else {
		g->stateTime = g->pauseTime;
		g->gameStart = false;
		g->currentMove = g->nextMove = STOPED;
		g->Stop();
		g->MoveTo(g->origemX, g->origemY);
	}
}

void Player::ObstacleCollision(Object* obj)
{
	if (ctrlWeb) {
		velX = velX * 0.55f;
		velY = velY * 0.5f;
		ctrlWeb = false;
	}
}

void Player::specialCollision(Object* obj) {
	Special* sp = (Special*)obj;
	setScore(getScore() + 10);
	scene->Delete(sp, STATIC);
	state = PURSUE;
}
// ---------------------------------------------------------------------------------

void Player::PivotCollision(Object* obj)
{
	Pivot* p = (Pivot*)obj;

	switch (currState)
	{
	case STOPED:
		// -----------------------
		//CurrentState == STOPED
		// -----------------------

		switch (nextState)
		{
		case LEFT:
			if (p->left)
			{
				currState = LEFT;
				Left();
			}
			break;
		case RIGHT:
			if (p->right)
			{
				currState = RIGHT;
				Right();
			}

			break;
		case UP:
			if (p->up)
			{
				currState = UP;
				Up();
			}
			break;
		case DOWN:
			if (p->down)
			{
				currState = DOWN;
				Down();
			}
			break;
		}
		break;

	case LEFT:
		// -----------------------
		// CurrentState == LEFT
		// -----------------------

		if (x < p->X())
		{
			if (!p->left)
			{
				MoveTo(p->X(), Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			if (x < p->X())
			{
				if (!p->left)
				{
					MoveTo(p->X(), Y());
					currState = STOPED;
					Stop();
				}
			}
			break;
		case RIGHT:
			currState = RIGHT;
			Right();

			break;
		case UP:
			if (x < p->X())
			{
				if (p->up)
				{
					MoveTo(p->X(), Y());
					currState = UP;
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
					currState = DOWN;
					Down();
				}
			}
			break;
		}
		break;

	case RIGHT:
		// -----------------------
		// CurrentState == RIGHT
		// -----------------------

		if (x > p->X())
		{
			if (!p->right)
			{
				MoveTo(p->X(), Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			currState = LEFT;
			Left();
			break;
		case RIGHT:
			if (x > p->X())
			{
				if (!p->right)
				{
					MoveTo(p->X(), Y());
					currState = STOPED;
					Stop();
				}
			}

			break;
		case UP:
			if (x > p->X())
			{
				if (p->up)
				{
					MoveTo(p->X(), Y());
					currState = UP;
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
					currState = DOWN;
					Down();
				}
			}
			break;
		}
		break;

	case UP:
		// -----------------------
		// CurrentState == UP
		// -----------------------

		if (y < p->Y())
		{
			if (!p->up)
			{
				MoveTo(x, p->Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			if (y < p->Y())
			{
				if (p->left)
				{
					MoveTo(x, p->Y());
					currState = LEFT;
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
					currState = RIGHT;
					Right();
				}
			}
			break;
		case UP:
			if (y < p->Y())
			{
				if (!p->up)
				{
					MoveTo(x, p->Y());
					currState = STOPED;
					Stop();
				}
			}
			break;
		case DOWN:
			currState = DOWN;
			Down();
			break;
		}
		break;

	case DOWN:
		// -----------------------
		// CurrentState == DOWN
		// -----------------------

		if (y > p->Y())
		{
			if (!p->down)
			{
				MoveTo(x, p->Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			if (y > p->Y())
			{
				if (p->left)
				{
					MoveTo(x, p->Y());
					currState = LEFT;
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
					currState = RIGHT;
					Right();
				}
			}
			break;
		case UP:
			currState = UP;
			Up();
			break;
		case DOWN:
			if (y > p->Y())
			{
				if (!p->down)
				{
					MoveTo(x, p->Y());
					currState = STOPED;
					Stop();
				}
			}
			break;
		}
		break;
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	//Controles
	if (window->KeyDown(VK_LEFT))
	{
		nextState = LEFT;

		if (currState == RIGHT || currState == STOPED)
		{
			currState = LEFT;
			Left();
		}
	}

	if (window->KeyDown(VK_RIGHT))
	{
		nextState = RIGHT;

		if (currState == LEFT || currState == STOPED)
		{
			currState = RIGHT;
			Right();
		}
	}

	if (window->KeyDown(VK_UP))
	{
		nextState = UP;

		if (currState == DOWN || currState == STOPED)
		{
			currState = UP;
			Up();
		}
	}

	if (window->KeyDown(VK_DOWN))
	{
		nextState = DOWN;

		if (currState == UP || currState == STOPED)
		{
			currState = DOWN;
			Down();
		}
	}

	// atualiza posição
	Translate(velX * gameTime, velY * gameTime);

	// mantém player dentro da tela
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
		
		velYU = -250.0f;
		velYD = 250.0f;
		velXL = -250.0f;
		velXR = 250.0f;
	}

	if (stateTime <= 0) {
		state = FLEE;
		
		velYU = -190.0f;
		velYD = 190.0f;
		velXL = -190.0f;
		velXR = 190.0f;

		stateTime = 5;
	}

	if (cont <= 200) {
		anim = false;
		cont++;
	}
	else {
		if (cont <= 400) {
			anim = true;
			cont++;
		}
		else {
			cont = 0;
		}
	}

}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
	switch (currState)
	{
	case LEFT:
		if (anim) {
			spriteL = new Sprite("Resources/PacManLa.png");
			spriteL->Draw(x, y, Layer::MIDDLE);
			break;
		}
		else {
			spriteL = new Sprite("Resources/PacManLf.png");
			spriteL->Draw(x, y, Layer::MIDDLE);
			break;
		}

	case RIGHT:
		if (anim) {
			spriteR = new Sprite("Resources/PacManRa.png");
			spriteR->Draw(x, y, Layer::MIDDLE);
			break;
		}
		else {
			spriteR = new Sprite("Resources/PacManRf.png");
			spriteR->Draw(x, y, Layer::MIDDLE);
			break;
		}

	case UP:
		if (anim) {
			spriteU = new Sprite("Resources/PacManUa.png");
			spriteU->Draw(x, y, Layer::MIDDLE);
			break;
		}
		else {
			spriteU = new Sprite("Resources/PacManUf.png");
			spriteU->Draw(x, y, Layer::MIDDLE);
			break;
		}

	case DOWN:
		if (anim) {
			spriteD = new Sprite("Resources/PacManDa.png");
			spriteD->Draw(x, y, Layer::MIDDLE);
			break;
		}
		else {
			spriteD = new Sprite("Resources/PacManDf.png");
			spriteD->Draw(x, y, Layer::MIDDLE);
			break;
		}

	default:
		switch (nextState)
		{
		case LEFT:
			if (anim) {
				spriteL = new Sprite("Resources/PacManLa.png");
				spriteL->Draw(x, y, Layer::MIDDLE);
				break;
			}
			else {
				spriteL = new Sprite("Resources/PacManLf.png");
				spriteL->Draw(x, y, Layer::MIDDLE);
				break;
			}

		case RIGHT:
			if (anim) {
				spriteR = new Sprite("Resources/PacManRa.png");
				spriteR->Draw(x, y, Layer::MIDDLE);
				break;
			}
			else {
				spriteR = new Sprite("Resources/PacManRf.png");
				spriteR->Draw(x, y, Layer::MIDDLE);
				break;
			}

		case UP:
			if (anim) {
				spriteU = new Sprite("Resources/PacManUa.png");
				spriteU->Draw(x, y, Layer::MIDDLE);
				break;
			}
			else {
				spriteU = new Sprite("Resources/PacManUf.png");
				spriteU->Draw(x, y, Layer::MIDDLE);
				break;
			}

		case DOWN:
			if (anim) {
				spriteD = new Sprite("Resources/PacManDa.png");
				spriteD->Draw(x, y, Layer::MIDDLE);
				break;
			}
			else {
				spriteD = new Sprite("Resources/PacManDf.png");
				spriteD->Draw(x, y, Layer::MIDDLE);
				break;
			}

		default:    spriteL->Draw(x, y, Layer::MIDDLE);
		}
	}
}

// ---------------------------------------------------------------------------------
void Player::setScene(Scene* sc) {
	scene = sc;
}
// ---------------------------------------------------------------------------------