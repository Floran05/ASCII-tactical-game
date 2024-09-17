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

protected:

	Coordinates mPosition;
	char mSymbol;

public:

	virtual void Update();
	virtual void Render();

	virtual void SetPosition(int x, int y) { mPosition = Coordinates(x, y); }
	virtual void SetPosition(const Coordinates& coordinates) { mPosition = coordinates; }

	Coordinates GetPosition() const { return mPosition; }
	char GetSymbol() const { return mSymbol; }

};

