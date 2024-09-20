#pragma once

#include "GameObject.h"

#include <vector>
#include <string>

#include "Cell.h"

class Player;

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

	std::string mContextualMessage;

protected:

	// Load level to mGrid from txt lines
	void LoadFromTxtLevel(const std::vector<std::string>& lines);

public:

	// Load level from txt file by index
	virtual bool Load(int levelIndex = -1);
	void ClearGrid();

	int GetRemainingEnemies();
	void SetContextualMessage(const std::string& message) { mContextualMessage = message; }

	Player* GetPlayer() const { return mPlayer; }
	Coordinates GetGridSize() const;
	
	void MoveGameObjectInGrid(const Coordinates& oldPosition, const Coordinates& newPosition);
	bool IsCellEmpty(const Coordinates& position);

	template <typename T>
	T* GetTargetInCell(const Coordinates& position);
	void SetCellContent(const Coordinates& position, GameObject* object);

	void OnGameOver();
	void OnWin();
};

template<typename T>
inline T* Level::GetTargetInCell(const Coordinates& position)
{
	if (!IsCellEmpty(position))
	{
		return dynamic_cast<T*>(mGrid[position.x][position.y]->GetContent());
	}
	return nullptr;
}
