#pragma once

#include "Singleton.h"

#include <list>

class Level;
class Controller;
class GameObject;

class Game : public Singleton<Game>
{
public:

	Game();
	virtual ~Game();

protected:

	Level* mLevel;
	Controller* mController;

	bool mRenderNeeded;

	std::list<GameObject*> objects;

public:

	void Init();
	void Run();

	void Update();
	void Render();

	void RequestRender();
	void AddObject(GameObject* object);


	Level* GetLevel() const { return mLevel; }
	Controller* GetController() const { return mController; }
	std::list<GameObject*>& GetEntities() { return objects; }
};

