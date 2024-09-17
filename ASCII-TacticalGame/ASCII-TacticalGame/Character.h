#pragma once

#include "GameObject.h"
#include"Game.h"
#include"Level.h"
class Enemy;
class Character : public GameObject
{
public:

	Character();
	virtual ~Character();

protected:

	int mHealthPoint;
	int mMaxHealthPoint;
	int mAttackPower;
	int mMaxRange;
	Character* mCurrentTarget;
	Coordinates mRoundPosition;

public:
	virtual void Move(int x, int y);
	virtual bool CanAttack();
	virtual void ApplyDamage(Character* target);
	virtual void AnyDamage(Character* initiator);
	virtual void SetRoundPosition(Coordinates position) { mRoundPosition = position; }
	virtual void SetRoundPosition(int x, int y) { mRoundPosition = Coordinates(x, y); }
	virtual void OnKill(Character* initiator);
	void SetHealthPoint(int Health) { mHealthPoint = Health; }
	void SetAttackPower(int AttackPower) { mAttackPower = AttackPower; }

	int GetHealthPoints() const { return mHealthPoint; }
	int GetMaxHealthPoints() const { return mMaxHealthPoint; }
	int GetAttackPower() const { return mAttackPower; }
	int GetMaxRange() const { return mMaxRange; }
	Character* GetCurrentTarget() const { return mCurrentTarget; }
	Coordinates GetRoundPosition() const { return mRoundPosition; }

	virtual void GetEnemyNearby(Coordinates position);
	template<typename T> T* TGetEnemyNearby(Coordinates position )
	{
		T* enemy = I(Game)->GetLevel()->GetTargetInCell<T>(Coordinates(position.x+1,position.y));
		if (enemy != nullptr)
			return enemy;
		enemy = I(Game)->GetLevel()->GetTargetInCell<T>(Coordinates(position.x-1,position.y));
		if (enemy != nullptr)
			return enemy;
		enemy = I(Game)->GetLevel()->GetTargetInCell<T>(Coordinates(position.x,position.y+1));
		if (enemy != nullptr)
			return enemy;
		enemy = I(Game)->GetLevel()->GetTargetInCell<T>(Coordinates(position.x,position.y-1));
		if (enemy != nullptr)
			return enemy;
		return nullptr;
	}
};