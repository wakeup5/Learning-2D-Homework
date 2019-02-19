#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{

}


GameNode::~GameNode()
{

}

//초기화
HRESULT GameNode::initialize(void)
{
	SetTimer(_hWnd, 0, 1000 / _fps, NULL);

	KEYMANAGER->initialize();

	return S_OK;
}

//해제
void GameNode::release(void)
{
	KillTimer(_hWnd, 0);

	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
}

//화면갱신
void GameNode::update(void)
{
	//화면 갱신
	InvalidateRect(_hWnd, NULL, true);
}

//화면출력
void GameNode::render(HDC hdc)
{

}

LRESULT GameNode::mainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		_mousePoint = makePoint(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_mousePoint = makeMousePoint(lParam);
		break;
	case WM_TIMER:
		this->update();
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
