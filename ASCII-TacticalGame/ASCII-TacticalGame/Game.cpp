#include "Game.h"

#include <iostream>

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
	mLevel->Load();
	mController = new Controller();

	mLevel->Render();
}

void Game::Run()
{
	while (true)
	{
		mLevel->Update();
		mController->Update();
		
		Sleep((1.f / FRAMERATE) * 1000);
	}
}
