#pragma once
#include "GameNode.h"

#define GAME_WIDTH 10
#define GAME_HEIGHT 2

#define GAME_LENGTH GAME_WIDTH * GAME_HEIGHT

using namespace std;

class GameStudy :
	public GameNode
{
private:
	int _nums[GAME_LENGTH];
	RECT _rect[GAME_LENGTH];
	bool _isClicks[GAME_LENGTH];
	int _selectNum;
	bool _gameover = false;

public:
	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	GameStudy(){}
	virtual ~GameStudy(){}
};

