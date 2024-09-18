#include "Game.h"

#include <iostream>

#include "Level.h"
#include "Controller.h"
#include "Windows.h"

Game::Game()
	: mLevel(nullptr)
	, mController(nullptr)
	, mRenderNeeded(true)
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
	AddObject(mLevel);
	mLevel->Load();
	mController = new Controller();
}

void Game::Run()
{
	while (true)
	{
		Update();
		Render();
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
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if (mIsGameEnded) return;

		if (*it == nullptr || !(*it)->IsAlive()) continue;
		(*it)->Update();
	}
}

void Game::Render()
{
	if (mIsGameEnded)
	{
		GetLevel()->OnGameOver();
		mIsGameEnded = false;
		return;
	}

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
	mRenderNeeded = false;
}

void Game::RequestRender()
{
	mRenderNeeded = true;
}

void Game::AddObject(GameObject* object)
{
	objects.emplace_back(object);
}

void Game::GameOver()
{
	mIsGameEnded = true;
}
