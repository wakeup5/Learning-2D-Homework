#pragma once
#include "GameObject.h"
class Missile :
	public GameObject
{
protected:
	int _degree = 0;
	int _speed = 10;

	bool _isFire = false;

public:
	Missile();
	~Missile();

	void move();

	void setIsFire(bool b){ _isFire = b; }
	bool getIsFire(){ return _isFire; }

	void setDegree(int d){ _degree = d; }
	void setSpeed(int s){ _speed = s; }
};

