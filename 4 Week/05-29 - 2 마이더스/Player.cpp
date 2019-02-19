#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	_isGold = true;
}


Player::~Player()
{
}

void Player::jump()
{
	if (getSpeedY() == 0) GameObject::setSpeedY(-5);
}

void Player::gravity()
{
	setSpeedY(getSpeedY() + 0.2);
	//GameObject::move();
}