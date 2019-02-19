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
void homework1(HWND, UINT, WPARAM, LPARAM);
void homework2(HWND, UINT, WPARAM, LPARAM);
void homework3(HWND, UINT, WPARAM, LPARAM);
void homework4(HWND, UINT, WPARAM, LPARAM);
void homework5(HWND, UINT, WPARAM, LPARAM);
void setWindowPositionAndSize(int x, int y, int width, int height);


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
	PAINTSTRUCT ps;
	HDC hdc;

	static int homework = 1;

	static POINT p = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	static RECT r;
	
	r = makeRectCenter(p.x, p.y, 100, 100);

	switch (iMessage)
	{
	case WM_CREATE:
	{

		break;
	}	
	case WM_DESTROY: //프로그램 종료시 발생.
		PostQuitMessage(0);
		return 0;
		/*
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawRectangle(hdc, r);
		EndPaint(hWnd, &ps);
		break;
	}
		*/
	case WM_KEYDOWN:
	{
		if (wParam == VK_TAB)
		{
			homework++;
			if (homework > 5) homework = 1;
			InvalidateRect(hWnd, NULL, true);
		}
		break;
	}
	}

	switch (homework)
	{
	case 1:
		homework1(hWnd, iMessage, wParam, lParam);
		break;
	case 2:
		homework2(hWnd, iMessage, wParam, lParam);
		break;
	case 3:
		homework3(hWnd, iMessage, wParam, lParam);
		break;
	case 4:
		homework4(hWnd, iMessage, wParam, lParam);
		break;
	case 5:
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

//숙제 1 사각형 한개를 그리고 화살표를 누르면 움직임.
void homework1(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT p = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	static RECT r;
	
	r = makeRectCenter(p.x, p.y, 100, 100);
	
	int speed = 10;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (r.left > 0)	p.x -= speed;
			break;
		case VK_RIGHT:
			if (r.right < WIN_SIZE_X) p.x += speed;
			break;
		case VK_UP:
			if (r.top > 0) p.y -= speed;
			break;
		case VK_DOWN:
			if (r.bottom < WIN_SIZE_Y) p.y += speed;
			break;
		}
			//hdc = GetDC(hWnd);
			//ReleaseDC(hWnd, hdc);
			InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawRectangle(hdc, r);

		TCHAR a[] = "숙제 1 - 화살표 상자 움직이기";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
		break;
	}

}
//숙제 2 사각형 한개를 그리고 드래그 하면 움직임.
void homework2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT p = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	static RECT r;
	r = makeRectCenter(p.x, p.y, 100, 100);

	static bool isMouseDown = false;

	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	static int dx = 0, dy = 0;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		if (checkInRect(makePoint(mouseX, mouseY), r))
		{
			isMouseDown = true;
			dx = p.x - mouseX;
			dy = p.y - mouseY;
		}
		break;
	case WM_LBUTTONUP:
		isMouseDown = false;
		break;
	case WM_MOUSEMOVE:
		if (isMouseDown)
		{
			p.x = mouseX + dx;
			p.y = mouseY + dy;
			InvalidateRect(hWnd, NULL, true);
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawRectangle(hdc, r);

		TCHAR a[] = "숙제 2 - 상자 드래그";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}
//숙제 3 사각형 두개를 그리고 화살표를 누르면 하나가 움직임. 다른 하나를 밀 수 있다.
void homework3(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int speed = 10;
	int size = 100;

	static POINT p1 = makePoint(100, 250);
	static RECT r1;
	r1 = makeRectCenter(p1.x, p1.y, size, size);

	static POINT p2 = makePoint(400, 250);
	static RECT r2;
	r2 = makeRectCenter(p2.x, p2.y, size, size);


	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			/*if ((r1.left > 0 || !checkInRect(r1, r2)) && r2.left > 0)*/ p2.x -= speed;
			r1 = makeRectCenter(p1.x, p1.y, 100, 100);
			r2 = makeRectCenter(p2.x, p2.y, 100, 100);
			if (checkInRect(r1, r2))
			{
				p1.x = r2.left - size / 2;
			}
			break;
		case VK_RIGHT:
			/*if (!(r1.right > WIN_SIZE_X && checkInRect(r1, r2)) || r2.right < WIN_SIZE_X)*/ p2.x += speed;
			r1 = makeRectCenter(p1.x, p1.y, 100, 100);
			r2 = makeRectCenter(p2.x, p2.y, 100, 100);
			if (checkInRect(r1, r2))
			{
				p1.x = r2.right + size / 2;
			}
			break;
		case VK_UP:
			/*if (!(r1.top < 0 && checkInRect(r1, r2) && r2.top > 0) || r2.bottom < WIN_SIZE_X)*/ p2.y -= speed;
			r1 = makeRectCenter(p1.x, p1.y, 100, 100);
			r2 = makeRectCenter(p2.x, p2.y, 100, 100);
			if (checkInRect(r1, r2))
			{
				p1.y = r2.top - size / 2;
			}
			break;
		case VK_DOWN:
			/*if (!(r1.bottom > WIN_SIZE_X && checkInRect(r1, r2)) || r2.bottom < WIN_SIZE_X)*/ p2.y += speed;
			r1 = makeRectCenter(p1.x, p1.y, 100, 100);
			r2 = makeRectCenter(p2.x, p2.y, 100, 100);
			if (checkInRect(r1, r2))
			{
				p1.y = r2.bottom + size / 2;
			}
			break;
		}
		if (wParam == VK_TAB)
		{
			p1 = makePoint(100, 250);
			p2 = makePoint(400, 250);
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawRectangle(hdc, r1);
		drawRectangle(hdc, r2);

		TCHAR a[] = "숙제 3 - 상자로 다른 상자 밀기";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}
