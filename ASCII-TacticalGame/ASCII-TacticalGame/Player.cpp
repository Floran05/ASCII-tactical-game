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
	bool bUselessKey = false;

	GetEnemyNearby(mPosition);
	switch (key)
	{
	case VK_UP:
		Move(-1, 0);
		break;
	case VK_DOWN:
		Move(1, 0);
		break;
	case VK_RIGHT:
		Move(0, 1);
		break;
	case VK_LEFT:
		Move(0, -1);
		break;
	case VK_SPACE:
		mHisTurn = false;
		mRoundPosition = mPosition;
		break;
	case VK_RETURN:
		if (GetCurrentTarget() != nullptr)
		{
			// In apply damage => Check if target is not nullptr
			ApplyDamage(GetCurrentTarget());
		}
		break;
	default:
		bUselessKey = true;
		break;
	}

	if (mHisTurn)
	{
		if (!bUselessKey)
		{
			I(Game)->GetLevel()->SetContextualMessage("");
			I(Game)->Render();
		}
		Update();
	}
}

//overide this funct for enemy
void Player::GetEnemyNearby(Coordinates position)
{
	mCurrentTarget = TGetEnemyNearby<Enemy>(position);
}
