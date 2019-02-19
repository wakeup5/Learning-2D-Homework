/**========================================
* Win API 05-11 과제 1
* @author	박진한(wakeup5, wlsgks5@naver.com)
* @date		2015/05/11
* @brief	마우스 클릭에 따라 구구단 출력
* ======================================== */
#include "stdafx.h"

#if HOMEWORK1
/* ========================================
*  ## 전역변수 ##
* ======================================== */
HINSTANCE _hInstance; // 프로그램 인스턴스
HWND _hWnd; // 윈도우 핸들

/* ========================================
*  ## 함수 원형 ##
* ======================================== */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowPositionAndSize(int x, int y, int width, int height);
void drawWord(HDC hdc, int x, int y, int word);

/* ========================================
*  ## 메인 함수 ## - 콘솔 메인 함수처럼 api의 메인 함수
* ======================================== */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	//_hInstance : 메세지 처리함수 지정.
	//메세지가 발생하면 지정함수를 호출해 메세지를 처리한다.
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;									// 클래스 여분 메모리
	wndClass.cbWndExtra = 0;									// 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			// 커서 모양
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// 상위 창 아이콘 모양
	wndClass.hInstance = hInstance;							// 윈도우 인스턴스
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// (*중요)프로시저 함수(메세지 처리함수) - 키보드 입력등에 호출되는 함수
	wndClass.lpszClassName = WIN_NAME;					// 클래스 명(화면 창 이름)
	wndClass.lpszMenuName = NULL;									// 메뉴명
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				// 윈도우 창 상단오른쪽 버튼 스타일

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 생성
	_hWnd = CreateWindow(
		WIN_NAME,		// 윈도우 클래스 이름
		WIN_NAME,		// 윈도우 타이틀바의 이름
		WIN_STYLE,	// 윈도우 스타일
		WIN_START_X,			// 윈도우 화면 좌표 x(좌우) - 픽셀 단위
		WIN_START_Y,			// 윈도우 화면 좌표 y(상하) - 픽셀 단위
		WIN_SIZE_X,			// 윈도우 화면 크기 width(폭)
		WIN_SIZE_Y,			// 윈도우 화면 크기 height(높이)
		NULL,					// 부모 윈도우 인스턴스
		(HMENU)NULL,			// 메뉴 핸들
		hInstance,				// 인스턴스 윈도우 지정
		NULL					// mdi 클라이언트 윈도우 및 자식 윈도우를 생성하면 지정해 주고, 사용하지 않으면 NULL
		);

	setWindowPositionAndSize(WIN_START_X, WIN_START_Y, WIN_SIZE_X, WIN_SIZE_Y);

	ShowWindow(_hWnd, cmdShow);

	//게임용
	/*
	while (true)
	{
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
	if (message.message == WM_QUIT)
	{
	break;
	}
	TranslateMessage(&message);
	DispatchMessage(&message);
	}
	//처리할 메세지가 없으면 렌더 호출
	//render();
	}
	*/

	//GetMessage : 메세지 큐(FIFO)에 입력된 메세지를 읽어서 메세지 구조체(변수 MSG message)에 저장한다.
	//TranslateMessage : 키보드 입력에 대한 메세지 처리
	//DispatchMessage : 윈도우 프로시저에 전달된 메세지를 실제 윈도우로 전달해준다. 업데이트? 프로시저 함수 호출 후 처리된 내용을 화면에 갱신해준다.


	//일반 윈도우 창
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//등록된 윈도우 클래스 제거
	UnregisterClass(WIN_NAME, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	HBRUSH myBrush;

	static int gugudan = 1;
	int x, y;

	x = ((gugudan - 1) % 3) * 100;
	y = ((gugudan - 1) / 3) * 200;

	switch (iMessage)
	{
	case WM_CREATE: //클래스의 생성자와 같은 이벤트. 처음 프로그램이 시작 할때 단 한번 발생.

		break;
	case WM_PAINT:
	{

		hdc = BeginPaint(hWnd, &ps);
		
		int x, y;
		POINT p[3];
		p[0] = { 0, 0 };
		p[1] = { 50, 0 };
		p[2] = { 40, 50 };
		int name[] = {'ㅂ', 'ㅏ', 'ㄱ', 'ㅈ', 'ㅣ', 'ㄴ', 'ㅎ', 'ㅏ', 'ㄴ'};

		for (int i = 0; i < 3; i++)
		{
			x = (i) % 3 * 100 + 500;
			y = (i) / 3 * 100 + 10;
			for (int j = 0; j < 3; j++)
			{
				drawWord(hdc, x + p[j].x, y + p[j].y, name[i * 3 + j]);
			}
		}

		myBrush = CreateSolidBrush(RGB(0, 196, 196));
		SelectObject(hdc, myBrush);

		//Pie(hdc, 100, 100, 200, 200, 0, 0, 500, 500); //부채꼴
		//Arc(hdc, 200, 200, 400, 400, 600, 600, 00, 0); //호

		Arc(hdc, -100, 300, 150, 700, 300, 700, 200, 300);
		Arc(hdc, 135, 340, 700, 900, 0, 500, 300, 900);
		Arc(hdc, -200, -200, 750, 880, 320, 1080, 950, 400);

		MoveToEx(hdc, 172, 397, NULL);
		LineTo(hdc, 245, 431);

		MoveToEx(hdc, 370, 442, NULL);
		LineTo(hdc, 689, 397);

		Ellipse(hdc, 173, 443, 224, 566);
		Ellipse(hdc, 387, 437, 605, 583);

		MoveToEx(hdc, 303, 509, NULL);
		LineTo(hdc, 242, 635);
		LineTo(hdc, 303, 660);

		Ellipse(hdc, 220, 712, 434, 794);

		for (int i = 0; i < 60; i++)
		{
			MoveToEx(hdc, 165 + (i * 10), 274, NULL);
			LineTo(hdc, 81 + (i * 10), 416);
			LineTo(hdc, 165 + ((i + 1) * 10), 274);
		}

		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY: //프로그램 종료시 발생.
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
	{
		hdc = GetDC(hWnd);
		{
			//구구단 출력
			char str1[128], str2[128], str3[128];
			int cy;
			for (int j = 1; j < 10; j++)
			{
				cy = ((j - 1) * 20) + y;
				//_itoa_s(gugudan, str1, 10);
				//_itoa_s(j, str2, 10);
				//_itoa_s(gugudan * j, str3, 10);
				wsprintf(str1, "%2d * %2d = %2d", gugudan, j, gugudan * j);
				TextOut(hdc, x, cy, str1, _tcslen(str1));
			}
		}
		if (gugudan < 9) gugudan++;

		char x[128], y[128];
		int MouseX = LOWORD(lParam);
		int MouseY = HIWORD(lParam);

		//_itoa_s(MouseX, x, 10);
		//_itoa_s(MouseY, y, 10);
		sprintf_s(x, "%5d, %5d", MouseX, MouseY);

		TextOut(hdc, 800, 930, x, _tcslen(x));

		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		//hdc = GetDC(hWnd);
		
		RECT r;
		r.top = y;
		r.left = x;
		r.bottom = y + 200;
		r.right = x + 100;

		InvalidateRect(hWnd, &r, true);

		if (gugudan > 1) gugudan--;
		//ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_MOUSEMOVE:
	{

		hdc = GetDC(hWnd);

		char x[128], y[128];
		int MouseX = LOWORD(lParam);
		int MouseY = HIWORD(lParam);

		_itoa_s(MouseX, x, 10);
		_itoa_s(MouseY, y, 10);
		sprintf_s(x, "%s, %s          ", x, y);

		TextOut(hdc, 900, 900, x, _tcslen(x));

		ReleaseDC(hWnd, hdc);
	}
	break;
	}

	//위 스위치문에서 직접 처리하지 않은 메세지 처리.
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}


void drawWord(HDC hdc, int x, int y, int word)
{
	int cx, cy;
	switch (word)
	{
	case 'ㅂ':
		for (int i = 0; i < 40; i++)
		{

			for (int j = 0; j < 40; j++)
			{
				if (j == 0 || j == 39 || i == 20 || i == 39)
					SetPixel(hdc, x + j, y + i, RGB(0, 0, 0));
			}
		}
		break;
	case 'ㅏ':
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (j == 20 || (j > 20 && i == 20))
					SetPixel(hdc, x + j, y + i, RGB(0, 0, 0));
			}
		}
		break;
	case 'ㄱ':
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (i == 0 || j == 39)
					SetPixel(hdc, x + j, y + i, RGB(0, 0, 0));
			}
		}
		break;
	case 'ㅈ':
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if ((i == 0) || (i == 40 - j) || (i > 20 && i == j))
					SetPixel(hdc, x + j, y + i, RGB(0, 0, 0));
			}
		}
		break;
	case 'ㅣ':
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (j == 20)
					SetPixel(hdc, x + j, y + i, RGB(0, 0, 0));
			}
		}
		break;
	case 'ㄴ':
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (j == 0 || i == 39)
					SetPixel(hdc, x + j, y + i, RGB(0, 0, 0));
			}
		}
		break;
	case 'ㅎ':
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				int a = ((i - 29) * (i - 29)) + (j - 20) * (j - 20);
				if ((j > 10 && j < 30 && i == 0) || (i == 10) || (a < 110 && a > 90))
					SetPixel(hdc, x + j, y + i, RGB(0, 0, 0));
			}
		}
		break;
	}
}

void setWindowPositionAndSize(int x, int y, int width, int height)
{
	//POINT : 위치, RECT : 크기
	RECT rc;// {0, 0, width, height};
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//3번째 인자는 메뉴 존재 여부(bool)
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}
#endif