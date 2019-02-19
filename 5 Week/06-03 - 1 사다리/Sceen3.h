#pragma once
#include "GameNode.h"
class Sceen3 :
	public GameNode
{
private:
	int _playerNum;
	Image* _selectImage[10];
	char _playerName[10][128];

	int _ladder[10][20];
	int _ladderNum[10];

	int _prevPoint[10];
	int _point[10];

	bool _isOpen;

	HWND _button;
public:
	Sceen3();
	~Sceen3();

	virtual HRESULT initialize(int playerNum);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void controlMessage(int message);

	void setGameInfo(int playerNum, Image* selectImage[10], char playerName[10][128])
	{
		_playerNum = playerNum;
		for (int i = 0; i < playerNum; i++)
		{
			_selectImage[i] = selectImage[i];
			strcpy_s(_playerName[i], strlen(playerName[i]) + 1, playerName[i]);
		}
	}
};

