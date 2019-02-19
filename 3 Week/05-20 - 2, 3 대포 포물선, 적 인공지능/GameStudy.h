#pragma once
#define MAX_BULLET 10
#define MAX_POWER 20
#define GRAVITY_ACCEL 0.2

#define RADER_RANGE 500

#include "GameNode.h"
#include "Cannon.h"
#include "Bullet.h"

using namespace std;

class GameStudy :
	public GameNode
{
private:
    Cannon _cannon;
    Bullet _bullet[MAX_BULLET];
    float _bulletEnd[MAX_BULLET];

    Cannon _enemy;

    float _power;
    float _shootPower;

    float _firstSpeedY;

    float _enemyAngle = 110;
    float _enemyPower;
    Bullet _enemyBullet;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

