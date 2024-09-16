#pragma once

struct Coordinates
{
	Coordinates(int X = 0, int Y = 0)
		: x(X)
		, y(Y)
	{}
	virtual ~Coordinates(){}

	int x;
	int y;
};

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

private:

	Coordinates mPosition;
	char mSymbol;

};

