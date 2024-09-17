#include "Game.h"

#include <iostream>

#include "Level.h"
#include "Controller.h"
#include "Windows.h"

Game::Game()
	: mLevel(nullptr)
	, mController(nullptr)
	, mRenderNeeded(true)
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
	mLevel->Render();
	mController = new Controller();
}

void Game::Run()
{
	while (true)
	{
		Update();
		if (mRenderNeeded)
		{
			Render();
		}
	}
}

void Game::Update()
{
	mController->Update();
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if (!(*it)->IsAlive()) continue;
		(*it)->Update();
	}
}

void Game::Render()
{
	for (auto it = objects.begin(); it != objects.end();++it)
	{
		if (!(*it)->IsAlive()) continue;
		(*it)->Render();
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
