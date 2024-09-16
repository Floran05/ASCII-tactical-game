#pragma once

#include "GameObject.h"

#include <vector>

#include "Player.h"
#include "Cell.h"

class Level : public GameObject
{
public:

	Level();
	virtual ~Level();

protected:

	static Player* sPlayer;

	std::vector<std::vector<Cell*>> mGrid;
	unsigned int mCurrentLevelIndex;

public:

	virtual void CreateLevel(unsigned int levelId);
	virtual void UpdateLevel();
	
};

