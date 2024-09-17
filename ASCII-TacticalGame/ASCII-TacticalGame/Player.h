#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	virtual ~Player();
protected :
	
public:
	void Update();
	void GetEnemyNearby(Coordinates position);
};

