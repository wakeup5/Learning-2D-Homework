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
			loadType = LOAD_RESOURCES;
			boundingBox = makeRect(0, 0, 0, 0);
		};

	}IMAGE_INFO, *LPIMAGE_INFO;

	LPIMAGE_INFO _imageInfo;	//이미지 경로
	CHAR *_fileName;			//이미지 경로명
	BOOL _trans;				//투명도
	COLORREF _transColor;		//투명 컬러키	

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
	HRESULT initialize(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initialize(const char* fileName, float centerX, float centerY, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	void release(void);

	//투명키 값 설정
	void setTransColor(BOOL trans, COLORREF transColor);

	//일반 렌더링
	void render(HDC hdc);
	void render(HDC hdc, int sourX, int sourY, int width, int height);

	//이미지 객체의 중심 좌표를 무시하고 원하는 좌표에 그릴 수 있다.
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height);

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
	
};

