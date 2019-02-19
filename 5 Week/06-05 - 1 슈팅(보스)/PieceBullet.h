#pragma once
#include "Bullet.h"
class PieceBullet :
	public Bullet
{
private:
	VPBullet _vMB;
	VIPBullet _viMB;

	Image* _bImage;
	int _pFrameCol;
	int _pFrameRow;
public:
	PieceBullet();
	~PieceBullet();

	virtual HRESULT initialize(int max, float range, int damage, Image* mImage, Image* image, int mFrameCol, int mFrameRow, int pFrameCol, int pFrameRow);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void fire(float startX, float startY, float angleR, float speed);

	virtual void popBullet();
};

