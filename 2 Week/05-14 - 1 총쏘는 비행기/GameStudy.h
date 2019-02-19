#pragma once
#include "GameNode.h"

#define SPEED 5

#define MAX_BULLET 10
#define BULLET_SPEED 10
#define BULLET_COOLTIME 100 //ms

using namespace std;

class GameStudy :
	public GameNode
{
private:

	//RECT _gamePad;
	POINT _player;
	const int _speed		= SPEED;

	const int _maxBullets	= MAX_BULLET;
	const int _bulletSpeed	= BULLET_SPEED;
	int _coolTime			= BULLET_COOLTIME;
	POINT *_bullets[MAX_BULLET];
	//vector<POINT> _bullets;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	//virtual LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);

	GameStudy(){}
	virtual ~GameStudy(){}
};

