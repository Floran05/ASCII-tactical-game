#include "Enemy.h"
#include"Player.h"
#include <iostream>

Enemy::Enemy()
{
	mMaxRange = 1;
	mIsEnemy = true;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	I(Game)->Render();
	Sleep(1500);
}

void Enemy::GetEnemyNearby(Coordinates position)
{
	mCurrentTarget = TGetEnemyNearby<Player>(position);
}