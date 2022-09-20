// ---------------------------------------------------------------------------------
// PACMAN
// PRIMEIRO LEVEL JOGAVEL
// ---------------------------------------------------------------------------------

#include <string>
#include <fstream>

#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Player.h"
#include "Ghost.h"
#include "Pivot.h"
#include "Food.h"
#include "Special.h"
#include "Obstacle.h"
#include "GameOver.h"
using std::ifstream;
using std::string;

Scene* Level1::scene = nullptr;
// ------------------------------------------------------------------------------

void Level1::Init()
{
	// indica em qual tela está
	setGameState(LVL1);

	// cria gerenciador de cena
	scene = new Scene();

	backg = new Sprite("Resources/Level1.png");

	// cria jogador
	player = new Player();
	scene->Add(player, MOVING);
	player->MoveTo(480.0f, 456.0f);//MOVE PARA O PONTO DE INICIO
	player->setScene(scene);

	// cria inimigos no centro ( eixo Y = 365.0f )
	Ghost* ghost = new Ghost(player, 407.0f, 361.0f, 20.0f);
	scene->Add(ghost, MOVING);
	ghost = new Ghost(player, 455.0f, 361.0f, 5.0f, PINK);
	scene->Add(ghost, MOVING);
	ghost = new Ghost(player, 505.0f, 361.0f, 10.0f, ORANGE);
	scene->Add(ghost, MOVING);
	ghost = new Ghost(player, 551.0f, 361.0f, 15.0f, RED);
	scene->Add(ghost, MOVING);


	// cria pontos de mudança de direção
	Pivot* pivot;
	bool left, right, up, down;
	float posX, posY;

	// cria pivôs a partir do arquivo
	ifstream fin;
	fin.open("PivotsL1.txt");
	fin >> left;
	while (!fin.eof())
	{
		if (fin.good())
		{
			// lê linha de informações do pivô
			fin >> right; fin >> up; fin >> down; fin >> posX; fin >> posY;
			pivot = new Pivot(left, right, up, down);
			pivot->MoveTo(posX, posY);
			scene->Add(pivot, STATIC);
		}
		else
		{
			// ignora comentários
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}
		fin >> left;
	}
	fin.close();

	// cria comidas no mapa
	foodSprite = new Image("Resources/Food.png");
	specialSprite = new Image("Resources/Special.png");
	Food* food;
	Special* special = new Special(specialSprite);
	special->MoveTo(73.0f, 73.0f);
	scene->Add(special, STATIC);
	special = new Special(specialSprite);
	special->MoveTo(887.0f, 646.0f);
	scene->Add(special, STATIC);
	special = new Special(specialSprite);
	special->MoveTo(73.0f, 650.0f);
	scene->Add(special, STATIC);
	special = new Special(specialSprite);
	special->MoveTo(888.0f, 73.0f);
	scene->Add(special, STATIC);

	float foodPosX, foodPosY;
	fin.open("FoodL1.txt");
	fin >> foodPosX;
	while (!fin.eof()) {
		if (fin.good()) {
			fin >> foodPosY;
			food = new Food(foodSprite);

			food->MoveTo(foodPosX, foodPosY);
			scene->Add(food, STATIC);
			scene->comidasTotais += 1;
		}
		else {
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}
		fin >> foodPosX;
	}

	fin.close();

	Obstacle* spiderweb = new Obstacle();
	spiderweb->MoveTo(168.0f, 408.0f);
	scene->Add(spiderweb, STATIC);
	spiderweb = new Obstacle();
	spiderweb->MoveTo(890.0f, 165.0f);
	scene->Add(spiderweb, STATIC);

}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
	delete backg;
	delete scene;
	delete foodSprite;
	delete specialSprite;
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
	// habilita/desabilita bounding box
	if (ctrlKeyB && window->KeyDown('B'))
	{
		viewBBox = !viewBBox;
		ctrlKeyB = false;
	}
	else if (window->KeyUp('B'))
	{
		ctrlKeyB = true;
	}

	if (window->KeyDown(VK_ESCAPE))
	{
		// volta para a tela de abertura
		Engine::Next<Home>();
	}
	else if (window->KeyDown('N'))
	{
		// passa manualmente para o próximo nível
		Engine::Next<Level2>();
	}
	else if (window->KeyDown('G'))
	{
		// passa manualmente para a tela de GameOver
		Engine::Next<GameOver>();
	}
	else
	{
		// atualiza cena
		scene->Update();
		scene->CollisionDetection();
	}

	// COMANDOS DO PLAYER
	if (getGameState() == GAMEOVER) {
		Engine::Next<GameOver>();
	}

	if (scene->comidasTotais == 0) {
		// passa naturalmente para o próximo nível
		Engine::Next<Level2>();
	}

}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
	// desenha cena
	backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	scene->Draw();

	// desenha bounding box dos objetos
	if (viewBBox)
		scene->DrawBBox();

}

// ------------------------------------------------------------------------------