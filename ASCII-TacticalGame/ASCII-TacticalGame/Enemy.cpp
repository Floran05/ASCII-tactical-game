#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
	mMaxRange = 1;
	mIsEnemy == true;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	I(Game)->GetLevel()->SetContextualMessage("Au tour de " + std::to_string(GetId()));
	I(Game)->Render();
	Sleep(3000);
}
