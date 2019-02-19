#pragma once
#include "Image.h"
class SpriteImage :	public Image
{
private:
	int _currentFrameCol;
	int _currentFrameRow;
	int _maxFrameCol;
	int _maxFrameRow;
	int _frameWidth;
	int _frameHeight;

	int _frameNum;

	void setBoundingBox()
	{
		_imageScale = makeRectCenter(_centerX, _centerY, _frameWidth, _frameHeight);
	}
public:
	SpriteImage();
	virtual ~SpriteImage();

	//ÇÁ·¹ÀÓ °ü·Ã
	//Æø ³ôÀÌ¿Í Çà¿­ °¹¼ö
	HRESULT initialize(const char* fileName, int width, int height, int frameColumn, int frameRow, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//Æø ³ôÀÌ, Áß½É ÁÂÇ¥, Çà¿­ °¹¼ö
	HRESULT initialize(const char* fileName, float centerX, float centerY, int width, int height, int frameColumn, int frameRow, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//ÇÁ·¹ÀÓ ·»´õ
	virtual void render(HDC hdc, BYTE alpha = 255);
	virtual void render(HDC hdc, float destX, float destY, BYTE alpha = 255);

	inline void setFrameX(int frameX)
	{
		if (frameX > _maxFrameCol)
		{
			_currentFrameCol = _maxFrameCol;
		}
		else if (frameX < 0)
		{
			_currentFrameCol = 0;
		}
		else
		{
			_currentFrameCol = frameX;
		}
	}
	inline void setFrameY(int frameY)
	{
		if (frameY > _maxFrameRow)
		{
			_currentFrameRow = _maxFrameRow;
		}
		else if (frameY < 0)
		{
			_currentFrameRow = 0;
		}
		else
		{
			_currentFrameRow = frameY;
		}
	}

	inline int getMaxFrameX(){ return _maxFrameCol; }
	inline int getMaxFrameY(){ return _maxFrameRow; }

	inline int getFrameX(){ return _currentFrameCol; }
	inline int getFrameY(){ return _currentFrameRow; }

	inline int getFrameWidth(){ return _frameWidth; }
	inline int getFrameHeight(){ return _frameHeight; }
};

