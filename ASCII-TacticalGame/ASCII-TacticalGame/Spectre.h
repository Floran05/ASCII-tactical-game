#pragma once

#include "Enemy.h"

class Spectre : public Enemy
{
public:
	Spectre();
	virtual ~Spectre();

	void Update();
	void OnKill(Character* initiator);
	
};

