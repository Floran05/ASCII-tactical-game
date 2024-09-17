#pragma once

#include "GameObject.h"

class Character : public GameObject
{
public:

	Character();
	virtual ~Character();

protected:

	int mHealthPoint;
	int mAttackPower;
	int mMaxRange;
	Coordinates mRoundPosition;

public:

	virtual void Move(int x, int y);
	virtual bool CanAttack();
	virtual bool ApplyDamage(Character* target);

	virtual void SetRoundPosition(Coordinates position) { mRoundPosition = position; }
	virtual void SetRoundPosition(int x, int y) { mRoundPosition = Coordinates(x, y); }

	int GetHealthPoints() const { return mHealthPoint; }
	int GetAttackPower() const { return mAttackPower; }
	int GetMaxRange() const { return mMaxRange; }
	Coordinates GetRoundPosition() const { return mRoundPosition; }

};