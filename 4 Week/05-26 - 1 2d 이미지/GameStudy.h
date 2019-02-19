#pragma once
#include "GameNode.h"
#include "Image.h"

using namespace std;

class GameStudy :
	public GameNode
{
private:
	Image *_image;

	Image *_character[10];

	Image *_sprite;
	int _timer, _spriteSpeed, _spriteView;
	int _sx, _sy, _sWidth, _sHeight;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

	void setBackBuffer();
};

