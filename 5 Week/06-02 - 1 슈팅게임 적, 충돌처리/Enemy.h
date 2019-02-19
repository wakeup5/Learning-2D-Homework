#pragma once
#include "GameNode.h"
#include "Bullet.h"
class Enemy :
	public GameNode
{
public:
	class Object : public GameObject
	{
	public:
		SpriteImage* image;
		Bullet* bullet;
	};

	typedef std::vector < Object* > VPEnemy;
	typedef std::vector < Object* >::iterator VIPEnemy;

private:
	VPEnemy _vEnemy;
	std::vector<Object*>::iterator _viEnemy;

public:
	Enemy();
	~Enemy();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	virtual void move();
	virtual void draw();

	std::vector<Object*>* getEnemys(){ return &_vEnemy; }
};

