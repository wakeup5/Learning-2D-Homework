#pragma once
#include "GameNode.h"

class Bullet : public GameNode
{
public:
	class BulletObject : public GameObject
	{
	private:
		SpriteImage* _image;

		float _startX;
		float _startY;

	public:
		BulletObject(){}
		virtual ~BulletObject(){}

		virtual HRESULT initialize(float startX, float startY, SpriteImage* image);
		virtual void release();
		virtual void update();
		virtual void render();

		float getStartX() { return _startX; }
		float getStartY() { return _startY; }
	};

	typedef std::vector<BulletObject*> VPBullet;
	typedef std::vector<BulletObject*>::iterator VIPBullet;

private:
	VPBullet _vBullet;
	VIPBullet _viBullet;

	int _max;
	float _range;

	Image* _image;

	int _frameCol;
	int _frameRow;
public:
	Bullet();
	~Bullet();

	virtual HRESULT initialize(int max, float range, Image* image, int frameCol, int frameRow);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void fire(float startX, float startY, float angleR, float speed);

	VPBullet* getBullets(){ return &_vBullet; }
};

