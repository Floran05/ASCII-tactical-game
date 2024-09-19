#include "Reaper.h"
#include "Level.h"
#include"Player.h"
#include"Character.h"

#include <iostream>
Reaper::Reaper()
{
	mSymbol = 'R';
	mHealthPoint = 1;
	mMaxHealthPoint = mHealthPoint;
	mAttackPower = 4;
	mName = "Reaper";
}

Reaper::~Reaper()
{
}

void Reaper::Update()
{
	
	Coordinates PlayerPos = I(Game)->GetLevel().GetPlayer()->GetPosition();
	if (abs(mPosition.x - PlayerPos.x) >= abs(mPosition.y - PlayerPos.y)) {
		if (mPosition.x - PlayerPos.x > 0)
			Move(-1, 0);
		else if(mPosition.x - PlayerPos.x < 0)
			Move(1, 0);
		I(Game)->GetLevel().SetContextualMessage("Au tour de " + DisplayName()+ " il te poursuit ");
	}
	if (abs(mPosition.x - PlayerPos.x) < abs(mPosition.y - PlayerPos.y)) {
		if (mPosition.y - PlayerPos.y > 0)
			Move(0, -1);
		else if(mPosition.y - PlayerPos.y < 0)
			Move(0, 1);
		I(Game)->GetLevel().SetContextualMessage("Au tour de " + DisplayName() + " il te poursuit ");
	}
	mRoundPosition = mPosition;
	GetEnemyNearby(mPosition);
	if (CanAttack()) {
		ApplyDamage(mCurrentTarget);
		I(Game)->GetLevel().SetContextualMessage("Au tour de " + DisplayName() + " | il attaque et tu perds " + std::to_string(mAttackPower) + " PV");
	}
	Enemy::Update();
}

void Reaper::OnKill(Character* initiator)
{
	std::list<GameObject*> Entities = I(Game)->GetEntities();
	for (GameObject* i : Entities) {
		if (Character* character = dynamic_cast<Character*>(i)) {
			if (character->IsAnEnemy()) {
				ApplyDamage(character);
			}
		}
	}
}
