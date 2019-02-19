#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
    GameNode::initialize();
    _colors[0] = RGB(255, 255, 0); // 노랑
    _colors[1] = RGB(0, 0, 255); // 파랑
    _colors[2] = RGB(255, 55, 55); // 빨강
    _colors[3] = RGB(255, 0, 255); //보라
    _colors[4] = RGB(255, 128, 0); // 주황
    _colors[5] = RGB(0, 255, 0); //초록
    _colors[6] = RGB(128, 0, 0); //검빨
    _colors[7] = RGB(0, 0, 0); //검정

    gameInit();

    _hole[0] = { _table.left + 5, _table.top + 5 };
    _hole[1] = { _table.right - 5, _table.top + 5 };
    _hole[2] = { _table.left + 5, _table.bottom - 5 };
    _hole[3] = { _table.right - 5, _table.bottom - 5 };
    _hole[4] = { _table.left, (_table.top + _table.bottom) / 2 };
    _hole[5] = { _table.right, (_table.top + _table.bottom) / 2 };

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

    if (_bullet[0].getSpeed() <= 0 && isCollisionEllipse(_mousePoint, makeRectCenter(_bullet[0].getPosition(), MISSILE_SIZE, MISSILE_SIZE)) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _isClick = true;
    }

    if (_isClick && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
    {
        _bullet[0].setSpeed(_power / 10);
        _bullet[0].setAngleR(_mouseR + M_PI);
        _isClick = false;
    }

    if (_isClick && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
    {
        _power = getDistance(_bullet[0].getPositionX(), _bullet[0].getPositionY(), _mousePoint.x, _mousePoint.y);
        if (_power > 200) _power = 200;
        _mouseR = getRadianByTwoPosition(_bullet[0].getPositionX(), _bullet[0].getPositionY(), _mousePoint.x, _mousePoint.y);

        float radian = _mouseR;
        _guideLine[0].x = _bullet[0].getPositionX();
        _guideLine[0].y = _bullet[0].getPositionY();

        for (int i = 1; i < GUIDELINE_MAX; i++)
        {
            if ((_power / 200) * GUIDELINE_MAX > i)
            {
                if (_guideLine[i - 1].x - cos(radian) * 5 < _table.left || _guideLine[i - 1].x - cos(radian) * 5 > _table.right)
                {
                    radian = M_PI - radian;
                }

                if (_guideLine[i - 1].y + sin(radian) * 5 < _table.top || _guideLine[i - 1].y + sin(radian) * 5 > _table.bottom)
                {
                    radian = 2 * M_PI - radian;
                }

                _guideLine[i].x = _guideLine[i - 1].x - cos(radian) * 5;
                _guideLine[i].y = _guideLine[i - 1].y + sin(radian) * 5;
                _guideLine[i].isView = true;
            }
            else
            {
                _guideLine[i].isView = false;
            }
        }
    }


    //미사일 움직임
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (_bullet[i].isFire)
        {
            _bullet[i].move();
            _bullet[i].setSpeed(_bullet[i].getSpeed() * 0.992);

            if (_bullet[i].getSpeed() < 0.1 && _bullet[i].getSpeed() != 0)
            {
                _bullet[i].setSpeed(0);
                if (i == 0)
                {
                    if (_turn == 0)
                    {
                        _turn = 1;
                    }
                    else
                    {
                        _turn = 0;
                    }
                }
            }
        }
    }

    //가장자리 충돌
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (!_bullet[i].isFire) continue;

        if (isCollisionEllipse(_bullet[i].getPosition(), makeRectCenter(_hole[0], HOLE_SIZE, HOLE_SIZE)) ||
            isCollisionEllipse(_bullet[i].getPosition(), makeRectCenter(_hole[1], HOLE_SIZE, HOLE_SIZE)) ||
            isCollisionEllipse(_bullet[i].getPosition(), makeRectCenter(_hole[2], HOLE_SIZE, HOLE_SIZE)) ||
            isCollisionEllipse(_bullet[i].getPosition(), makeRectCenter(_hole[3], HOLE_SIZE, HOLE_SIZE)) ||
            isCollisionEllipse(_bullet[i].getPosition(), makeRectCenter(_hole[4], HOLE_SIZE, HOLE_SIZE)) ||
            isCollisionEllipse(_bullet[i].getPosition(), makeRectCenter(_hole[5], HOLE_SIZE, HOLE_SIZE)))
        {
            if (i != 0 && 
                _bullet[i].getPositionX() - MISSILE_SIZE / 4 > _table.right ||
                _bullet[i].getPositionX() + MISSILE_SIZE / 4 < _table.left ||
                _bullet[i].getPositionY() - MISSILE_SIZE / 4 > _table.bottom ||
                _bullet[i].getPositionY() + MISSILE_SIZE / 4 < _table.top)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (_player[_turn][j] == -1)
                    {
                        _player[_turn][j] = i;
                        _bullet[i].isFire = false;
                        break;
                    }
                }
            }
        }
        else
        {
            if (_bullet[i].getPositionX() - MISSILE_SIZE / 2 < _table.left)
            {
                _bullet[i].setAngleD(180 - _bullet[i].getAngleD());
                _bullet[i].setPosition(POINT{ _table.left + MISSILE_SIZE / 2, _bullet[i].getPositionY() });
                _bullet[i].setSpeed(_bullet[i].getSpeed() * 0.98);
            }

            if (_bullet[i].getPositionX() + MISSILE_SIZE / 2 > _table.right)
            {
                _bullet[i].setAngleD(180 - _bullet[i].getAngleD());
                _bullet[i].setPosition(POINT{ _table.right - MISSILE_SIZE / 2, _bullet[i].getPositionY() });
                _bullet[i].setSpeed(_bullet[i].getSpeed() * 0.98);
            }

            if (_bullet[i].getPositionY() - MISSILE_SIZE / 2 < _table.top)
            {
                _bullet[i].setAngleD(360 - _bullet[i].getAngleD());
                _bullet[i].setPosition(POINT{ _bullet[i].getPositionX(), _table.top + MISSILE_SIZE / 2 });
                _bullet[i].setSpeed(_bullet[i].getSpeed() * 0.98);
            }

            if (_bullet[i].getPositionY() + MISSILE_SIZE / 2 > _table.bottom)
            {
                _bullet[i].setAngleD(360 - _bullet[i].getAngleD());
                _bullet[i].setPosition(POINT{ _bullet[i].getPositionX(), _table.bottom - MISSILE_SIZE / 2 });
                _bullet[i].setSpeed(_bullet[i].getSpeed() * 0.98);
            }
        }
        
    }

    //공끼리 충돌
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (!_bullet[i].isFire) continue;
        for (int j = i + 1; j < MAX_MISSILE; j++)
        {
            //if (i == j) continue;
            if (!_bullet[j].isFire) continue;

            if (isCollisionCircle(
                makeRectCenter(_bullet[i].getPosition(), MISSILE_SIZE, MISSILE_SIZE),
                makeRectCenter(_bullet[j].getPosition(), MISSILE_SIZE, MISSILE_SIZE)))
            {
                float mx = (_bullet[i].getPositionX() + _bullet[j].getPositionX()) / 2;
                float my = (_bullet[i].getPositionY() + _bullet[j].getPositionY()) / 2;
                float dist = sqrt((pow(_bullet[i].getPositionX() - _bullet[j].getPositionX(), 2) + pow(_bullet[i].getPositionY() - _bullet[j].getPositionY(), 2)));

                _bullet[i].setPosition(
                    POINT{
                    mx + (MISSILE_SIZE / 2) * (_bullet[i].getPositionX() - _bullet[j].getPositionX()) / dist,
                    my + (MISSILE_SIZE / 2) * (_bullet[i].getPositionY() - _bullet[j].getPositionY()) / dist });

                _bullet[j].setPosition(
                    POINT{
                    mx + (MISSILE_SIZE / 2) * (_bullet[j].getPositionX() - _bullet[i].getPositionX()) / dist,
                    my + (MISSILE_SIZE / 2) * (_bullet[j].getPositionY() - _bullet[i].getPositionY()) / dist });


                float e = 0.95;
                float as = _bullet[i].getSpeed(), bs = _bullet[j].getSpeed();
                float vax = _bullet[i].getSpeedX(), vay = _bullet[i].getSpeedY(), vbx = _bullet[j].getSpeedX(), vby = _bullet[j].getSpeedY();
                float aR = atan2(_bullet[i].getPositionY() - _bullet[j].getPositionY(), _bullet[i].getPositionX() - _bullet[j].getPositionX()),
                    bR = atan2(_bullet[j].getPositionY() - _bullet[i].getPositionY(), _bullet[j].getPositionX() - _bullet[i].getPositionX());

                float vaxp = (1 - 1 * e) / (1 + 1)*(vax*cos(aR) + vay*sin(aR)) + (1 + 1 * e) / (1 + 1)*(vbx*cos(aR) + vby*sin(aR));
                float vbxp = (1 + 1 * e) / (1 + 1)*(vax*cos(aR) + vay*sin(aR)) + (1 - 1 * e) / (1 + 1)*(vbx*cos(aR) + vby*sin(aR));

                float vayp = vay*cos(aR) - vax*sin(aR);
                float vbyp = vby*cos(aR) - vbx*sin(aR);

                _bullet[i].setSpeedX(vaxp*cos(aR) - vayp*sin(aR));
                _bullet[i].setSpeedY(vaxp*sin(aR) + vayp*cos(aR));

                _bullet[j].setSpeedX(vbxp*cos(aR) - vbyp*sin(aR));
                _bullet[j].setSpeedY(vbxp*sin(aR) + vbyp*cos(aR));
            }
        }
    }

    if (KEYMANAGER->isOnceKeyDown('1'))
    {
        gameInit();
    }
}

