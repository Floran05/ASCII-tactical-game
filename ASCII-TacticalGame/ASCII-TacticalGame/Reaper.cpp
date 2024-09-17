#include "Reaper.h"
#include "Level.h"
#include"Player.h"
Reaper::Reaper()
{
	mSymbol = 'R';
	mHealthPoint = 1;
	mMaxHealthPoint = mHealthPoint;
}

Reaper::~Reaper()
{
}

void Reaper::Update()
{
	// to be reworked
	Coordinates PlayerPos = I(Game)->GetLevel()->GetPlayer()->GetPosition();
	if (mPosition.x > PlayerPos.x || mPosition.y > PlayerPos.y) {
		Move(-1, -1);
	}
	else {
		Move(1, 1);
	}
}

void Reaper::OnKill(Character* initiator)
{
	//to do 
}
