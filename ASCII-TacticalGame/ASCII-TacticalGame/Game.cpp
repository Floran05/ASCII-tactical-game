#include "Game.h"

#include <iostream>

#include "Level.h"
#include "Controller.h"
#include "Windows.h"

Game::Game()
	: mLevel(nullptr)
	, mController(nullptr)
	, mIsGameEnded(false)
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
	//AddObject(mLevel);
	mLevel->Load();
	mController = new Controller();
}

void Game::Run()
{
	while (true)
	{
		Update();
		Render();
		if (mIsGameEnded)
		{
			mIsGameEnded = false;
		}
	}
}

void Game::Update()
{
	if (I(Game)->GetLevel()->GetRemainingEnemies() <= 0)
	{
		if (!I(Game)->GetLevel()->Load())
		{
			GetLevel()->OnWin();
		}
	}

	mController->Update();
	mLevel->Update();
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if (*it == nullptr || !(*it)->IsAlive()) continue;
		(*it)->Update();

		if (mIsGameEnded) return;
	}
}

void Game::Render()
{
	mLevel->Render();
	for (auto it = objects.begin(); it != objects.end();)
	{
		if (*it != nullptr && (*it)->IsAlive())
		{
			(*it)->Render();
			++it;
		}
		else
		{
			Coordinates pos = (*it)->GetPosition();
			delete *it;
			*it = nullptr;
			GetLevel()->SetCellContent(pos, nullptr);
			it = objects.erase(it);
		}
	}

	if (mIsGameEnded)
	{
		objects.clear();
		GetLevel()->OnGameOver();
	}
}

void Game::AddObject(GameObject* object)
{
	objects.emplace_back(object);
}

void Game::GameOver()
{
	mIsGameEnded = true;
}
