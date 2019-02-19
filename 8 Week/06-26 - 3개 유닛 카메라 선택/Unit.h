#pragma once
#include "GameObject.h"
#include "ProgressBar.h"

class Unit : public GameObject
{
protected:
	SpriteImage* _image;
	CheckTimer* _walkTimer;
	int _walkTime;

	float _maxHP;
	float _HP;
	float _maxMP;
	float _MP;

	float _maxSpeed;
	float _viewAccel;

	ProgressBar* _hpBar;
	ProgressBar* _mpBar;

	char* _unitName;
public:
	Unit();
	~Unit();

	virtual HRESULT initialize(SpriteImage* image, float centerX, float centerY, int width, int height, float angleD, float speed);
	virtual HRESULT initialize(float x, float y, float angleD, float speed){ return S_OK; }
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC);

	virtual void move();
	virtual void draw(HDC);

	virtual void frame();

	float getMaxHP(){ return _maxHP; }
	float getHP(){ return _HP; }
	float getMaxMP(){ return _maxMP; }
	float getMP(){ return _MP; }
	float getMaxSpeed(){ return _maxSpeed; }
	float getViewAccel(){ return _viewAccel; }

	void setMaxHP(float maxHP){ _maxHP = maxHP; }
	void setHP(float HP){ _HP = HP; }
	void setMaxMP(float maxMP){ _maxMP = maxMP; }
	void setMP(float MP){ _MP = MP; }
	void setMaxSpeed(float maxSpeed){ _maxSpeed = maxSpeed; }
	void setViewAccel(float viewAccel){ _viewAccel = viewAccel; }

	char* getUnitName(){ return _unitName; }
};

