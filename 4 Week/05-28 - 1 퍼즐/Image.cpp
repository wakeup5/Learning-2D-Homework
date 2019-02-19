#include "stdafx.h"
#include "Image.h"

#pragma comment (lib, "msimg32.lib")

Image::Image()
	:_imageInfo(NULL),
	_fileName(NULL),
	_trans(NULL),
	_transColor(RGB(0, 0, 0))
{
}


Image::~Image()
{
}

HRESULT Image::initialize(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = width / 2;
	_imageInfo->centerY = height / 2;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::initialize(const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = width / 2;
	_imageInfo->centerY = height / 2;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일경로이름 복사
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = centerX;
	_imageInfo->centerY = centerY;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일경로이름 복사
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::initialize(const char* fileName, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = width / 2;
	_imageInfo->centerY = height / 2;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameColumn - 1;
	_imageInfo->maxFrameY = frameRow - 1;
	_imageInfo->frameWidth = _imageInfo->width / frameColumn;
	_imageInfo->frameHeight = _imageInfo->height / frameRow;

	//파일경로이름 복사
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}
HRESULT Image::initialize(const char* fileName, float centerX, float centerY, int width, int height, int frameColumn, int frameRow, BOOL trans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->centerX = centerX;
	_imageInfo->centerY = centerY;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameColumn - 1;
	_imageInfo->maxFrameY = frameRow - 1;
	_imageInfo->frameWidth = _imageInfo->width / frameColumn;
	_imageInfo->frameHeight = _imageInfo->height / frameRow;

	//파일경로이름 복사
	int fileNameLength = strlen(fileName);
	_fileName = new CHAR[fileNameLength + 1];
	strcpy_s(_fileName, fileNameLength + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WIN_SIZE_X;
	_blendImage->height = WIN_SIZE_Y;

	ReleaseDC(_hWnd, hdc);

	//이미지 리소스를 얻는데 실패하면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::release(void)
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_blendImage);
		SAFE_DELETE(_fileName);

		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}
}

void Image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void Image::render(HDC hdc)
{
	//투명처리를 할 경우
	if (_trans)
	{
		//gdi를 뺀 함수도 있다. 
		GdiTransparentBlt(
			hdc,		//복사할 곳 DC
			_imageInfo->centerX - _imageInfo->width / 2,		//대상 좌표 X시작점
			_imageInfo->centerY - _imageInfo->height / 2,		//대상 좌표 Y시작점
			_imageInfo->width, //이미지 폭
			_imageInfo->height, //이미지 높이
			_imageInfo->hMemDC,
			0, //복사 좌표 시작
			0, //복사 좌표 시작
			_imageInfo->width, //복사 폭
			_imageInfo->height, //폭사 높이
			_transColor	//복사에서 제외할 색상
			);
	}
	//하지 않을 경우
	else
	{
		//StrechBlt는 확대축소하여 복사 가능
		BitBlt(hdc, _imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

void Image::render(HDC hdc, int destX, int destY)
{
	//투명처리를 할 경우
	if (_trans)
	{
		//gdi를 뺀 함수도 있다. 
		GdiTransparentBlt(
			hdc,		//복사할 곳 DC
			destX,		//대상 좌표 X시작점
			destY,		//대상 좌표 Y시작점
			_imageInfo->width, //이미지 폭
			_imageInfo->height, //이미지 높이
			_imageInfo->hMemDC, 
			0, //복사 좌표 시작
			0, //복사 좌표 시작
			_imageInfo->width, //복사 폭
			_imageInfo->height, //폭사 높이
			_transColor	//복사에서 제외할 색상
			);
	}
	//하지 않을 경우
	else
	{
		//StrechBlt는 확대축소하여 복사 가능
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

void Image::render(HDC hdc, int sourX, int sourY, int width, int height)
{
	//투명처리를 할 경우
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi를 뺀 함수도 있다. 
		GdiTransparentBlt(
			hdc,		//복사할 곳 DC
			_imageInfo->centerX - width / 2,
			_imageInfo->centerY - height / 2,
			width,
			height,
			_imageInfo->hMemDC,
			sourX,
			sourY,
			width,
			height,
			_transColor	//복사에서 제외할 색상
			);
	}
	//하지 않을 경우
	else
	{
		//StrechBlt는 확대축소하여 복사 가능
		BitBlt(hdc, _imageInfo->centerX - width / 2, _imageInfo->centerY - height / 2, width, height, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height)
{
	//투명처리를 할 경우
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi를 뺀 함수도 있다. 
		GdiTransparentBlt(
			hdc,		//복사할 곳 DC
			destX,		//대상 좌표 X시작점
			destY,		//대상 좌표 Y시작점
			width,
			height,
			_imageInfo->hMemDC,
			sourX,
			sourY,
			width,
			height,
			_transColor	//복사에서 제외할 색상
			);
	}
	//하지 않을 경우
	else
	{
		//StrechBlt는 확대축소하여 복사 가능
		BitBlt(hdc, destX, destY, width, height, _imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}

}

void Image::frameRender(HDC hdc)
{
	//투명처리를 할 경우
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi를 뺀 함수도 있다. 
		GdiTransparentBlt(
			hdc,		//복사할 곳 DC
			_imageInfo->centerX - _imageInfo->frameWidth / 2,
			_imageInfo->centerY - _imageInfo->frameHeight / 2,		//대상 좌표 Y시작점
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,//
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor	//복사에서 제외할 색상
			);
	}
	//하지 않을 경우
	else
	{
		//StrechBlt는 확대축소하여 복사 가능
		BitBlt(hdc,
			_imageInfo->centerX - _imageInfo->frameWidth / 2,
			_imageInfo->centerY - _imageInfo->frameHeight / 2,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}

}
void Image::frameRender(HDC hdc, int destX, int destY)
{
	//투명처리를 할 경우
	if (_trans)
	{
		int widthSour, heightSour;
		//gdi를 뺀 함수도 있다. 
		GdiTransparentBlt(
			hdc,		//복사할 곳 DC
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,		//대상 좌표 Y시작점
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,//
			_imageInfo->currentFrameY * _imageInfo->frameHeight,//
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor	//복사에서 제외할 색상
			);
	}
	//하지 않을 경우
	else
	{
		BitBlt(hdc,
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}

}

void Image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	//투명처리를 할 경우
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, hdc, 0, 0, SRCCOPY);
		//gdi를 뺀 함수도 있다. 
		
		
		GdiTransparentBlt(
			_blendImage->hMemDC,		//복사할 곳 DC
			_imageInfo->centerX - _imageInfo->width / 2,		//대상 좌표 X시작점
			_imageInfo->centerY - _imageInfo->height / 2,		//대상 좌표 Y시작점
			_imageInfo->width, //이미지 폭
			_imageInfo->height, //이미지 높이
			_imageInfo->hMemDC,
			0, //복사 좌표 시작
			0, //복사 좌표 시작
			_imageInfo->width, //복사 폭
			_imageInfo->height, //폭사 높이
			_transColor	//복사에서 제외할 색상
			);
		
		
		//return;
		AlphaBlend(hdc, _imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC,
			_imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	//하지 않을 경우
	else
	{
		AlphaBlend(hdc, _imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC,
			_imageInfo->centerX - _imageInfo->width / 2, _imageInfo->centerY - _imageInfo->height / 2, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}