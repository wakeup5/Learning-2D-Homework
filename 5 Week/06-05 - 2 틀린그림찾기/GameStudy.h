#pragma once
#include "GameNode.h"
#include "HiddenSearch.h"

class GameStudy :
	public GameNode
{
private:
	HiddenSearch* _hs;

	int _stage;

	int _time;
	int _clearTime;
	bool _isGameOver;
	int _gameTime;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void init1();
	void init2();
	void init3();
};
