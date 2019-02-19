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
		int width;
		int height;
		BYTE loadType;
		
		//구조체 초기화
		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCES;
		};

	}IMAGE_INFO, *LPIMAGE_INFO;

	LPIMAGE_INFO _imageInfo;	//이미지 경로
	CHAR *_fileName;			//이미지 경로명
	BOOL _trans;				//투명도
	COLORREF _transColor;		//투명 컬러키	
public:
	Image();
	~Image();

	//빈 비트맵 하나 생성
	HRESULT initialize(int width, int height);

	//이미지 설정(파일로 읽어옴)
	HRESULT initialize(const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	void release(void);

	//투명키 값 설정
	void setTransColor(BOOL trans, COLORREF transColor);

	//일반 렌더링
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int x, int y, int width, int height);

	//DC얻기
	inline HDC getMemDC(){ return _imageInfo->hMemDC; }
};

