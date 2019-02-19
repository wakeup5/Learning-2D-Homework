#pragma once
#include "GameNode.h"
#include "Missile.h"
#include "Bullet.h"
#include "Enemy.h"

class Rocket :
	public GameNode,
	public GameObject
{
private:
	Image* _image;
	SpriteImage* _boostImage;

	//GameObject _info;

	Missile* _missile;
	Bullet* _bullet;

	int _hp;
public:
	Rocket();
	virtual ~Rocket();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	void setHp(int hp){ _hp = hp; }
	int getHp(){ return _hp; }
};

