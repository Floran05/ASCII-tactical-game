#include "Console.h"

#include <iostream>

#include "Character.h"
#include "Game.h"
#include "Player.h"
#include "Utilities.h"

Console::Console()
{
}

Console::~Console()
{
}

void Console::ClearConsole()
{
	HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(handleConsole, &csbi))
	{
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(handleConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(handleConsole, csbi.dwCursorPosition);
}

void Console::SetConsoleColor(int color)
{
	HANDLE handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (color <= 0)
	{
		color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	}
	SetConsoleTextAttribute(handleConsole, color);
}

void Console::DrawHealthBar(int size, float percent)
{
	if (size < 3) size = 3;
	size -= 2;

	float step = 1.f / size;

	std::cout << "[";
	for (int i = 0; i < size; ++i)
	{
		std::cout << (percent >= i * step ? '=' : ' ');
	}
	std::cout << "]";
}

void Console::DrawCharacterStats(Character* character, int rowSize)
{
	Console::DrawSeparator(rowSize * 4 + 1);
	if (character == nullptr || !character->IsAlive())
	{
		const std::string noTargetMessage = "No target";
		std::cout << std::endl;
		std::cout << std::string(((rowSize * 4 + 1) - noTargetMessage.size()) / 2, ' ') << noTargetMessage << std::endl;
	}
	else
	{
		int healthPointsStringSize = static_cast<int>(std::to_string(character->GetHealthPoints()).size());
		int maxHealthPointsStringSize = static_cast<int>(std::to_string(character->GetMaxHealthPoints()).size());
		int healthBarSize = (rowSize * 4) - 3 - healthPointsStringSize - maxHealthPointsStringSize;
		DrawHealthBar(healthBarSize, static_cast<float>(character->GetHealthPoints()) / character->GetMaxHealthPoints());
		std::cout << " " << character->GetHealthPoints() << " / " << character->GetMaxHealthPoints() << std::endl;
		std::cout << "Attack power: " << character->GetAttackPower() << std::endl;
	}

	Console::DrawSeparator(rowSize * 4 + 1);
}

void Console::DrawGridHorizontalBorder(int gridWidth, bool bAtExtremity)
{
	SetConsoleColor(0);
	std::cout << "+";
	if (!bAtExtremity)
	{
		SetConsoleColor(8);
	}
	for (int i = 0; i < gridWidth; ++i)
	{
		if (!bAtExtremity && i == gridWidth - 1)
		{
			std::cout << "---";
			SetConsoleColor(0);
			std::cout << "+";
			continue;
		}
		std::cout << "---+";
	}
	std::cout << std::endl;
}

void Console::DrawSeparator(int size)
{
	std::cout << std::string(size, '_') << std::endl;
}

void Console::DrawContextualInputs()
{
	std::vector<std::string> inputs;
	if (I(Game)->GetLevel().GetPlayer()->CanAttack())
	{
		inputs.emplace_back("[Enter] Attack");
	}

	inputs.emplace_back("[Space] End round");

	for (auto it = inputs.begin(); it != inputs.end(); ++it)
	{
		std::cout << *it;
		if (it + 1 != inputs.end())
		{
			std::cout << " | ";
		}
	}
	std::cout << std::endl;
}

void Console::DrawMessage(const std::string& message)
{
	Console::SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_RED);
	std::cout << message;
	Console::SetConsoleColor(0);
}

void Console::DrawScreenMessage(const std::string& message, int gridWidth, int color)
{
	gridWidth = gridWidth * 4 + 1;
	Console::ClearConsole();
	Console::SetConsoleColor(color);
	Console::DrawSeparator(gridWidth);
	std::cout << std::string(gridWidth, ' ') << std::endl;
	std::cout << 
		std::string((gridWidth - message.size()) / 2, ' ') << 
		message << 
		std::string(static_cast<int>(Utilities::Round((gridWidth - message.size()) / 2.f)), ' ') << 
		std::endl;
	Console::DrawSeparator(gridWidth);
	std::cout << std::string(gridWidth, ' ') << std::endl;
	Console::SetConsoleColor(0);
}