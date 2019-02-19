#pragma once
#include "GameNode.h"
#include "Sceen1.h"

class GameStudy :
	public GameNode
{
private:
	Sceen1* _s1;
	int _sceenNum;
	bool _isInit;

	int _playerNum;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void controlMessage(int message);
};
