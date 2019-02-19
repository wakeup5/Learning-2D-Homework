#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Block.h"

class GameStudy :
	public GameNode
{
private:
	Player _player;
	GameObject _queen;

	std::vector<Block*> _block;

	bool _isLeft;
	bool _isRight;

	bool _isGameWin;
	bool _isGameLose;

public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

	void stage1();
	void stage2();
	void stage3();

	void releaseBlock();

	void playerCollition();
};
