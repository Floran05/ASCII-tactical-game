#include "Character.h"

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
}

bool Character::CanAttack()
{
	return false;
}

bool Character::ApplyDamage(Character* target)
{
	return false;
}
