#include "Character.h"

#include <iostream>

#include"Game.h"
#include"Level.h"
#include"Utilities.h"

Character::Character()
	: mHealthPoint(0)
	, mMaxHealthPoint(0)
	, mAttackPower(0)
	, mMaxRange(0)
	, mIsAlive(true)
	, mCurrentTarget(nullptr)
{
}

Character::~Character()
{
}

void Character::Move(int x, int y)
{	
	Coordinates oldPosition = GetPosition();
	Coordinates newPosition = Coordinates(oldPosition.x+x,oldPosition.y+y);
	Coordinates GridSize = I(Game)->GetLevel()->GetGridSize();

	if (Utilities::ManhattanDistance(newPosition.x, newPosition.y, mRoundPosition.x, mRoundPosition.y) > mMaxRange) {
		return;
	}
	if (!I(Game)->GetLevel()->IsCellEmpty(newPosition))
		return;
	if (newPosition.x > GridSize.x-1 && newPosition.x < 0 ) {
		return;
	}
	
	if (newPosition.y > GridSize.y-1 && newPosition.y < 0 ) {
		return;
	}
	mPosition = newPosition;
	if (oldPosition.x != newPosition.x || oldPosition.y != newPosition.y)
	{
		I(Game)->GetLevel()->MoveGameObjectInGrid(oldPosition, newPosition);
		I(Game)->RequestRender();
	}
}

bool Character::CanAttack()
{
	return mIsAlive && mCurrentTarget != nullptr;	
}

void Character::ApplyDamage(Character* target)
{
	target->SetHealthPoint(target->GetHealthPoints() - mAttackPower);
	if (target->GetHealthPoints() <= 0) {
		target->Kill();
	}
}

void Character::GetEnemyNearby(Coordinates position)
{
}
