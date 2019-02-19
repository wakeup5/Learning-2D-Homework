#pragma once

#include "Image.h"

class GameNode
{
private:
	Image* _backBuffer;
protected:
	Image* _mapImage;
public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT initialize(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	virtual LRESULT mainProc(HWND, UINT, WPARAM, LPARAM);

	void setBackBuffer();
	Image *getBackBuffer(){ return _backBuffer; }
};

