#pragma once
#include "Missile.h"
#include "Enemy.h"

class GuideMissile :
	public Missile
{
private:
	Enemy* _enemy;
public:
	GuideMissile();
	~GuideMissile();

	void setEnemy(Enemy* e){ _enemy = e; }
	void guideMove();
};

