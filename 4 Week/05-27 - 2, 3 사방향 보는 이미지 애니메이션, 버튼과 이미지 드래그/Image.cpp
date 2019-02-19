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

	ReleaseDC(_hWnd, hdc);

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

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

	ReleaseDC(_hWnd, hdc);

	_trans = trans;
	_transColor = transColor;

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

	ReleaseDC(_hWnd, hdc);

	_trans = trans;
	_transColor = transColor;

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

		SAFE_DELETE(_imageInfo);
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