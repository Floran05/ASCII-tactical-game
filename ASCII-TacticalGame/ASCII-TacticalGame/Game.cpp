#include "Game.h"
#include "Level.h"
#include "Controller.h"

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
	mLevel->Load();
	mLevel->Update();
	mController = new Controller();
}

void Game::Run()
{
	
}

void Game::Start()
{

}
