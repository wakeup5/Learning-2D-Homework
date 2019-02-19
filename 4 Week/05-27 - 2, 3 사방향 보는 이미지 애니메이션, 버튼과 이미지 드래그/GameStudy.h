#pragma once
#include "GameNode.h"
#include "Image.h"

using namespace std;

enum VIEW_DIRECTION
{
	VIEW_LEFT = 1,
	VIEW_RIGHT = 2,
	VIEW_FRONT = 0,
	VIEW_BACK = 3
};

class GameStudy :
	public GameNode
{
private:
	Image *_background;
	Image *_sprite;
	VIEW_DIRECTION _view;
	RECT _spriteRect;
	bool _isSpriteClick;
	int cx, cy;

	int _timer, _delay, _spriteNum;
	bool _backCount = false;

	Image *_button;
	RECT _buttonRect;
	bool _isButtonClick;

	Image *_cursor;
	
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

};

