#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
	mMaxRange = 1;

}

Enemy::~Enemy()
{
}

<<<<<<< HEAD
void Enemy::Update()
{
	I(Game)->GetLevel()->SetContextualMessage("Au tour de " + std::to_string(GetId()));
	I(Game)->Render();
	Sleep(3000);
}
=======

>>>>>>> 4dfcf3f4fe6c3b6e486d5853edee4ddf06ba7f64
