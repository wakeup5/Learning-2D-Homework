#pragma once
#include "GameNode.h"

#define GAME_WIDTH 4
#define GAME_HEIGHT 2
#define GAME_LENGTH GAME_WIDTH * GAME_HEIGHT

using namespace std;

class GameStudy :
	public GameNode
{
private:
	RECT _rect[GAME_LENGTH];
	int _select;
	bool _isOpen = false;
	int _offTime;
	int _score;
	bool _isClick = false;
public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

