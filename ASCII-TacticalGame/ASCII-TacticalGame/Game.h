#pragma once

#include "Singleton.h"

#include <list>

#include "Level.h"
#include "Controller.h"

class Level;
class Controller;
class GameObject;

class Game : public Singleton<Game>
{
public:

	Game();
	virtual ~Game();

protected:

	Level mLevel;
	Controller mController;

	bool mIsGameEnded;

	std::list<GameObject*> mObjects;

public:

	void Init();
	void Run();
	void Update();
	void Render();

	void AddObject(GameObject* object);

	void GameOver();

	Level& GetLevel() { return mLevel; }
	Controller& GetController() { return mController; }
	std::list<GameObject*>& GetEntities() { return mObjects; }
};

