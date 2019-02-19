#pragma once
#include "GameNode.h"
class HiddenSearch :
	public GameNode
{
private:
	typedef struct tagHSRect
	{
		float left, top, right, bottom;
		bool find;
	}HSRect;

	Image* _oImage;
	Image* _mImage;
	Image* _ok;

	vector<HSRect> _vRc;
	vector<HSRect>::iterator _viRc;

	int _time;
	int _maxTime;
public:
	HiddenSearch();
	~HiddenSearch();

	virtual HRESULT initialize(Image* original, Image* modify, vector<RECT> vRc, Image* ok);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	bool isClear();
	bool isGameOver();
};

