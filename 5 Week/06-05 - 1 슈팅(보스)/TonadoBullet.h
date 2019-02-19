#pragma once
#include "Bullet.h"
class TonadoBullet :
	public Bullet
{
public:
	TonadoBullet();
	~TonadoBullet();

	virtual HRESULT initialize(int max, float range, int damage, Image* image, int frameCol, int frameRow);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
};

