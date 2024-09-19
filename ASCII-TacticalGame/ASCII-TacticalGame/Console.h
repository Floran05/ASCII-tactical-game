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

	static void DrawGridHorizontalBorder(int gridWidth, bool bAtExtremity = false);
	static void DrawSeparator(int size);
	
	static void DrawContextualInputs();
	static void DrawMessage(const std::string& message);

	static void DrawScreenMessage(const std::string& message, int gridWidth, int color = 0);

};

