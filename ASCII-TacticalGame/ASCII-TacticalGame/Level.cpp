#include <fstream>
#include <iostream>
#include <Windows.h>

#include "Game.h"
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

void Level::LoadFromTxtLevel(const std::vector<std::string>& lines)
{
	for (int i = 0, j = lines.size(); i < j; ++i)
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
			case 'F':
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

void Level::DrawHorizontalBorder()
{
	if (mGrid.size() <= 0) return;

	std::cout << "+";
	for (int i = 0, j = mGrid[0].size(); i < j; ++i)
	{
		std::cout << "---+";
	}
	std::cout << std::endl;
}

void Level::SetConsoleColor(int color)
{
	HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (color <= 0)
	{
		color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}
	SetConsoleTextAttribute(handleConsole, color);
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

void Level::Update()
{
	DrawHorizontalBorder();
	int r = 0, c = 0;
	for (std::vector<Cell*> row : mGrid)
	{
		c = 0;

		std::cout << "|";
		for (Cell* cell : row)
		{
			if (cell->GetContent() == nullptr)
			{
				const Coordinates PlayerPosition = mPlayer->GetPosition();
				if (Utilities::ManhattanDistance(PlayerPosition.x, PlayerPosition.y, r, c) <= mPlayer->GetMaxRange())
				{
					SetConsoleColor(BACKGROUND_BLUE);
				}
				std::cout << "   ";
				SetConsoleColor(0);
				std::cout << "|";
			}
			else
			{
				std::cout << " " << cell->GetContent()->GetSymbol() << " |";
			}

			++c;
		}
		std::cout << std::endl;
		DrawHorizontalBorder();

		++r;
	}
}
