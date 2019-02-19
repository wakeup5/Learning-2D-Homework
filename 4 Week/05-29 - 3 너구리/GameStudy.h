#pragma once
#include "GameNode.h"

class GameStudy :
	public GameNode
{
private:
	enum OBJECT_TYPE
	{
		TYPE_NONE,
		TYPE_FLOOR,
		TYPE_FLOOR_LADDER,
		TYPE_LADDER,
		TYPE_FRUIT,
		TYPE_THORN,
		TYPE_MONSTER
	};
	struct Block
	{
		GameObject object;
		OBJECT_TYPE type;
	};
	GameObject _player;

	Block _block[28 * 20];

	bool _isDead;
	bool _isJump;
	bool _isBigJump;

	bool _isLeft;
public:
	GameStudy(){}
	virtual ~GameStudy(){}

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void gameInit();

	void playerMove();
};
