#pragma once
#include "GameNode.h"
class HPBar :
	public GameNode
{
private:
	Image* _image;
	Image* _backImage;

	float* _x;
	float* _y;

	float _diffX;
	float _diffY;

	int* _hp;
	int _maxHp;

public:
	HPBar();
	~HPBar();

	virtual HRESULT initialize(Image* image, Image* backImage, float* x, float* y, int* hp, int maxHp, float dx = 0, float dy = 0);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setPositionP(float* x, float* y){ _x = x; _y = y; }
	void setDiff(float x, float y){ _diffX = x; _diffY = y; }
	void setHpInfo(int* hp, int maxHp){ _hp = hp; _maxHp = maxHp; }
};

