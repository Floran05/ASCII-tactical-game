#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	virtual ~Player();

protected :
	
	bool mHisTurn;

public:

	void Update() override;
	bool TryMove(int key);
	void OnKill(Character* instigator);

	void GetEnemyNearby(Coordinates position) override;
	bool IsHisTurn() const { return mHisTurn; }
};

