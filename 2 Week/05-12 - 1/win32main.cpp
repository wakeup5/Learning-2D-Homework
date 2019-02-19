/**
Win API
@author	������(wakeup5, wlsgks5@naver.com)
@date	2015/05/08
@brief	������ api �⺻
*/
#include "stdafx.h"

HINSTANCE _hInstance; // ���α׷� �ν��Ͻ�
HWND _hWnd; // ������ �ڵ�

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

	wndClass.cbClsExtra		= 0;									// Ŭ���� ���� �޸�
	wndClass.cbWndExtra		= 0;									// ������ ���� �޸�
	wndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	// ��׶���
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Ŀ�� ���
	wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// ���� â ������ ���
	wndClass.hInstance		= hInstance;							// ������ �ν��Ͻ�
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;						// (*�߿�)���ν��� �Լ�(�޼��� ó���Լ�) - Ű���� �Էµ ȣ��Ǵ� �Լ�
	wndClass.lpszClassName	= WIN_NAME;					// Ŭ���� ��(ȭ�� â �̸�)
	wndClass.lpszMenuName	= NULL;									// �޴���
	wndClass.style			= CS_HREDRAW | CS_VREDRAW;				// ������ â ��ܿ����� ��ư ��Ÿ��

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WIN_NAME,		// ������ Ŭ���� �̸�
		WIN_NAME,		// ������ Ÿ��Ʋ���� �̸�
		WIN_STYLE,		// ������ ��Ÿ��
		WIN_START_X,	// ������ ȭ�� ��ǥ x(�¿�) - �ȼ� ����
		WIN_START_Y,	// ������ ȭ�� ��ǥ y(����) - �ȼ� ����
		WIN_SIZE_X,		// ������ ȭ�� ũ�� width(��)
		WIN_SIZE_Y,		// ������ ȭ�� ũ�� height(����)
		NULL,			// �θ� ������ �ν��Ͻ�
		(HMENU)NULL,	// �޴� �ڵ�
		hInstance,		// �ν��Ͻ� ������ ����
		NULL			// mdi Ŭ���̾�Ʈ ������ �� �ڽ� �����츦 �����ϸ� ������ �ְ�, ������� ������ NULL
		);

	setWindowPositionAndSize(WIN_START_X, WIN_START_Y, WIN_SIZE_X, WIN_SIZE_Y);

	ShowWindow(_hWnd, cmdShow);

	//���ӿ�
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
	//ó���� �޼����� ������ ���� ȣ��
	//render();
	}
	*/

	//�Ϲ� ������ â
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
	case WM_DESTROY: //���α׷� ����� �߻�.
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

//���� 1 �簢�� �Ѱ��� �׸��� ȭ��ǥ�� ������ ������.
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

		TCHAR a[] = "���� 1 - ȭ��ǥ ���� �����̱�";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
		break;
	}

}
//���� 2 �簢�� �Ѱ��� �׸��� �巡�� �ϸ� ������.
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

		TCHAR a[] = "���� 2 - ���� �巡��";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}
//���� 3 �簢�� �ΰ��� �׸��� ȭ��ǥ�� ������ �ϳ��� ������. �ٸ� �ϳ��� �� �� �ִ�.
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

		TCHAR a[] = "���� 3 - ���ڷ� �ٸ� ���� �б�";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}
//���� 4 �簢�� �ΰ��� �׸���. �簢�� �ϳ��� ���� �簢�� �ϳ��� �ִ�. �ٸ� �ϳ��� �浹�ϸ� ���� �簢���� �Űܰ��� �ٸ� �簢���� ������.
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

		TCHAR a[128] = "���� 4 - �浹�ϸ� ��Ʈ�� ���� �ٲ�";
		//wsprintf(a, "%s %d %d", a, controlRect * -1, checkInRect(r1, r2));
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
	break;
	}
}
//���� 5 �� ȭ�鿡 ���콺Ŭ���ϸ� ������ ����. ���(3�� �̻�), ������, ���� ����.
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
		InvalidateRect(hWnd, NULL, false);//������ �ʰ� WM_PAINT ȣ��
	}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		TCHAR a[128] = "���� 5 - Ŭ���ϸ� ���� ���� ����";
		TextOut(hdc, 10, 10, a, _tcslen(a));
		EndPaint(hWnd, &ps);
	}
		break;
	}
}