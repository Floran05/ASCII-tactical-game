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
}

void Level::Render()
{
	if (!mGrid.size() || mPlayer == nullptr) return;
	int gridWidth = static_cast<int>(mGrid[0].size());

	Console::ClearConsole();

	Console::DrawCharacterStats(mPlayer->GetCurrentTarget(), gridWidth);
	Console::DrawGridHorizontalBorder(gridWidth, true);

	// Draw Grid
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
						Console::SetConsoleColor(9 * 12);
					}
					else if (Utilities::ManhattanDistance(initialPosition.x, initialPosition.y, r, c) <= mPlayer->GetMaxRange())
					{
						Console::SetConsoleColor(9 * 16);
					}
				}
				std::cout << "   ";
				Console::SetConsoleColor(c == row.size() - 1 ? 0 : 8);
				std::cout << "|";
				Console::SetConsoleColor(0);
			}
			else
			{
				if (mPlayer->IsHisTurn() && mPlayer->GetCurrentTarget() != nullptr && cell->GetContent()->GetId() == mPlayer->GetCurrentTarget()->GetId())
				{
					Console::SetConsoleColor(12 * 16 + 15);
				}
				std::cout << " ";
				std::cout << cell->GetContent()->GetSymbol();
				std::cout << " ";
				Console::SetConsoleColor(c == row.size() - 1 ? 0 : 8);
				std::cout << "|";
				Console::SetConsoleColor(0);
			}

			++c;
		}
		std::cout << std::endl;
		Console::DrawGridHorizontalBorder(gridWidth, r == mGrid.size() - 1);

		++r;
	}

	Console::DrawCharacterStats(mPlayer, gridWidth);
	if (!mContextualMessage.empty())
	{
		Console::DrawMessage(mContextualMessage);
		std::cout << " ";
	}
	if (mPlayer->IsHisTurn())
	{
		Console::DrawContextualInputs();
	}
}

void Level::LoadFromTxtLevel(const std::vector<std::string>& lines)
{
	ClearGrid();
	for (int i = 0, j = static_cast<int>(lines.size()); i < j; ++i)
	{
		mGrid.emplace_back(std::vector<Cell*>());
		int column = 0;
		for (const char c : lines[i])
		{
			Cell* newCell = new Cell();
			Character* newCharacter = nullptr;
			mGrid[i].emplace_back(newCell);
			switch (c)
			{
			case '@':
				mPlayer = new Player();
				newCharacter = mPlayer;
				break;
			case 'G':
				newCharacter = Enemy::Create<Golem>();
				break;
			case 'S':
				newCharacter = Enemy::Create<Spectre>();
				break;
			case 'R':
				newCharacter = Enemy::Create<Reaper>();
				break;
			default:
				break;
			}

			if (newCharacter)
			{
				newCharacter->SetPosition(i, column);
				newCharacter->SetRoundPosition(i, column);
			}
			newCell->SetContent(newCharacter);

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
			if (Enemy* enemy = dynamic_cast<Enemy*>(cell->GetContent()))
			{
				if(enemy->IsAlive())
				{
					++remainingEnemies;
				}
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

void Level::SetCellContent(const Coordinates& position, GameObject* object)
{
	mGrid[position.x][position.y]->SetContent(object);
}

void Level::OnGameOver()
{
	Console::DrawScreenMessage("G A M E  O V E R", mGrid.size() ? static_cast<int>(mGrid[0].size()) : 10, 12 * 16);
	Sleep(1000);
	Load(0);
}

void Level::OnWin()
{
	Console::DrawScreenMessage("Y O U  W I N", mGrid.size() ? static_cast<int>(mGrid[0].size()) : 10, 12 * 2 + 15);
	Sleep(2000);
	exit(0);
}

bool Level::Load(int levelIndex)
{
	if (levelIndex >= 0)
	{
		mCurrentLevelIndex = levelIndex + 1;
	}
	else
	{
		++mCurrentLevelIndex;
	}
	unsigned int currentLevelId = 0;
	bool bSkipEmptyLine = true;

	std::vector<std::string> levelRaw;

	std::ifstream file("./resources/levels.txt");
	if (!file)
	{
		std::cout << "CAN'T OPEN FILE" << std::endl;
		return false;
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

		if (!line.empty() && currentLevelId == mCurrentLevelIndex - 1)
		{
			levelRaw.emplace_back(line);
		}
	}
	file.close();

	if (!levelRaw.size())
	{
		return false;
	}

	LoadFromTxtLevel(levelRaw);
	return true;
}

void Level::ClearGrid()
{
	for (auto row = mGrid.begin(); row != mGrid.end();)
	{
		for (auto col = (*row).begin(); col != (*row).end();)
		{
			if ((*col)->GetContent() != nullptr)
			{
				(*col)->GetContent()->Kill();
			}
			col = (*row).erase(col);
		}
		row = mGrid.erase(row);
	}
}

Coordinates Level::GetGridSize() const
{
	if (!mGrid.size()) return Coordinates();
	
	return Coordinates(static_cast<int>(mGrid.size()), static_cast<int>(mGrid[0].size()));
}
