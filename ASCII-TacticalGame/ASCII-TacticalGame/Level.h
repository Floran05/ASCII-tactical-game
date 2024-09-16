#pragma once

#include "GameObject.h"

#include <vector>
#include <string>

class Player;
class Cell;

class Level : public GameObject
{
public:

	Level();
	virtual ~Level();

protected:

	Player* mPlayer;

	std::vector<std::vector<Cell*>> mGrid;
	unsigned int mCurrentLevelIndex;

protected:

	void LoadFromTxtLevel(const std::vector<std::string>& lines);

	void DrawHorizontalBorder();
	void SetConsoleColor(int color = 0);

public:

	// Load level from txt file by index
	virtual void Load(unsigned int levelId = 0);
	// Update level to represent current game state
	virtual void Update();

	Player* GetPlayer() const { return mPlayer; }
	
};

