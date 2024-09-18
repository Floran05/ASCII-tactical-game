#include "Reaper.h"
#include "Level.h"
#include"Player.h"
#include"Character.h"
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

	Coordinates PlayerPos = I(Game)->GetLevel()->GetPlayer()->GetPosition();
	if (mPosition.x - PlayerPos.x > mPosition.y - PlayerPos.y ) {
		if (mPosition.x - PlayerPos.x > 0)
			Move(1, 0);
		else
			Move(-1, 0);
	}
	if (mPosition.x - PlayerPos.x < mPosition.y - PlayerPos.y) {
		if (mPosition.y - PlayerPos.y > 0)
			Move(0, 1);
		else
			Move(0, -1);
	}
	
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
