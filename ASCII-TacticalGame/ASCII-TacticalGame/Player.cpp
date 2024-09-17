#include "Player.h"
#include "Game.h"
#include "Controller.h"
#include <Windows.h>
Player::Player()
{
	mSymbol = '@';
	mMaxRange = 3;
}

Player::~Player()
{
}

void Player::Update()
{
	if (I(Game)->GetController()->IsKey(VK_UP)) {
		Move(-1,0);
	}
	else if (I(Game)->GetController()->IsKey(VK_DOWN)) {
		Move(1,0);
	}
	else if (I(Game)->GetController()->IsKey(VK_RIGHT)) {
		Move(0,1);
	}
	else if (I(Game)->GetController()->IsKey(VK_LEFT)) {
		Move(0,-1);
	}
	else if (I(Game)->GetController()->IsKey(VK_SPACE)) {

	}
}
