// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

//MFC가 아닌 응용프로그램의 경우에는 WIN32_LEAN_AND_MEAN를 정의해 빌드 시간을 단축시킨다.
#define WIN32_LEAN_AND_MEAN

/* ========================================
*  ## 헤더파일 ##
* ======================================== */
#include <Windows.h>	//윈도우 관련 헤더
#include <stdio.h>		//표준 입출력 헤더
#include <tchar.h>		//윈도우에서 사용할 문자열 출력 헤더
//MBCS(Multi Byte Character Set) 기존의 사용하던 멀티바이트 형태의 문자열
//WBCS(Widw Byte Character Set) 모든 문자를 2바이트로 처리

#include <math.h>
#include <string>

/* ========================================
*  ## 정의문 ##
* ======================================== */

//윈도우 이름
#define WIN_NAME (LPTSTR)(TEXT("API Window"))

//윈도우 위치 사이즈
#define WIN_START_X 100		//x위치
#define WIN_START_Y 0		//y위치
#define WIN_SIZE_X 1000		//폭
#define WIN_SIZE_Y 1000		//높이

//윈도우 스타일
#define WIN_STYLE WS_CAPTION | WS_SYSMENU

//안전 동적할당 해제 매크로
#define SAFE_DELETE(p)			{if (p) {delete(p); (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if (p) {delete[](p); (p)=NULL;}}
#define SAFE_RELEASE(p)			{if (p) {(p)->release(); (p) = NULL;}}

#define HOMEWORK 1
#if HOMEWORK == 1
#define HOMEWORK1 1
#endif
#if HOMEWORK == 2
#define HOMEWORK2 1
#endif
#if HOMEWORK == 3
#define HOMEWORK3 1
#endif
#if HOMEWORK == 4
#define HOMEWORK4 1
#endif

/* ========================================
*  ## 전역변수 ##
* ======================================== */
extern HINSTANCE _hInstance; // 프로그램 인스턴스
extern HWND _hWnd; // 윈도우 핸들

using namespace std;