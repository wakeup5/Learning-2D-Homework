#pragma once
#include "GameNode.h"
#include "HPBar.h"

class Player : public GameObject
{
private:
	Image* _image;
	SpriteImage* _boostImage;

	HPBar _hpBar;
	
	int _hp;
	int _maxHp;
public:
	Player();
	virtual ~Player();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();

	void setHp(int hp){ _hp = hp; }
	int getHp(){ return _hp; }
};