//숙제 4 사각형 두개를 그린다. 사각형 하나에 작은 사각형 하나가 있다. 다른 하나와 충돌하면 작은 사각형이 옮겨가고 다른 사각형이 움직임.
void homework4(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int speed = 10;
	int size = 100;

	static POINT p1 = makePoint(100, 250);
	static RECT r1;
	r1 = makeRectCenter(p1.x, p1.y, size, size);

	static POINT p2 = makePoint(400, 250);
	static RECT r2;
	r2 = makeRectCenter(p2.x, p2.y, size, size);

	static int controlRect = 1;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (controlRect < 1) r1 = makeRectCenter(p1.x - speed, p1.y, 100, 100);
			else r2 = makeRectCenter(p2.x - speed, p2.y, 100, 100);
						
			if (checkInRect(r1, r2)) controlRect = controlRect * -1; 

			if (controlRect < 1) p1.x -= speed;
			else p2.x -= speed;
			
			break;
		case VK_RIGHT:
			if (controlRect < 1) r1 = makeRectCenter(p1.x + speed, p1.y, 100, 100);
			else r2 = makeRectCenter(p2.x + speed, p2.y, 100, 100);

			if (checkInRect(r1, r2)) controlRect = controlRect * -1; 

			if (controlRect < 1) p1.x += speed;
			else p2.x += speed;

			break;
		case VK_UP:
			if (controlRect < 1) r1 = makeRectCenter(p1.x, p1.y - speed, 100, 100);
			else r2 = makeRectCenter(p2.x, p2.y - speed, 100, 100);
			
			if (checkInRect(r1, r2)) controlRect = controlRect * -1;

			if (controlRect < 1) p1.y -= speed;
			else p2.y -= speed;

			break;
		case VK_DOWN:
			if (controlRect < 1) r1 = makeRectCenter(p1.x, p1.y + speed, 100, 100);
			else r2 = makeRectCenter(p2.x, p2.y + speed, 100, 100);
			
			if (checkInRect(r1, r2)) controlRect = controlRect * - 1;

			if (controlRect < 1) p1.y += speed;
			else p2.y += speed;

			break;
		}
		if (wParam == VK_TAB)
		{
			p1 = makePoint(100, 250);
			p2 = makePoint(400, 250);
		}
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		drawRectangle(hdc, r1);
		drawRectangle(hdc, r2);

		if (controlRect < 1)
		{
			drawRectangleCenter(hdc, p1.x, p1.y, 50, 50);
		}
		else
		{
			drawRectangleCenter(hdc, p2.x, p2.y, 50, 50);
		}

		TCHAR a[128] = "숙제 4 - 충돌하면 컨트롤 상자 바뀜";
		//wsprintf(a, "%s %d %d", a, controlRect * -1, checkInRect(r1, r2));
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}
//숙제 5 흰 화면에 마우스클릭하면 뭔가가 생성. 모양(3개 이상), 사이즈, 색상 랜덤.
void homework5(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HBRUSH b, ob;
	HPEN p, op;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
	{
		hdc = GetDC(hWnd);
		
		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		b = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		ob = (HBRUSH)SelectObject(hdc, b);
		p = CreatePen(PS_SOLID, (rand() % 10) + 1, RGB(rand() % 256, rand() % 256, rand() % 256));
		op = (HPEN)SelectObject(hdc, p);

		switch (rand() % 3)
		{
		case 0:
			drawEllipseCenter(hdc, mouseX, mouseY, (rand() % 50) + 50, (rand() % 50) + 50);
			break;
		case 1:
			drawRectangleCenter(hdc, mouseX, mouseY, (rand() % 50) + 50, (rand() % 50) + 50);
			break;
		case 2:
			POINT point[4];
			point[0] = { mouseX, mouseY - (rand() % 50) - 50 };
			point[1] = { mouseX - (rand() % 50) - 50, mouseY };
			point[2] = { mouseX, mouseY + (rand() % 50) + 50 };
			point[3] = { mouseX + (rand() % 50) + 50, mouseY };
			Polygon(hdc, point, 4);
			break;
		}

		SelectObject(hdc, ob);
		DeleteObject(b);
		SelectObject(hdc, op);
		DeleteObject(p);

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, false);//지우지 않고 WM_PAINT 호출
	}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		TCHAR a[128] = "숙제 5 - 클릭하면 랜덤 도형 생성";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
		break;
	}
}