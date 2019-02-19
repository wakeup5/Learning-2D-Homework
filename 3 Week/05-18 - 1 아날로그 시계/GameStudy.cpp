#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();

	_center.x = WIN_SIZE_X / 2;
	_center.y = WIN_SIZE_Y / 2;

	return S_OK;
}

//해제
void GameStudy::release(void)
{
	GameNode::release();
}

//화면갱신
void GameStudy::update(void)
{
	GameNode::update();

	timer = time(NULL);
	localtime_s(&t, &timer);

	_hour = t.tm_hour;
	_minite = t.tm_min;
	_second = t.tm_sec;

	//초침 끝자리 좌표
	double secondRadian = _second * 6 * M_PI / 180;
	_sp.x = _center.x + LENGTH_SECOND * sin(secondRadian);
	_sp.y = _center.y - LENGTH_SECOND * cos(secondRadian);

	//분침 끝자리 좌표
	double miniteRadian = _minite * 6 * M_PI / 180;
	_mp.x = _center.x + LENGTH_MINITE * sin(miniteRadian);
	_mp.y = _center.y - LENGTH_MINITE * cos(miniteRadian);

	//시침 끝자리 좌표
	double hourRadian = _hour * 30 * M_PI / 180;
	_hp.x = _center.x + LENGTH_HOUR * sin(hourRadian);
	_hp.y = _center.y - LENGTH_HOUR * cos(hourRadian);

}

//화면출력
void GameStudy::render(HDC hdc)
{
	//시계 가장자리 출력
	drawEllipseCenter(hdc, _center, WATCH_SIZE, WATCH_SIZE);
	drawEllipseCenter(hdc, _center, 5, 5);

	HPEN p;

	//시침
	p = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 5, RGB(0, 0, 0)));
	drawLine(hdc, _center.x, _center.y, _hp.x, _hp.y);
	//분침
	p = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));
	drawLine(hdc, _center.x, _center.y, _mp.x, _mp.y);
	//초침
	p = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 0, 0)));
	drawLine(hdc, _center.x, _center.y, _sp.x, _sp.y);
	//SelectObject(hdc, p);
	//DeleteObject(p);


	TCHAR time[128];
	sprintf_s(time, "%0.0f : %0.0f : %0.0f", _hour, _minite, _second);
	TextOut(hdc, 10, 10, time, _tcslen(time));
}
