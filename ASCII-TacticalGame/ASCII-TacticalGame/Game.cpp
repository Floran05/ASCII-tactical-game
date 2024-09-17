#include "Game.h"
#include "Level.h"
#include "Controller.h"
#include "Windows.h"

Game::Game()
	: mLevel(nullptr)
	, mController(nullptr)
{
}

Game::~Game()
{
	delete mLevel;
	delete mController;
}

void Game::Init()
{
	mLevel = new Level();
	mController = new Controller();
}

void Game::Run()
{
	while (true)
	{

	}
}

void Game::Start()
{
	mLevel->Load();
}