//화면출력
void GameStudy::render(HDC hdc)
{
    HBRUSH hb;
    HBRUSH ob;
    TCHAR ballNumberStr[128];

    //구멍
    for (int i = 0; i < 6; i++)
    {
        hb = CreateSolidBrush(RGB(0, 0, 0));
        ob = (HBRUSH)SelectObject(hdc, hb);
        drawEllipseCenter(hdc, _hole[i], HOLE_SIZE, HOLE_SIZE);
        SelectObject(hdc, ob);
        DeleteObject(hb);
        DeleteObject(ob);
    }

    Rectangle(hdc, _table.left, _table.top, _table.right, _table.bottom);
    for (int i = 0; i < MAX_MISSILE; i++)
    {
        if (!_bullet[i].isFire) continue;

        hb = CreateSolidBrush((i == 0) ? RGB(255, 255, 255) : _colors[(i - 1) % 8]);
        ob = (HBRUSH)SelectObject(hdc, hb);
        drawEllipseCenter(hdc, _bullet[i].getPosition(), MISSILE_SIZE, MISSILE_SIZE);
        SelectObject(hdc, ob);
        DeleteObject(hb);
        DeleteObject(ob);
        if (i != 0)
        {
            if (i < 9)
            {
                sprintf_s(ballNumberStr, "%-2d", -i);
            }
            else
            {
                sprintf_s(ballNumberStr, "%2d", i);
            }
            TextOut(hdc, _bullet[i].getPositionX() - 8, _bullet[i].getPositionY() - 8, ballNumberStr, _tcslen(ballNumberStr));
        }
    }

    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            if (_player[j][i] == -1) continue;

            hb = CreateSolidBrush((_player[j][i] == 0) ? RGB(255, 255, 255) : _colors[(_player[j][i] - 1) % 8]);
            ob = (HBRUSH)SelectObject(hdc, hb);
            drawEllipseCenter(hdc, (j == 0)? 50 : WIN_SIZE_X - 50, 100 + (i * 50), MISSILE_SIZE, MISSILE_SIZE);
            SelectObject(hdc, ob);
            DeleteObject(hb);
            DeleteObject(ob);
            if (_player[j][i] != 0 && _player[j][i] != -1)
            {
                if (_player[j][i] < 9)
                {
                    sprintf_s(ballNumberStr, "%-2d", -_player[j][i]);
                }
                else
                {
                    sprintf_s(ballNumberStr, "%2d", _player[j][i]);
                }
                TextOut(hdc, (j == 0) ? 48 : WIN_SIZE_X - 58, 92 + (i * 50), ballNumberStr, _tcslen(ballNumberStr));
            }
        }
    }

    if (_turn == 0)
    {
        drawEllipseCenter(hdc, 50, 50, 30, 30);
    }
    else
    {
        drawEllipseCenter(hdc, WIN_SIZE_X - 50, 50, 30, 30);
    }

    float xx = _bullet[0].getPositionX() + cos(_bullet[0].getAngleR()) * _bullet[0].getSpeed() * 10;
    float yy = _bullet[0].getPositionY() - sin(_bullet[0].getAngleR()) * _bullet[0].getSpeed() * 10;

    drawLine(hdc, _bullet[0].getPositionX(), _bullet[0].getPositionY(), xx, yy);
    
    if (_isClick)
    {
        float xx = _bullet[0].getPositionX() + cos(_mouseR) * _power;
        float yy = _bullet[0].getPositionY() - sin(_mouseR) * _power;
        drawLine(hdc, _bullet[0].getPositionX(), _bullet[0].getPositionY(), xx, yy);
    }

    //가이드 라인
    if (_isClick)
    {
        for (int i = 1; i < GUIDELINE_MAX; i++)
        {
            if (_guideLine[i].isView)
            //drawLine(hdc, _guideLine[i - 1], _guideLine[i]);
            drawEllipseCenter(hdc, _guideLine[i].x, _guideLine[i].y, 5, 5);
        }
    }

}

