#include "stdafx.h"
#include "SpriteImage.h"


SpriteImage::SpriteImage() : Image()
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

//폭 높이와 행열 갯수
HRESULT SpriteImage::initialize(const char* fileName, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	return initialize(fileName, _centerX, _centerY, width, height, frameColumn, frameRow, trans, transColor);
}
//폭 높이, 중심 좌표, 행열 갯수
HRESULT SpriteImage::initialize(const char* fileName, float centerX, float centerY, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	if (FAILED(Image::initialize(fileName, centerX, centerY, width, height, trans, transColor)) || _imageInfo == NULL)
	{
		release();
		return E_FAIL;
	}
	//Image::setTransColor(trans, transColor);
	_maxFrameCol = frameColumn - 1;
	_maxFrameRow = frameRow - 1;

	_frameWidth = width / frameColumn;
	_frameHeight = height / frameRow;

	setBoundingBox();

	//이미지 리소스를 얻는데 실패하면
	if (Image::_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//프레임 렌더
void SpriteImage::render(HDC hdc, BYTE alpha)
{
	SpriteImage::render(hdc, _centerX - _frameWidth / 2, _centerY - _frameHeight / 2, alpha);
}

void SpriteImage::render(HDC hdc, float destX, float destY, BYTE alpha)
{
	Image::render(hdc, destX, destY, _currentFrameCol * _frameWidth, _currentFrameRow * _frameHeight, _frameWidth, _frameHeight, alpha);
}


void SpriteImage::nextFrameX()
{
	if (_currentFrameCol >= _maxFrameCol)
	{
		_currentFrameCol = 0;
	}
	else
	{
		_currentFrameCol++;
	}
}
void SpriteImage::nextFrameY()
{
	if (_currentFrameRow >= _maxFrameRow)
	{
		_currentFrameRow = 0;
	}
	else
	{
		_currentFrameRow++;
	}
}

void SpriteImage::prevFrameX()
{
	if (_currentFrameCol < 0)
	{
		_currentFrameCol = _maxFrameCol;
	}
	else
	{
		_currentFrameCol--;
	}
}
void SpriteImage::prevFrameY()
{
	if (_currentFrameRow < 0)
	{
		_currentFrameRow = _maxFrameRow;
	}
	else
	{
		_currentFrameRow--;
	}
}

void SpriteImage::nextFrameX(int delay)
{
	if (_time % delay == 0)
	{
		nextFrameX();
		_time = 0;
	}
	_time++;
}
void SpriteImage::nextFrameY(int delay)
{
	if (_time % delay == 0)
	{
		nextFrameY();
		_time = 0;
	}
	_time++;
}

void SpriteImage::prevFrameX(int delay)
{
	if (_time % delay == 0)
	{
		prevFrameX();
		_time = 0;
	}
	_time++;
}
void SpriteImage::prevFrameY(int delay)
{
	if (_time % delay == 0)
	{
		prevFrameY();
		_time = 0;
	}
	_time++;
}