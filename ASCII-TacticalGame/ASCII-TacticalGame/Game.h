#pragma once

#include "Singleton.h"

#define FRAMERATE 30

class Level;
class Controller;

class Game : public Singleton<Game>
{
public:

	Game();
	virtual ~Game();

protected:

	Level* mLevel;
	Controller* mController;

public:

	void Init();
	void Run();

	Level* GetLevel() { return mLevel; }
	Controller* GetController() { return mController; }


};

