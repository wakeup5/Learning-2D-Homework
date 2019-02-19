#pragma once
#include "GameObject.h"
class Block :
	public GameObject
{
private:
	bool _isGold = false;
	int _goldDelay = 50;

	int _blockKind;
public:
	Block();
	~Block();

	void setBlockKind(int i){ _blockKind = i; }
	int getBlockKind(){ return _blockKind; }
	void setGold(){ _isGold = true; }

	void update();
	void render(HDC);
};

