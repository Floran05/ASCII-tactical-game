#pragma once

#include "GameObject.h"

#include <vector>
#include <string>
#include <Windows.h>

class Player;
class Cell;

class Level : public GameObject
{
public:

	Level();
	virtual ~Level();

	void Update() override;
	void Render() override;

protected:

	Player* mPlayer;

	std::vector<std::vector<Cell*>> mGrid;
	unsigned int mCurrentLevelIndex;



protected:

	// Load level to mGrid from txt lines
	void LoadFromTxtLevel(const std::vector<std::string>& lines);

	// Draw grid top / bottom border
	void DrawHorizontalBorder();
	// Change console text / background color
	void SetConsoleColor(HANDLE handleConsole, int color = 0);
	// Clear console content
	void ClearConsole(HANDLE handleConsole);
	// Display enemy stats
	void UpdateEnemyUI();
	// Display player stats and messages
	void UpdatePlayerUI();
	void DrawHealthBar(int size, float percent);

	int GetRemainingEnemies();

public:

	// Load level from txt file by index
	virtual void Load(unsigned int levelId = 0);

	Player* GetPlayer() const { return mPlayer; }
	Coordinates GetGridSize() const;
	
	void MoveGameObjectInGrid(Coordinates oldPosition, Coordinates newPosition);
};