void GameStudy::gameInit()
{
    _table = RECT{ 100, 100, WIN_SIZE_X - 100, WIN_SIZE_Y - 100 };

    float x;
    float y;
    float size = MISSILE_SIZE + 1;
    //첫번째줄
    for (int i = 0, k = 1; i < 5; i++)
    {
        x = (WIN_SIZE_X / 2) - 2 * size + (i * size / 2);
        y = _table.top + 150 + (sqrt(3) / 2 * size) * i;
        for (int j = 0; j < 5 - i; j++, k++)
        {
            _bullet[k].setPosition(POINT{ x, y });
            
            //공 초기화
            _bullet[k].isFire = true;
            _bullet[k].setSpeed(0);


            x += size;
        }
    }

    _bullet[0].setPosition(POINT{ WIN_SIZE_X / 2, _table.bottom - 150 });
    _bullet[0].isFire = true;
    _bullet[0].setSpeed(0);

    _turn = 1;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            _player[i][j] = -1;
        }
    }
}


//05-19 숙제

//첫번째 각도에 따라서 총알 쏘고, 라디안, 각도 표시
//정적배열로.

//두번째 총알을 쓰면 벽을 튕겨 방향을 바꾼다.



//숙제

//당구
//포켓볼 - 공 색도 있다. 번호도 있다.
//흰공. 클릭 후 땡기면 방향과 힘을 받아 공이 굴러간다.
//땡기면 방향 표시를 해줘야 한다.
//땡기면 공이 움직일 예상 경로가 뜬다.
//구멍이 6개 있고 그 안에 공을 넣는다.
//탄성충돌?

//가운데 탱크
//키보드 방향키로 탱크움직임. 앞 방향 개념이 있고, 죄우 누르면 방향이 앞뒤를 누르면 앞, 뒤로 움직인다.
//마우스로 포신 방향이 움직인다.
//마우스 클릭으로 발사
//적 등장 사방에서
//등장하면 플레이어를 보고 포탄을 쏜다.
//맞으면 에너지 달고, 적 맞으면 죽음 한방에

//이거 하면 실력 늘음
//1p 2p 개녕
//각각 원이 있다.
//원 끝에 작은 원ㅇ 있고, 방향이 잇다.
//좌우 누르면 방향바뀜
//스페이스바 누르면 총알 발사
//서로 몸통을 맟춰 점수 획득
//쏠수도 있지만 방어 가능
//작은 원 맞으면 총알이 튕겨나감
//화면 상하벽에 맞으면 튕겨나감
//좌우는 밖으로 나감
//20발 맥스
//자기총알 자기가 맞음
//총알끼리 부딛힘