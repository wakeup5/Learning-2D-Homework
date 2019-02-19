#pragma once
#include "GameNode.h"
class Enemy : public GameObject
{
private:
	SpriteImage* _image;
	float _frameTime;

protected:
	int _hp;
	int _maxHp;

public:
	Enemy();
	virtual ~Enemy();

	virtual HRESULT initialize(SpriteImage* image, float frameTime);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();
	virtual void draw();

	void setHp(int hp){ _hp = hp; }
	int getHp(){ return _hp; }
};

