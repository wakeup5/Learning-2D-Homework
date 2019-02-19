#pragma once
#include "GameNode.h"
#include "Bullet.h"

#define MISSILE_SPEED 10
#define MISSILE_SIZE 50
#define MAX_MISSILE 16

using namespace std;

class GameStudy :
	public GameNode
{
private:
	typedef struct tagCannon
	{
		POINT center;
		POINT cannonEnd;
		int radius;
		float angle;
		float angleRadian;
		int length;
	} Cannon;

	typedef struct tagMissile
	{
		double px, py;
		float angleRadian;
		float angle;
		int speed;
		int radius;
		bool isFire;
	} Missile;

	Cannon _cannon;
	Missile _missiles[MAX_MISSILE];

    Bullet _bullet[MAX_MISSILE];

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

    float getAngle(float x1, float y1, float x2, float y2);

	GameStudy(){}
	virtual ~GameStudy(){}
};

