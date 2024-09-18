#include "Golem.h"

#include <stdlib.h>
#include<Windows.h>
Golem::Golem()
{
	mSymbol = 'G';
	mHealthPoint = 3;
	mMaxHealthPoint = mHealthPoint;
	mAttackPower = 2;
	mName = "Golem";
}

Golem::~Golem()
{
}
void Golem::Update() {
	Enemy::Update();
	GetEnemyNearby(mPosition);
	if (CanAttack())
		ApplyDamage(mCurrentTarget);
}
void Golem::OnKill(Character* initiator)
{
	initiator->SetAttackPower(initiator->GetAttackPower() + mAttackPower);
}

void Golem::AnyDamage(Character* initiator)
{
	if (!initiator->IsAnEnemy() && initiator->GetAttackPower()>0) {
		srand(timeGetTime());
		mHealthPoint += rand() % initiator->GetAttackPower() + 1;
	}
}




