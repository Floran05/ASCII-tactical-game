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
	mLevel->Load();
	AddObject(mLevel);
	mController = new Controller();
}

void Game::Run()
{
	while (true)
	{
		mController->Update();
		for (auto it = objects.begin(); it != objects.end(); ++it)
		{
			(*it)->Update();
		}

		if (mRenderNeeded)
		{
			for (auto it = objects.begin(); it != objects.end(); ++it)
			{
				(*it)->Render();
			}
			mRenderNeeded = false;
		}
		
		Sleep(static_cast<DWORD>((1.f / FRAMERATE) * 1000));
	}
}

void Game::RequestRender()
{
	mRenderNeeded = true;
}

void Game::AddObject(GameObject* object)
{
	objects.emplace_back(object);
}
