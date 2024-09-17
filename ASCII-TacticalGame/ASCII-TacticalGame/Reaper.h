#pragma once

#include "Enemy.h"

class Reaper : public Enemy
{
public:
	Reaper();
	virtual ~Reaper();

	void Update();
	void OnKill(Character* initiator);
};

