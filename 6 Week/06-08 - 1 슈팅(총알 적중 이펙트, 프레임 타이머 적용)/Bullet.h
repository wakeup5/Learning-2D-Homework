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

		int _damage;
	public:
		BulletObject(){}
		virtual ~BulletObject(){}

		virtual HRESULT initialize(float startX, float startY, SpriteImage* image);
		virtual void release();
		virtual void update();
		virtual void render();

		float getStartX() { return _startX; }
		float getStartY() { return _startY; }

		int getDamage(){ return _damage; }
		void setDamage(int damage){ _damage = damage; }
	};

	typedef std::vector<BulletObject*> VPBullet;
	typedef std::vector<BulletObject*>::iterator VIPBullet;

protected:
	VPBullet _vBullet;
	VIPBullet _viBullet;

	int _max;
	float _range;
	int _damage;

	Image* _image;

	int _frameCol;
	int _frameRow;
public:
	Bullet();
	~Bullet();

	virtual HRESULT initialize(int max, float range, int damage, Image* image, int frameCol, int frameRow);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void fire(float startX, float startY, float angleR, float speed);

	VPBullet* getBullets(){ return &_vBullet; }

	//총알과 오브젝트 충돌처리 함수
	template < typename T >
	static bool collitionCheck(GameObject* object, Bullet::VPBullet* bullet, std::function<void(T*, Bullet::BulletObject*)> callback)
	{
		VIPBullet viBullet;
		RECT r;
		bool result = false;

		if (object == NULL) return result;

		for (viBullet = bullet->begin(); viBullet != bullet->end();)
		{
			if (IntersectRect(&r, &object->getRect(), &(*viBullet)->getRect()))
			{
				if (callback != NULL) callback(static_cast<T*>(object), (*viBullet));
				viBullet = bullet->erase(viBullet);
				result = true;
			}
			else
			{
				viBullet++;
			}
		}

		return result;
	}
};

