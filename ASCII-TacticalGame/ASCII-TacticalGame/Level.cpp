#include <fstream>
#include <iostream>

#include "Game.h"
#include "Console.h"
#include "Level.h"
#include "Player.h"
#include "Golem.h"
#include "Spectre.h"
#include "Reaper.h"
#include "Cell.h"
#include "Utilities.h"

Level::Level()
	: mPlayer(nullptr)
	, mCurrentLevelIndex(0)
{
	mGrid.clear();
}

Level::~Level()
{
	delete mPlayer;
}

void Level::Update()
{
	mPlayer->Update();
	if (GetRemainingEnemies() <= 0)
	{
		Load(++mCurrentLevelIndex);
	}
}

void Level::Render()
{
	if (!mGrid.size() || mPlayer == nullptr) return;
	int gridWidth = static_cast<int>(mGrid[0].size());

	Console::ClearConsole();

	Console::DrawCharacterStats(mPlayer->GetCurrentTarget(), gridWidth);
	Console::DrawGridHorizontalBorder(gridWidth);
	const Coordinates initialPosition = mPlayer->GetRoundPosition();
	int r = 0, c = 0;
	for (std::vector<Cell*> row : mGrid)
	{
		c = 0;

		std::cout << "|";
		for (Cell* cell : row)
		{
			if (cell->GetContent() == nullptr || !cell->GetContent()->IsAlive())
			{
				if (mPlayer->IsHisTurn())
				{
					if (r == initialPosition.x && c == initialPosition.y)
					{
						Console::SetConsoleColor(BACKGROUND_BLUE);
					}
					else if (Utilities::ManhattanDistance(initialPosition.x, initialPosition.y, r, c) <= mPlayer->GetMaxRange())
					{
						Console::SetConsoleColor(BACKGROUND_GREEN);
					}
				}
				std::cout << "   ";
				Console::SetConsoleColor(0);
				std::cout << "|";
			}
			else
			{
				std::cout << " ";
				if (mPlayer->GetCurrentTarget() != nullptr && cell->GetContent()->GetId() == mPlayer->GetCurrentTarget()->GetId())
				{
					Console::SetConsoleColor(FOREGROUND_RED);
				}
				std::cout << cell->GetContent()->GetSymbol();
				Console::SetConsoleColor(0);
				std::cout << " |";
			}

			++c;
		}
		std::cout << std::endl;
		Console::DrawGridHorizontalBorder(gridWidth);

		++r;
	}

	Console::DrawCharacterStats(mPlayer, gridWidth);
	Console::DrawContextualInputs();
	if (!mContextualMessage.empty())
	{
		Console::DrawMessage(mContextualMessage);
	}
}

void Level::LoadFromTxtLevel(const std::vector<std::string>& lines)
{
	for (int i = 0, j = static_cast<int>(lines.size()); i < j; ++i)
	{
		mGrid.emplace_back(std::vector<Cell*>());
		int column = 0;
		for (const char c : lines[i])
		{
			Cell* newCell = new Cell();
			mGrid[i].emplace_back(newCell);
			switch (c)
			{
			case '@':
				if (!mPlayer)
				{
					mPlayer = new Player();
					mPlayer->SetPosition(i, column);
					mPlayer->SetRoundPosition(i, column);
					newCell->SetContent(mPlayer);
				}
				else
				{
					newCell->SetContent(nullptr);
				}
				break;
			case 'G':
				newCell->SetContent(Enemy::Create<Golem>());
				break;
			case 'S':
				newCell->SetContent(Enemy::Create<Spectre>());
				break;
			case 'R':
				newCell->SetContent(Enemy::Create<Reaper>());
				break;
			default:
				newCell->SetContent(nullptr);
				break;
			}

			++column;
		}
	}
}

int Level::GetRemainingEnemies()
{
	int remainingEnemies = 0;
	for (std::vector<Cell*>& row : mGrid)
	{
		for (Cell* cell : row)
		{
			if (cell->GetContent() != nullptr && dynamic_cast<Enemy*>(cell->GetContent()))
			{
				++remainingEnemies;
			}
		}
	}
	return remainingEnemies;
}

void Level::MoveGameObjectInGrid(const Coordinates& oldPosition, const Coordinates& newPosition)
{
	mGrid[newPosition.x][newPosition.y]->SetContent(mGrid[oldPosition.x][oldPosition.y]->GetContent());
	mGrid[oldPosition.x][oldPosition.y]->SetContent(nullptr);
}

bool Level::IsCellEmpty(const Coordinates& position)
{
	if (position.x < 0) 
		return true;
	if (position.x > mGrid.size() - 1) 
		return true;
	if (position.y < 0) 
		return true;
	if (position.y > mGrid[position.x].size() - 1) 
		return true;
	return mGrid[position.x][position.y]->GetContent() == nullptr;
}

void Level::Load(unsigned int levelId)
{
	unsigned int currentLevelId = 0;
	bool bSkipEmptyLine = true;

	std::vector<std::string> levelRaw;

	std::ifstream file("./resources/levels.txt");
	if (!file)
	{
		std::cout << "CAN'T OPEN FILE" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty() && !bSkipEmptyLine)
		{
			++currentLevelId;
			bSkipEmptyLine = true;
			if (levelRaw.size())
			{
				break;
			}
		}

		if (!line.empty()) bSkipEmptyLine = false;

		if (currentLevelId == levelId)
		{
			levelRaw.emplace_back(line);
		}
	}
	file.close();

	return LoadFromTxtLevel(levelRaw);
}

Coordinates Level::GetGridSize() const
{
	if (!mGrid.size()) return Coordinates();
	
	return Coordinates(static_cast<int>(mGrid.size()), static_cast<int>(mGrid[0].size()));
}
