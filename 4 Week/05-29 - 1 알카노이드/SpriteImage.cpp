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


