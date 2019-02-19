/**========================================
* Win API
* @author	������(wakeup5, wlsgks5@naver.com)
* @date	2015/05/11
* @brief	�ܼ� ������Ʈ�� ���� api ������ â�� ����.
* ======================================== */
#include "stdafx.h"

#if HOMEWORK4
/* ========================================
*  ## �������� ##
* ======================================== */
HINSTANCE _hInstance; // ���α׷� �ν��Ͻ�
HWND _hWnd; // ������ �ڵ�

/* ========================================
*  ## �Լ� ���� ##
* ======================================== */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowPositionAndSize(int x, int y, int width, int height);

/* ========================================
*  ## ���� �Լ� ## - �ܼ� ���� �Լ�ó�� api�� ���� �Լ�
* ======================================== */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;
	WNDCLASS wndClass;

	//_hInstance : �޼��� ó���Լ� ����.
	//�޼����� �߻��ϸ� �����Լ��� ȣ���� �޼����� ó���Ѵ�.
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;									// Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;									// ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			// Ŀ�� ���
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		// ���� â ������ ���
	wndClass.hInstance = hInstance;							// ������ �ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						// (*�߿�)���ν��� �Լ�(�޼��� ó���Լ�) - Ű���� �Էµ ȣ��Ǵ� �Լ�
	wndClass.lpszClassName = WIN_NAME;					// Ŭ���� ��(ȭ�� â �̸�)
	wndClass.lpszMenuName = NULL;									// �޴���
	wndClass.style = CS_HREDRAW | CS_VREDRAW;				// ������ â ��ܿ����� ��ư ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		WIN_NAME,		// ������ Ŭ���� �̸�
		WIN_NAME,		// ������ Ÿ��Ʋ���� �̸�
		WIN_STYLE,	// ������ ��Ÿ��
		WIN_START_X,			// ������ ȭ�� ��ǥ x(�¿�) - �ȼ� ����
		WIN_START_Y,			// ������ ȭ�� ��ǥ y(����) - �ȼ� ����
		WIN_SIZE_X,			// ������ ȭ�� ũ�� width(��)
		WIN_SIZE_Y,			// ������ ȭ�� ũ�� height(����)
		NULL,					// �θ� ������ �ν��Ͻ�
		(HMENU)NULL,			// �޴� �ڵ�
		hInstance,				// �ν��Ͻ� ������ ����
		NULL					// mdi Ŭ���̾�Ʈ ������ �� �ڽ� �����츦 �����ϸ� ������ �ְ�, ������� ������ NULL
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

	//GetMessage : �޼��� ť(FIFO)�� �Էµ� �޼����� �о �޼��� ����ü(���� MSG message)�� �����Ѵ�.
	//TranslateMessage : Ű���� �Է¿� ���� �޼��� ó��
	//DispatchMessage : ������ ���ν����� ���޵� �޼����� ���� ������� �������ش�. ������Ʈ? ���ν��� �Լ� ȣ�� �� ó���� ������ ȭ�鿡 �������ش�.


	//�Ϲ� ������ â
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//��ϵ� ������ Ŭ���� ����
	UnregisterClass(WIN_NAME, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	case WM_CREATE: //Ŭ������ �����ڿ� ���� �̺�Ʈ. ó�� ���α׷��� ���� �Ҷ� �� �ѹ� �߻�.

		break;
	case WM_DESTROY: //���α׷� ����� �߻�.
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
	{

		hdc = GetDC(hWnd);

		char x[128], y[128];
		int MouseX = LOWORD(lParam);
		int MouseY = HIWORD(lParam);

		_itoa_s(MouseX, x, 10);
		_itoa_s(MouseY, y, 10);
		sprintf_s(x, "%s, %s          ", x, y);
		
		TextOut(hdc, 10, 10, x, _tcslen(x));

		ReleaseDC(hWnd, hdc);
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

		TextOut(hdc, 10, 30, x, _tcslen(x));

		ReleaseDC(hWnd, hdc);
	}
	break;
	}

	//�� ����ġ������ ���� ó������ ���� �޼��� ó��.
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowPositionAndSize(int x, int y, int width, int height)
{
	//POINT : ��ġ, RECT : ũ��
	RECT rc;// {0, 0, width, height};
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//3��° ���ڴ� �޴� ���� ����(bool)
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}
#endif