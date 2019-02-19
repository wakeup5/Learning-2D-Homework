#include "stdafx.h"
#include "SpriteImage.h"


SpriteImage::SpriteImage()
{
	_currentFrameCol = 0;
	_currentFrameRow = 0;
	_maxFrameCol = 0;
	_maxFrameRow = 0;
	_frameWidth = 0;
	_frameHeight = 0;
}

SpriteImage::~SpriteImage()
{

}

HRESULT SpriteImage::initialize(Image* image, int frameColumn, int frameRow)
{
	_image = image;

	_centerX = _image->getX();
	_centerY = _image->getY();

	_maxFrameCol = frameColumn - 1;
	_maxFrameRow = frameRow - 1;

	_frameWidth = _image->getWidth() / frameColumn;
	_frameHeight = _image->getHeight() / frameRow;

	setBoundingBox();

	return S_OK;
}

//ÇÁ·¹ÀÓ ·»´õ
void SpriteImage::render(HDC hdc, BYTE alpha)
{
	SpriteImage::render(hdc, _centerX - _frameWidth / 2, _centerY - _frameHeight / 2, alpha);
}

void SpriteImage::render(HDC hdc, float destX, float destY, BYTE alpha)
{
	_image->render(hdc, destX, destY, _currentFrameCol * _frameWidth, _currentFrameRow * _frameHeight, _frameWidth, _frameHeight, alpha);
}

void SpriteImage::nextFrameX()
{
	if (_currentFrameCol++ >= _maxFrameCol)
	{
		_currentFrameCol = 0;
	}
}
void SpriteImage::nextFrameY()
{
	if (_currentFrameRow++ >= _maxFrameRow)
	{
		_currentFrameRow = 0;
	}
}

void SpriteImage::prevFrameX()
{
	if (_currentFrameCol++ < 0)
	{
		_currentFrameCol = _maxFrameCol;
	}
}
void SpriteImage::prevFrameY()
{
	if (_currentFrameRow++ < 0)
	{
		_currentFrameRow = _maxFrameRow;
	}
}

void SpriteImage::nextFrame()
{
	nextFrameX();
	if (_currentFrameCol >= _maxFrameCol)
	{
		nextFrameY();
	}
}
void SpriteImage::prevFrame()
{
	prevFrameX();
	if (_currentFrameCol < 0)
	{
		prevFrameY();
	}
}


void SpriteImage::nextFrameX(float mSecond)
{
	float tick = GetTickCount();
	if (mSecond + _time <= tick)
	{
		_time = tick;
		nextFrameX();
	}
}
void SpriteImage::nextFrameY(float mSecond)
{
	float tick = GetTickCount();
	if (mSecond + _time <= tick)
	{
		_time = tick;
		nextFrameY();
	}
}

void SpriteImage::prevFrameX(float mSecond)
{
	float tick = GetTickCount();
	if (mSecond + _time <= tick)
	{
		_time = tick;
		prevFrameX();
	}
}
void SpriteImage::prevFrameY(float mSecond)
{
	float tick = GetTickCount();
	if (mSecond + _time <= tick)
	{
		_time = tick;
		prevFrameY();
	}
}

void SpriteImage::nextFrame(float mSecond)
{
	float tick = GetTickCount();
	if (mSecond + _time <= tick)
	{
		_time = tick;
		nextFrame();
	}
}
void SpriteImage::prevFrame(float mSecond)
{
	float tick = GetTickCount();
	if (mSecond + _time <= tick)
	{
		_time = tick;
		nextFrame();
	}
}