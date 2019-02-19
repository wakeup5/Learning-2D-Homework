/**
Win API
@author	박진한(wakeup5, wlsgks5@naver.com)
@date	2015/05/08
@brief	윈도우 api 기본
*/
#include "stdafx.h"

HINSTANCE _hInstance; // 프로그램 인스턴스
HWND _hWnd; // 윈도우 핸들

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowPositionAndSize(int x, int y, int width, int height);

void homework2(HWND, UINT, WPARAM, LPARAM);
void homework3(HWND, UINT, WPARAM, LPARAM);
void homework4(HWND, UINT, WPARAM, LPARAM);
void homework5(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	_hInstance = hInstance;

	wndClass.cbClsExtra		= 0;									// 클래스 여분 메모리
	wndClass.cbWndExtra		= 0;									// 윈도우 여분 메모리
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// 백그라운드
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// 커서 모양
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// 상위 창 아이콘 모양
	wndClass.hInstance		= hInstance;							// 윈도우 인스턴스
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;						// (*중요)프로시저 함수(메세지 처리함수) - 키보드 입력등에 호출되는 함수
	wndClass.lpszClassName	= WIN_NAME;					// 클래스 명(화면 창 이름)
	wndClass.lpszMenuName	= NULL;									// 메뉴명
	wndClass.style			= CS_HREDRAW | CS_VREDRAW;				// 윈도우 창 상단오른쪽 버튼 스타일

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WIN_NAME,		// 윈도우 클래스 이름
		WIN_NAME,		// 윈도우 타이틀바의 이름
		WIN_STYLE,		// 윈도우 스타일
		WIN_START_X,	// 윈도우 화면 좌표 x(좌우) - 픽셀 단위
		WIN_START_Y,	// 윈도우 화면 좌표 y(상하) - 픽셀 단위
		WIN_SIZE_X,		// 윈도우 화면 크기 width(폭)
		WIN_SIZE_Y,		// 윈도우 화면 크기 height(높이)
		NULL,			// 부모 윈도우 인스턴스
		(HMENU)NULL,	// 메뉴 핸들
		hInstance,		// 인스턴스 윈도우 지정
		NULL			// mdi 클라이언트 윈도우 및 자식 윈도우를 생성하면 지정해 주고, 사용하지 않으면 NULL
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

	//일반 윈도우 창
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnregisterClass(WIN_NAME, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static int homeworkNum = 1;
	
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_TAB:
			homeworkNum++;
			if (homeworkNum > 2) homeworkNum = 1;
			//KillTimer(hWnd, 2);
			//KillTimer(hWnd, 3);
			//KillTimer(hWnd, 4);
			//KillTimer(hWnd, 5);
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_DESTROY: //프로그램 종료시 발생.
		PostQuitMessage(0);
		return 0;
	}

	switch (homeworkNum)
	{
	case 1:
		homework2(hWnd, iMessage, wParam, lParam);
		break;
	case 2:
		homework3(hWnd, iMessage, wParam, lParam);
		break;
	case 3:
		homework4(hWnd, iMessage, wParam, lParam);
		break;
	case 4:
		homework5(hWnd, iMessage, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowPositionAndSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}

//숙제 1 RandomFunction float메소드 생성.
//숙제 2 사각형을 만들고 사각형을 드래그 하면 크기가 변함.
void homework2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static POINT mp;
	static RECT r;

	static POINTRECT pr = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 100, 100);

	static bool isClick = false;
	static int whereClick = 0;
	static int dx = 0, dy = 0;

	mp = makeMousePoint(lParam);

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawRectangle(hdc, pr.rect);
		TCHAR a[] = "숙제 2 - 마우스 드래그로 상자 크기 조절";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
		if (checkCollision(mp, pr.rect))
		{
			isClick = true;
			if (mp.x < pr.point.x && mp.y < pr.point.y)
			{
				whereClick = 1;
				dx = pr.rect.left - mp.x;
				dy = pr.rect.top - mp.y;
			}
			else if (mp.x > pr.point.x && mp.y < pr.point.y)
			{
				whereClick = 2;
				dx = pr.rect.right - mp.x;
				dy = pr.rect.top - mp.y;
			}
			else if (mp.x < pr.point.x && mp.y > pr.point.y)
			{
				whereClick = 3;
				dx = pr.rect.left - mp.x;
				dy = pr.rect.bottom - mp.y;
			}
			else if (mp.x > pr.point.x && mp.y > pr.point.y)
			{
				whereClick = 4;
				dx = pr.rect.right - mp.x;
				dy = pr.rect.bottom - mp.y;
			}
		}
		break;
	case WM_LBUTTONUP:
		isClick = false;
		break;
	case WM_MOUSEMOVE:
	{
		if (isClick)
		{
			if (whereClick == 1)
			{
				pr.rect.left = mp.x + dx;
				pr.rect.top = mp.y + dy;
			}
			else if (whereClick == 2)
			{
				pr.rect.right = mp.x + dx;
				pr.rect.top = mp.y + dy;
			}
			else if (whereClick == 3)
			{
				pr.rect.left = mp.x + dx;
				pr.rect.bottom = mp.y + dy;
			}
			else if (whereClick == 4)
			{
				pr.rect.right = mp.x + dx;
				pr.rect.bottom = mp.y + dy;
			}
		}
		pr.point.x = pr.rect.left + (pr.rect.right - pr.rect.left) / 2;
		pr.point.y = pr.rect.top + (pr.rect.bottom - pr.rect.top) / 2;

		InvalidateRect(hWnd, NULL, true);
	}
		break;
	}
}

