#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
private:
	bool _isLive = false;
	int _speed = 10;
public:
	Enemy();
	~Enemy();

	void setIsLive(bool i){ _isLive = i; }
	bool getIsLive(){ return _isLive; }

	void setSpeed(int speed){ _speed = speed; }
	int getSpeed(){ return _speed; }
};

