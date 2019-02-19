/**
@file   Image.h
@author 박진한(wlsgks5@naver.com)
@date   2015/05/26
*/
#pragma once

/**
@class	Image
@author	박진한(wlsgks5@naver.com)
@date	2015/05/26
*/
class Image
{
private:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCES = 0, //리소스 로드
		LOAD_FILE,			//파일로드
		LOAD_EMPTY,			//아무것도 없는 이미지
		LOAD_END			//이넘문의 끝 혹은 길이
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float centerX;
		float centerY;
		int width;
		int height;
		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		BYTE loadType;
		RECT boundingBox;
		
		//구조체 초기화
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			centerX = 0;
			centerY = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCES;
			boundingBox = makeRect(0, 0, 0, 0);
		};

	}IMAGE_INFO, *LPIMAGE_INFO;

	LPIMAGE_INFO _imageInfo;	//이미지 경로
	CHAR *_fileName;			//이미지 경로명
	BOOL _trans;				//투명도
	COLORREF _transColor;		//투명 컬러키

	BLENDFUNCTION _blendFunc;	//알파블렌드
	LPIMAGE_INFO _blendImage;	//

	inline void setBoundingBox()
	{
		_imageInfo->boundingBox = makeRectCenter(_imageInfo->centerX, _imageInfo->centerY, _imageInfo->width, _imageInfo->height);
	}
public:
	Image();
	~Image();

	//빈 비트맵 하나 생성
	HRESULT initialize(int width, int height);

	//이미지 설정(파일로 읽어옴)
	//폭과 높이를 가진 이미지
	HRESULT initialize(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//중심좌표와 폭 높이
	HRESULT initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//프레임 관련
	//폭 높이와 행열 갯수
	HRESULT initialize(const char* fileName, int width, int height, int frameColumn, int frameRow, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//폭 높이, 중심 좌표, 행열 갯수
	HRESULT initialize(const char* fileName, float centerX, float centerY, int width, int height, int frameColumn, int frameRow, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	void release(void);

	//투명키 값 설정
	void setTransColor(BOOL trans, COLORREF transColor);

	//일반 렌더링
	void render(HDC hdc);
	void render(HDC hdc, int sourX, int sourY, int width, int height);

	//이미지 객체의 중심 좌표를 무시하고 원하는 좌표에 그릴 수 있다.
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height);

	//프레임 렌더
	void frameRender(HDC hdc);
	void frameRender(HDC hdc, int destX, int destY);

	void alphaRender(HDC hdc, BYTE alpha);

	//DC얻기
	inline HDC getMemDC(){ return _imageInfo->hMemDC; }

	//좌표 x
	inline void setX(float x){ _imageInfo->centerX = x; setBoundingBox(); }
	inline float getX(){ return _imageInfo->centerX; }

	//좌표 y
	inline void setY(float y){ _imageInfo->centerY = y; setBoundingBox(); }
	inline float getY(){ return _imageInfo->centerY; }

	//좌표 x, y
	inline void setCenter(float x, float y){ _imageInfo->centerX = x; _imageInfo->centerY = y; setBoundingBox(); }

	//가로 해상도
	inline int getWidth(){ return _imageInfo->width; }

	//세로 해상도
	inline int getHeight(){ return _imageInfo->height; }

	//바운딩 박스
	inline RECT boundingBox(){ return _imageInfo->boundingBox; }

	inline void setFrameX(int frameX)
	{
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
		else
		{
			_imageInfo->currentFrameX = frameX; 
		}
	}
	inline void setFrameY(int frameY)
	{
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
		else
		{
			_imageInfo->currentFrameY = frameY;
		}
	}

	inline int getMaxFrameX(){ return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(){ return _imageInfo->maxFrameY; }

	inline int getFrameX(){ return _imageInfo->currentFrameX; }
	inline int getFrameY(){ return _imageInfo->currentFrameY; }

	inline int getFrameWidth(){ return _imageInfo->frameWidth; }
	inline int getFrameHeight(){ return _imageInfo->frameHeight; }
	
};

