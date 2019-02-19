#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Bullet.h"
#include "Timer.h"

class PlayerManager : public GameNode
{
private:
	Player* _player;
	Bullet* _bullet;
	Bullet* _missile;

	Timer* _bulletTimer;
	Timer* _missileTimer;
public:
	PlayerManager();
	virtual ~PlayerManager();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	Player* getPlayer(){ return _player; }

};

