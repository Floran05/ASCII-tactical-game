#include "Game.h"

#include <iostream>

#include "Level.h"
#include "Controller.h"
#include "Windows.h"

Game::Game()
	: mIsGameEnded(false)
{
}

Game::~Game()
{
}

void Game::Init()
{
	mLevel.Load();
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
	if (I(Game)->GetLevel().GetRemainingEnemies() <= 0)
	{
		if (!I(Game)->GetLevel().Load())
		{
			GetLevel().OnWin();
		}
	}

	mLevel.Update();
	for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		if (*it == nullptr || !(*it)->IsAlive()) continue;
		(*it)->Update();

		if (mIsGameEnded) return;
	}
}

void Game::Render()
{
	mLevel.Render();
	for (auto it = mObjects.begin(); it != mObjects.end();)
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
			GetLevel().SetCellContent(pos, nullptr);
			it = mObjects.erase(it);
		}
	}

	if (mIsGameEnded)
	{
		mObjects.clear();
		GetLevel().OnGameOver();
	}
}

void Game::AddObject(GameObject* object)
{
	mObjects.emplace_back(object);
}

void Game::GameOver()
{
	mIsGameEnded = true;
}
