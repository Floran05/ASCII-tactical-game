#include "Spectre.h"
#include "Level.h"
#include"Player.h"
Spectre::Spectre()
{
	mSymbol = 'S';
	mHealthPoint = 2;
	mMaxHealthPoint = mHealthPoint;
	mAttackPower = 1;
	
}
Spectre::~Spectre()
{
}

void Spectre::Update()
{
	Coordinates PlayerPos = I(Game)->GetLevel()->GetPlayer()->GetPosition();
	if (mPosition.x > PlayerPos.x || mPosition.y > PlayerPos.y) {
		Move(1, 1);
	}
	else {
		Move(-1, -1);
	}

}

void Spectre::OnKill(Character* initiator) {

	initiator->SetHealthPoint(initiator->GetMaxHealthPoints());
}



