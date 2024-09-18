#pragma once

#include <Windows.h>
#include <string>

class Character;

class Console
{
public:
	Console();
	virtual ~Console();

public:

	static void ClearConsole();
	static void SetConsoleColor(int color);

	static void DrawHealthBar(int size, float percent);
	static void DrawCharacterStats(Character* character, int rowSize);

	static void DrawGridHorizontalBorder(int gridWidth);
	static void DrawSeparator(int size);
	
	static void DrawContextualInputs();
	static void DrawMessage(const std::string& message);

	static void DrawGameOverScreen(int gridWidth);
	static void DrawOnWinScreen(int gridWidth);

};

