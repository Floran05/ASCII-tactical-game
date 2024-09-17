#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	virtual ~Player();
protected :
	
public:
	void Update() override;
	void GetEnemyNearby(Coordinates position) override;
};

