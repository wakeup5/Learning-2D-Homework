#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
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

//����
void GameStudy::release(void)
{
	GameNode::release();
}

//ȭ�鰻��
void GameStudy::update(void)
{
	GameNode::update();
    
    //������
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

    //����
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

    //�ܼ��� ���� ���� ������ ��ġ�� �Ű���.
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
            //�ո��� ��ǥ�� �̵�
            _worm[i].x = _worm[i - 1].x;
            _worm[i].y = _worm[i - 1].y;

            /* ������ ũ�⿡ ���󰡰�
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

//ȭ�����
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





//����

//���̽� ��Ű
//���� ������
//�и� ���� ������
//���� ���� ħ�� ����

//���� 2
//�����̴� ������ ����. ũ�Ⱑ �� �ٸ� �����ص��� 10��
//���������� ���� �ִ� ����
//ó�� ���� �������� ���� �ڿ� ���� ������ �������.
//���� �ε����� �ݻ��
//�밡���� �����ϰ� �ִ�.
//�˿�Ű�� ������ ���� ���� ����.
