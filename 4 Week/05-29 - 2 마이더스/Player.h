#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
private:
	bool _isGold;
public:
	Player();
	~Player();

	void initialize()
	{
		_isGold = true;
	}

	void setNormalHand(){ _isGold = false; }
	bool isGoldHand(){ return _isGold; }

	void jump();
	void gravity();
};

