#pragma once
#include "GameNode.h"
#include "Sceen3.h"

class Sceen1 :
	public GameNode
{
private:
	HWND _textInput;
	HWND _submit;

	int _playerNum;

	HWND _submit2;
	HWND _textInput2[10];
	Image* _image[10];
	Image* _dragImage;
	Image* _selectImage[10];
	char _playerName[10][128];

	char _errorStr[128];
	int _sceenNum;

	Sceen3* _s3;

public:
	Sceen1();
	virtual ~Sceen1();

	virtual HRESULT initialize();
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void controlMessage(int message);
};

