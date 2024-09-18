#include "Spectre.h"
#include "Level.h"
#include"Player.h"
Spectre::Spectre()
{
	mSymbol = 'S';
	mHealthPoint = 2;
	mMaxHealthPoint = mHealthPoint;
	mAttackPower = 1;
	mName = "Spectre";
}
Spectre::~Spectre()
{
}

void Spectre::Update()
{
	Enemy::Update();
	Coordinates PlayerPos = I(Game)->GetLevel()->GetPlayer()->GetPosition();
	if (mPosition.x - PlayerPos.x >= 0)
		Move(1, 0);
	else if (mPosition.x - PlayerPos.x < 0)
		Move(-1, 0);

	if (mPosition.y - PlayerPos.y >= 0)
		Move(0, 1);
	else if (mPosition.y - PlayerPos.y < 0)
		Move(0, -1);

	mRoundPosition = mPosition;
	GetEnemyNearby(mPosition);
	if (CanAttack())
		ApplyDamage(mCurrentTarget);
}

void Spectre::OnKill(Character* initiator) {

	initiator->SetHealthPoint(initiator->GetMaxHealthPoints());
}



