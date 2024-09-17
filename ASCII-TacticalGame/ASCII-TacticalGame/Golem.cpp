#include "Golem.h"

#include <stdlib.h>
#include<Windows.h>
Golem::Golem()
{
	mSymbol = 'G';
	mHealthPoint = 4;
	mMaxHealthPoint = mHealthPoint;
	mAttackPower = 2;
	
}

Golem::~Golem()
{
}

void Golem::OnKill(Character* initiator)
{
	initiator->SetAttackPower(initiator->GetAttackPower() + mAttackPower);
}

void Golem::AnyDamage(Character* initiator)
{
	srand(timeGetTime());
	mHealthPoint += rand() % initiator->GetAttackPower() + 1;
}




