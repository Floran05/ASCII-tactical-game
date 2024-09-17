#include "Character.h"
#include"Game.h"
#include"Level.h"
#include"Utilities.h"
Character::Character()
	: mHealthPoint(0)
	, mAttackPower(0)
	, mMaxRange(0)
{
}

Character::~Character()
{
}

void Character::Move(int x, int y)
{	
	Coordinates GridSize = I(Game)->GetLevel()->GetGridSize();
	if (mPosition.x + x <= GridSize.x-1 && mPosition.x + x >= 0) {
		mPosition.x += x;
	}
	
	if (mPosition.y + y <= GridSize.y-1 && mPosition.y + y >= 0) {
		mPosition.y += y;
	}
	
	if (Utilities::ManhattanDistance(mPosition.x + x, mPosition.y + y, mRoundPosition.x, mRoundPosition.y) > mMaxRange) {
		return;
	}
	
}

bool Character::CanAttack()
{
	return false;
}

bool Character::ApplyDamage(Character* target)
{
	return false;
}