//숙제 3 똥피하기
void homework3(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static POINTRECT player = makePointRectCenter(WIN_SIZE_X / 2, WIN_SIZE_Y - 20, 20, 20);

	player = makePointRectCenter(player.point, 20, 20);

	//int speed = 10;

	static vector<POINT> *ddongs = new vector<POINT>;
	vector<POINT>::iterator iter;

	static RECT gamePad = RECT{ 10, 10, WIN_SIZE_X - 10, WIN_SIZE_Y - 10 };
	static int maxSpeed = 10;
	static float speed = 0;
	static bool isKeyDown = false, isLeft = false, isRight = false;
	static bool isDead = false;
	static int po = 0;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		drawRectangle(hdc, gamePad);
		drawEllipse(hdc, player.rect);

		for (iter = ddongs->begin(); iter != ddongs->end(); iter++)
		{
			drawRectangleCenter(hdc, *iter, 20, 20);
		}

		TCHAR a[128] = "숙제 3 - 똥피하기 - ";
		wsprintf(a, "%s 점수:%5d 갯수:%2d", a, po, ddongs->size());
		TextOut(hdc, 10, 10, a, _tcslen(a));

		if (isDead)
		{
			TCHAR b[128] = "으앙 쥬금";
			wsprintf(b, "%s %5d점 스페이스바 누르셈", b, po);
			TextOut(hdc, (WIN_SIZE_X / 2) - 50, (WIN_SIZE_Y / 2) - 10 , b, _tcslen(b));
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
		if (wParam == 0)
		{
			if (RANDOM->getInt(100) < 10 + po / 20)
			{
				int randX = RANDOM->getIntTo(gamePad.left + 10, gamePad.right - 10);
				ddongs->push_back(POINT{ randX, 20 });
			}

			for (iter = ddongs->begin(); iter != ddongs->end(); iter++)
			{
				iter->y *= 1.05;
				if (iter->y > WIN_SIZE_Y + 20)
				{
					iter = ddongs->erase(iter);
					po++;
				}
				//충돌처리
				if (checkCollision(makeRectCenter(*iter, 20, 20), player.rect))
				{
					KillTimer(hWnd, 0);
					isDead = true;
				}
			}
			/*
			hdc = GetDC(hWnd);
			for (iter = ddongs.begin(); iter != ddongs.end(); iter++)
			{
			drawRectangleCenter(hdc, *iter, 20, 20);
			}
			ReleaseDC(hWnd, hdc);
			*/

			if (player.rect.left + speed > gamePad.left && player.rect.right + speed < gamePad.right)
			{
				player.point.x += speed;
			}
			else
			{
				speed = 0;
			}

			if (!isKeyDown) speed = (int)speed * 0.8;
			else
			{
				if (isLeft)
				{
					if (-maxSpeed < speed)
						speed -= 0.5;
				}
				else if (isRight)
				{
					if (maxSpeed > speed)
						speed += 0.5;
				}
			}

			InvalidateRect(hWnd, NULL, true);
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
		{
			SetTimer(hWnd, 0, 10, NULL);
			ddongs = new vector < POINT > ;
			po = 0;
			isDead = false;
		}
		switch (wParam)
		{
		case VK_LEFT:
			isLeft = true;
			isRight = false;
			break;
		case VK_RIGHT:
			isLeft = false;
			isRight = true;
			break;
		case VK_SPACE:
			if (isDead)
			{
				SetTimer(hWnd, 0, 10, NULL);
				ddongs = new vector < POINT >;
				po = 0;
				isDead = false;
			}
			break;
		}
		
		isKeyDown = true;
		break;
	case WM_KEYUP:
		isKeyDown = false;
		isLeft = false;
		isRight = false;
		break;
	}
}

//숙제 4 개구리 길 건너기 게임 
// - 에너지바 빨간색
// - 안전지대 벗어나면 에너지바 줄어듬
// - 안전지대 처음, 중간에 여러개 있다.
// - 안전지대 걸치면 에너지바 안줄음
// - 방해물이 왔다 갔다 하는데 조금이라도 닿으면 죽음
void homework4(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		TCHAR a[] = "숙제 4 - 길건너기";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}

//숙제 5 슈팅게임
// - 스페이스바 누르면 총알 하나 나감. 연발로 누르면 여러개 발사.
void homework5(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		TCHAR a[] = "숙제 5 - 슈팅게임";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}