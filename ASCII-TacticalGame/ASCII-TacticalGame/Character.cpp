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
	, mCurrentTarget(nullptr)
{
}

Character::~Character()
{
}

bool Character::Move(int x, int y)
{	
	Coordinates oldPosition = GetPosition();
	Coordinates newPosition = Coordinates(oldPosition.x+x,oldPosition.y+y);
	Coordinates GridSize = I(Game)->GetLevel().GetGridSize();

	if (Utilities::ManhattanDistance(newPosition.x, newPosition.y, mRoundPosition.x, mRoundPosition.y) > mMaxRange) {
		return false;
	}
	if (!I(Game)->GetLevel().IsCellEmpty(newPosition))
		return false;
	if (newPosition.x > GridSize.x-1 || newPosition.x < 0 ) {
		return false;
	}
	
	if (newPosition.y > GridSize.y-1 || newPosition.y < 0 ) {
		return false;
	}
	mPosition = newPosition;
	if (oldPosition.x != newPosition.x || oldPosition.y != newPosition.y)
	{
		I(Game)->GetLevel().MoveGameObjectInGrid(oldPosition, newPosition);
		return true;
	}

	return false;
}

bool Character::CanAttack()
{
	return mIsAlive && mCurrentTarget != nullptr;	
}

void Character::ApplyDamage(Character* target)
{
	if (target == nullptr || !target->IsAlive())
		return;
	target->SetHealthPoint(target->GetHealthPoints() - mAttackPower);
	target->AnyDamage(this);
	if (target->GetHealthPoints() <= 0) {
		target->Kill();
		target->OnKill(this);
		mCurrentTarget = nullptr;
	}
}

void Character::AnyDamage(Character* initiator)
{

}

void Character::OnKill(Character* initiator)
{
}

int Character::GetTargetId() const
{
	return GetCurrentTarget() != nullptr ? GetCurrentTarget()->GetId() : -1;
}

void Character::GetEnemyNearby(Coordinates position)
{

}
