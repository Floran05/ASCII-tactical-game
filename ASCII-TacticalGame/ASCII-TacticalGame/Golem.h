#pragma once

#include "Enemy.h"

class Golem : public Enemy
{
public:
	Golem();
	virtual ~Golem();

	void OnKill(Character* initiator);
	void AnyDamage(Character* initiator);
	void Update();
};

