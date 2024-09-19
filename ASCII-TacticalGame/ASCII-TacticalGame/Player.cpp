#include "Player.h"

#include <iostream>
#include <Windows.h>

#include "Game.h"
#include "Controller.h"
#include "Enemy.h"

Player::Player()
	: mHisTurn(false)
{
	mSymbol = '@';
	mMaxRange = 3;
	mHealthPoint = 10;
	mAttackPower = 2;
	mMaxHealthPoint = mHealthPoint;
}

Player::~Player()
{
}

void Player::Update()
{
	int oldTargetId = GetTargetId();
	GetEnemyNearby(mPosition);
	bool bTargetHasChanged = oldTargetId != GetTargetId();

	if (!mHisTurn)
	{
		I(Game)->GetLevel().SetContextualMessage("A ton tour !");
		mHisTurn = true;
		I(Game)->Render();
	}
	else if (bTargetHasChanged)
	{
		I(Game)->Render();
	}

	int key = I(Game)->GetController().WaitForKey();
	bool bHasMoved = TryMove(key);
	bool bUselessActionKey = false;
	switch (key)
	{
	case VK_SPACE:
		mHisTurn = false;
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
		if (!bUselessActionKey || bHasMoved)
		{
			I(Game)->GetLevel().SetContextualMessage("");
			I(Game)->Render();
		}
		Update();
	}
	else
	{
		mRoundPosition = mPosition;
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

void Player::OnKill(Character* instigator)
{
	I(Game)->GameOver();
}

void Player::GetEnemyNearby(Coordinates position)
{
	mCurrentTarget = TGetEnemyNearby<Enemy>(position);
}
