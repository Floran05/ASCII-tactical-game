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

	static int sObjectGlobalId;

	int mId;
	bool mIsAlive;
	Coordinates mPosition;
	char mSymbol;


public:

	virtual void Update();
	virtual void Render();

	virtual void SetPosition(int x, int y) { mPosition = Coordinates(x, y); }
	virtual void SetPosition(const Coordinates& coordinates) { mPosition = coordinates; }

	int GetId() const { return mId; }
	Coordinates GetPosition() const { return mPosition; }
	char GetSymbol() const { return mSymbol; }
	bool IsAlive() const { return mIsAlive; }
	
	void Kill();

};

