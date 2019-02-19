#pragma once
class Bullets : public GameNode
{
private:
	class Bullet : public GameObject
	{
	private:
		SpriteImage* _image;	//x축 방향, y축 애니메이션
		void(*_moveFunc)(GameObject*);		//움직일 코드를 가지고 있는 함수포인터

		float _startX;
		float _startY;

		CheckTimer *_timer;
	public:
		Bullet(SpriteImage* image, float startX, float startY, float angle = 0.0f, float speed = 0.0f, void(*moveFunc)(GameObject*) = NULL);
		~Bullet();

		virtual void release();
		virtual void update();
		virtual void render(HDC hdc);

		float getStartX(){ return _startX; }
		float getStartY(){ return _startY; }
	};

protected:
	typedef std::list<Bullet*> BulletList;
	typedef std::list<Bullet*>::iterator BulletLIter;

	BulletList* _lBullet;
	BulletLIter _liBullet;

	SpriteImage* _bulletImage;
	float _range;
	float _max;

public:
	Bullets();
	~Bullets();

	virtual void initialize(SpriteImage* image, float range, float max);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(float startX, float startY, float angle, float speed, void(*moveFunc)(GameObject*) = NULL);
	virtual void fire(SpriteImage* image, float startX, float startY, float angle, float speed, void(*moveFunc)(GameObject*) = NULL);
	virtual void fire(Bullet* bullet);

	static Bullet* createBullet(SpriteImage*, float startX, float startY, float angle = 0.0f, float speed = 0.0f, void(*moveFunc)(GameObject*) = NULL);
};

//typedef Bullets::Bullet Bullet;