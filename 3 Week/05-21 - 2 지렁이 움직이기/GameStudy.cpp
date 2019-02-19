#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();	

    /*
    float randomAngleD = RANDOM->getInt(360);
    float randomX = RANDOM->getIntTo(100, WIN_SIZE_X - 100);
    float randomY = RANDOM->getIntTo(100, WIN_SIZE_Y - 100);

    _size = 20;

    _worm[0].angleD = randomAngleD;
    _worm[0].angleR = randomAngleD * M_PI / 180;
    _worm[0].speed = 2;
    _worm[0].x = randomX;
    _worm[0].y = randomY;
    _worm[0].size = _size;
    _worm[0].prevD = _worm[0].angleD;
    _worm[0].prevR = _worm[0].angleR;

    for (int i = 1; i < WORM_LENGTH; i++)
    {
        _worm[i].angleD = randomAngleD;
        _worm[i].angleR = randomAngleD * M_PI / 180;
        //_worm[i].speed = _size;
        _worm[i].size = _size;// -(static_cast<float>(i) / WORM_LENGTH * _size / 4);
        _worm[i].x = _worm[i - 1].x - _worm[i - 1].size * cos(_worm[i - 1].angleR);
        _worm[i].y = _worm[i - 1].y + _worm[i - 1].size * sin(_worm[i - 1].angleR);
        _worm[i].prevD = _worm[i].angleD;
        _worm[i].prevR = _worm[i].angleR;
    }
    */

    for (int i = 0; i < WORM_LENGTH; i++)
    {
        _worm[i].angleD = (i == 0) ? RANDOM->getInt(360) : _worm[i - 1].angleD;
        _worm[i].angleR = _worm[i].angleD * M_PI / 180;
        _worm[i].x = (i == 0) ? RANDOM->getIntTo(100, WIN_SIZE_X - 100) : (_worm[i - 1].x - cosf(_worm[i].angleR) * (_worm[i - 1].size + _worm[i].size) / 2);
        _worm[i].y = (i == 0) ? RANDOM->getIntTo(100, WIN_SIZE_Y - 100) : (_worm[i - 1].y - sinf(_worm[i].angleR) * (_worm[i - 1].size + _worm[i].size) / 2);
        _worm[i].size = RANDOM->getIntTo(20, 40);//20 - (static_cast<float>(i) / WORM_LENGTH * 20 / 4);
        _worm[i].speed = 3;
    }
    
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
    
    //움직임
    for (int i = 0; i < WORM_LENGTH; i++)
    {
        _worm[i].speed = _worm[0].speed;

        if (i == 0)
        {
            _worm[i].x += cos(_worm[i].angleR) * _worm[i].speed;
            _worm[i].y += sin(_worm[i].angleR) * _worm[i].speed;
        }
        else
        {
            float distance = sqrt(pow(_worm[i].x - _worm[i - 1].x, 2) + pow(_worm[i].y - _worm[i - 1].y, 2));

            if ((_worm[i - 1].size + _worm[i].size) / 2 < distance)
            {
				_worm[i].angleR = getAngleToCollisionCircle(_worm[i].x, _worm[i].y, _worm[i - 1].x, _worm[i - 1].y);
                //_worm[i].angleD = _worm[i].angleR * 180 / M_PI;
                _worm[i].x = _worm[i - 1].x - cos(_worm[i].angleR) * (_worm[i - 1].size + _worm[i].size) / 2;
                _worm[i].y = _worm[i - 1].y + sin(_worm[i].angleR) * (_worm[i - 1].size + _worm[i].size) / 2;
            }

            _worm[i].x += cos(_worm[i].angleR) * _worm[i - 1].speed;
            _worm[i].y -= sin(_worm[i].angleR) * _worm[i - 1].speed;
        }
        
    }

    //방향
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _worm[0].angleD -= 5;
    }

    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _worm[0].angleD += 5;
    }
   

    if (_worm[0].x < 0)
    {
        _worm[0].angleD = 180 - _worm[0].angleD;
        _worm[0].x = 0;
    }

    if (_worm[0].x > WIN_SIZE_X)
    {
        _worm[0].angleD = 180 - _worm[0].angleD;
        _worm[0].x = WIN_SIZE_X;
    }

    if (_worm[0].y < 0)
    {
        _worm[0].angleD = 360 - _worm[0].angleD;
        _worm[0].y = 0;
    }

    if (_worm[0].y > WIN_SIZE_Y)
    {
        _worm[0].angleD = 360 - _worm[0].angleD;
        _worm[0].y = WIN_SIZE_Y;
    }

    _worm[0].angleR = _worm[0].angleD * M_PI / 180;

    if (_worm[0].speed < 10 && KEYMANAGER->isOnceKeyDown(VK_UP))
    {
        _worm[0].speed++;
    }

    if (_worm[0].speed > 0 && KEYMANAGER->isOnceKeyDown(VK_DOWN))
    {
        _worm[0].speed--;
    }

    //_worm[0].angleR = _worm[0].angleD * M_PI / 180;

    //단순히 마디가 이전 마디의 위치로 옮겨짐.
    /*
    for (int i = WORM_LENGTH - 1; i > 0; i--)
    {
        _worm[i].x = _worm[i - 1].x;
        _worm[i].y = _worm[i - 1].y;
    }
    */


    /*
    if (_time % _worm[0].speed == 0)
    {
        if (KEYMANAGER->isStayKeyDown(VK_LEFT))
        {
            _worm[0].angleD += 15;
        }

        if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
        {
            _worm[0].angleD -= 15;
        }

        if (_worm[0].speed < 5 && KEYMANAGER->isOnceKeyDown(VK_DOWN))
        {
            _worm[0].speed++;
        }

        if (_worm[0].speed > 1 && KEYMANAGER->isOnceKeyDown(VK_UP))
        {
            _worm[0].speed--;
        }


        for (int i = WORM_LENGTH - 1; i > 0; i--)
        {
            //앞마디 좌표로 이동
            _worm[i].x = _worm[i - 1].x;
            _worm[i].y = _worm[i - 1].y;

            /* 각도와 크기에 따라가게
            _worm[i].prevD = _worm[i].angleD;
            _worm[i].prevR = _worm[i].angleR;
            _worm[i].angleD = _worm[i - 1].prevD;
            _worm[i].angleR = _worm[i].angleD * M_PI / 180;
            
            _worm[i].x = _worm[i - 1].x + _worm[i - 1].size * cos(_worm[i].angleR + M_PI);
            _worm[i].y = _worm[i - 1].y - _worm[i - 1].size * sin(_worm[i].angleR + M_PI);
            *
            
        }

        _worm[0].prevD = _worm[0].angleD;
        _worm[0].prevR = _worm[0].angleR;
        _worm[0].angleR = _worm[0].angleD * M_PI / 180;
        _worm[0].x = _worm[0].x - _worm[0].size * cos(_worm[0].angleR + M_PI);
        _worm[0].y = _worm[0].y + _worm[0].size * sin(_worm[0].angleR + M_PI);
        
        if (_worm[0].x < 0)
        {
            _worm[0].angleD = 180 - _worm[0].angleD;
            _worm[0].x = 0;
        }

        if (_worm[0].x > WIN_SIZE_X)
        {
            _worm[0].angleD = 180 - _worm[0].angleD;
            _worm[0].x = WIN_SIZE_X;
        }

        if (_worm[0].y < 0)
        {
            _worm[0].angleD = 360 - _worm[0].angleD;
            _worm[0].y = 0;
        }

        if (_worm[0].y > WIN_SIZE_Y)
        {
            _worm[0].angleD = 360 - _worm[0].angleD;
            _worm[0].y = WIN_SIZE_Y;
        }
    }
    
    _time++;
    if (_time >= 1000)
    {
        _time = 0;
    }

    */
   

}

//화면출력
void GameStudy::render(HDC hdc)
{
    for (int i = 0; i < WORM_LENGTH; i++)
    {
        drawEllipseCenter(hdc, _worm[i].x, _worm[i].y, _worm[i].size, _worm[i].size);

		POINT start, end;
		start.x = _worm[i].x;
		start.y = _worm[i].y;

		end.x = start.x + cos(_worm[i].angleR) * 10;
		end.y = start.y - sin(_worm[i].angleR) * 10;

		drawLine(hdc, start, end);
    }

   // TCHAR a[128];
    //sprintf_s(a, "time %d, speed %d, t/s %d", _time, _worm[0].speed, _time%static_cast<int>(_worm[0].speed));
    //TextOut(hdc, 10, 10, a, _tcslen(a));

}





//숙제

//아이스 하키
//공은 마찰력
//밀면 공이 움직임
//서로 본진 침범 못함

//숙제 2
//지렁이는 원으로 구성. 크기가 다 다름 같게해도됨 10개
//일직선으로 가고 있다 랜덤
//처음 원이 방향으로 가고 뒤에 작은 원들이 따라붙음.
//벽에 부딛히면 반사됨
//대가리를 조종하고 있다.
//죄우키를 누르면 방향 조종 가능.
