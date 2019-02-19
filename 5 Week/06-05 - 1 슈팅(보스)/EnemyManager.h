#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "HpEnemy.h"

class EnemyManager :
	public GameNode
{
private:
	typedef std::vector<Enemy*> VEnemy;
	typedef std::vector<Enemy*>::iterator VIEnemy;

	VEnemy _vEnemy;
	VIEnemy _viEnemy;

	HpEnemy* _boss;

	Bullet* _bullet;
	Timer* _bulletTimer;
public:
	EnemyManager();
	~EnemyManager();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	VEnemy* getEnemys(){ return &_vEnemy; }
};

