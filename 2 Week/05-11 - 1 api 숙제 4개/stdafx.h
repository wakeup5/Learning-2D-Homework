// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

//MFC�� �ƴ� �������α׷��� ��쿡�� WIN32_LEAN_AND_MEAN�� ������ ���� �ð��� �����Ų��.
#define WIN32_LEAN_AND_MEAN

/* ========================================
*  ## ������� ##
* ======================================== */
#include <Windows.h>	//������ ���� ���
#include <stdio.h>		//ǥ�� ����� ���
#include <tchar.h>		//�����쿡�� ����� ���ڿ� ��� ���
//MBCS(Multi Byte Character Set) ������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ�
//WBCS(Widw Byte Character Set) ��� ���ڸ� 2����Ʈ�� ó��

#include <math.h>
#include <string>

/* ========================================
*  ## ���ǹ� ##
* ======================================== */

//������ �̸�
#define WIN_NAME (LPTSTR)(TEXT("API Window"))

//������ ��ġ ������
#define WIN_START_X 100		//x��ġ
#define WIN_START_Y 0		//y��ġ
#define WIN_SIZE_X 1000		//��
#define WIN_SIZE_Y 1000		//����

//������ ��Ÿ��
#define WIN_STYLE WS_CAPTION | WS_SYSMENU

//���� �����Ҵ� ���� ��ũ��
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
*  ## �������� ##
* ======================================== */
extern HINSTANCE _hInstance; // ���α׷� �ν��Ͻ�
extern HWND _hWnd; // ������ �ڵ�

using namespace std;