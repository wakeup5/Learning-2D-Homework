#pragma once
#include "Enemy.h"
#include "HPBar.h"

class HpEnemy :
	public Enemy
{
private:
	HPBar _hpBar;

public:
	HpEnemy();
	~HpEnemy();

	virtual HRESULT initialize(SpriteImage* image, float frameTime, Image* hpImage, Image* backHpImage, int maxHp);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();
	virtual void draw();

};

