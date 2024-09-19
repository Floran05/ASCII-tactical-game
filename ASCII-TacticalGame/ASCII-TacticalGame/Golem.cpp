#include "Golem.h"
#include"Game.h"
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
	I(Game)->GetLevel().SetContextualMessage("Au tour de " + DisplayName() + " " + std::to_string(GetId()));
	GetEnemyNearby(mPosition);
	if (CanAttack()){
		ApplyDamage(mCurrentTarget);
		I(Game)->GetLevel().SetContextualMessage("Au tour de " + DisplayName() +" "+ std::to_string( GetId()) + "  | il attaque et tu perds " + std::to_string(mAttackPower) + " PV");
	}
	Enemy::Update();
}
void Golem::OnKill(Character* initiator)
{
	initiator->SetAttackPower(initiator->GetAttackPower() + mAttackPower);
}

void Golem::AnyDamage(Character* initiator)
{
	if (!initiator->IsAnEnemy() && initiator->GetAttackPower()>0) {
		srand(timeGetTime());
		mHealthPoint += rand() % initiator->GetAttackPower() ;
	}
}




