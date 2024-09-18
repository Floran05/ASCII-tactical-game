#include "Player.h"
#include "Game.h"
#include "Controller.h"
#include "Enemy.h"
#include<iostream>
#include <Windows.h>
Player::Player()
	: mHisTurn(false)
{
	mSymbol = '@';
	mMaxRange = 3;
	mHealthPoint = 5;
	mAttackPower = 2;
	mMaxHealthPoint = mHealthPoint;
}

Player::~Player()
{
}

void Player::Update()
{
	if (!mHisTurn)
	{
		I(Game)->GetLevel()->SetContextualMessage("A ton tour !");
		mHisTurn = true;
		I(Game)->Render();
	}

	int key = I(Game)->GetController()->WaitForKey();
	bool bUselessMoveKey = TryMove(key) == false;
	bool bUselessActionKey = false;

	GetEnemyNearby(mPosition);
	switch (key)
	{
	case VK_SPACE:
		mHisTurn = false;
		mRoundPosition = mPosition;
		break;
	case VK_RETURN:
		mHisTurn = false;
		ApplyDamage(GetCurrentTarget());
		break;
	default:
		bUselessActionKey = true;
		break;
	}

	if (mHisTurn)
	{
		if (!bUselessMoveKey || !bUselessActionKey)
		{
			I(Game)->GetLevel()->SetContextualMessage("");
			I(Game)->Render();
		}
		Update();
	}
}

bool Player::TryMove(int key)
{
	Coordinates pos = GetPosition();
	bool bHasMoved = false;
	switch (key)
	{
	case VK_UP:
		bHasMoved = Move(-1, 0);
		break;
	case VK_DOWN:
		bHasMoved = Move(1, 0);
		break;
	case VK_RIGHT:
		bHasMoved = Move(0, 1);
		break;
	case VK_LEFT:
		bHasMoved = Move(0, -1);
		break;
	default:
		break;
	}

	return bHasMoved;
}

//overide this funct for enemy
void Player::GetEnemyNearby(Coordinates position)
{
	mCurrentTarget = TGetEnemyNearby<Enemy>(position);
}
