#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();	

    _enemy.setPosition(POINT{700, WIN_SIZE_Y});
    _enemy.setAngleD(90);

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

    if (_cannon.getPosition().x > 0 && KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _cannon.moveX(-2);
    }

    if (_cannon.getPosition().x < WIN_SIZE_X && KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _cannon.moveX(2);
    }

    if (_cannon.getAngleD() < 100 && KEYMANAGER->isStayKeyDown(VK_UP))
    {
        _cannon.setAngleD(_cannon.getAngleD() + 2);
    }

    if (_cannon.getAngleD() > 10 && KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        _cannon.setAngleD(_cannon.getAngleD() - 2);
    }

    if (_power < MAX_POWER && KEYMANAGER->isStayKeyDown(VK_SPACE))
    {
        _power += 0.5;
    }

    if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
    {
        for (int i = 0; i < MAX_BULLET; i++)
        {
            if (!_bullet[i].isFire)
            {
                _bullet[i].isFire = true;
                _bullet[i].setSpeed(_power);
                _bullet[i].setAngleD(_cannon.getAngleD());
                _bullet[i].setPosition(_cannon.getEndPoint());

                //_bulletEnd[i] = _bullet[i].getPosition().x + (-_bullet[i].getSpeedY() / GRAVITY_ACCEL * 2) * _bullet[i].getSpeedX();
                
                //float time1 = (_bullet[i].getSpeedY() / GRAVITY_ACCEL * 2);
               // float distance1 = _bullet[i].getSpeedY() * time1 + (GRAVITY_ACCEL * pow(time1, 2) / 2);
                //float distance2 = distance1 + _bullet[i].getPositionY();

               // float time2 = (distance2 - GRAVITY_ACCEL) / (distance2 * _bullet[i].getSpeedY());

                while (_bullet[i].getPositionY() < WIN_SIZE_Y)
                {
                    _bullet[i].moveGravity();
                }

                _bulletEnd[i] = _bullet[i].getPosition().x;
                
                _bullet[i].setSpeed(_power);
                _bullet[i].setAngleD(_cannon.getAngleD());
                _bullet[i].setPosition(_cannon.getEndPoint());

                _shootPower = _power;

                break;
            }
        }
        _power = 0;
    };
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (_bullet[i].isFire)
        {
            _bullet[i].moveGravity();
        }

        if (_bullet[i].getPosition().y > WIN_SIZE_Y)
        {
            _bullet[i].isFire = false;
        }
    }

    if (KEYMANAGER->isOnceKeyDown('1'))
    {
        for (int i = 0; i < MAX_BULLET; i++)
        {
            if (_bullet[i].isFire)
            {
                _bullet[i].isFire = false;
            }
        }
    }

    float weightMove;
    weightMove = 0;
    //적 움직임
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (_bullet[i].isFire && //총알이 살아 있으면
            isCollisionEllipse(_bullet[i].getPosition(), makeRectCenter(_enemy.getPosition(), RADER_RANGE, RADER_RANGE)) && //총알이 적 근처에 도달했으면 
            isCollisionCircle(makeRectCenter(_bulletEnd[i], WIN_SIZE_Y, 50, 50 ), _enemy.getSize()) &&
            _bullet[i].getSpeedY() > 0) //총알이 적에게 부딫히는 시뮬레이션이 나오면
        {
            if (_enemy.getPosition().x <= _bulletEnd[i])
            {
                weightMove += _enemy.getPosition().x - _bulletEnd[i];
            }
            else
            {
                weightMove -= _bulletEnd[i] - _enemy.getPosition().x;
            }

            _enemyAngle = 180 - _cannon.getAngleD();
            _enemyPower = _shootPower;
        }
    }

    if (weightMove < 0)
    {
        _enemy.moveX(-1);
    }
    else if (weightMove > 0)
    {
        _enemy.moveX(1);
    }

    //적 조준
    if (_enemy.getAngleD() < _enemyAngle - 1)
    {
        _enemy.setAngleD(_enemy.getAngleD() + 0.5);
    }
    else if (_enemy.getAngleD() > _enemyAngle + 1)
    {
        _enemy.setAngleD(_enemy.getAngleD() - 0.5);
    }

    //조준 되면 발사
    if (_enemy.getAngleD() > _enemyAngle - 10 && _enemy.getAngleD() < _enemyAngle + 10)
    {
        if (!_enemyBullet.isFire)
        {
            _enemyBullet.isFire = true;
            _enemyBullet.setSpeed(_enemyPower);
            _enemyBullet.setAngleD(_enemy.getAngleD());
            _enemyBullet.setPosition(_enemy.getEndPoint());
        }
    }

    //적총알 없애기
    if (_enemyBullet.getPositionY() > WIN_SIZE_Y)
    {
        _enemyBullet.isFire = false;
    }

    //적 총알 움직임
    if (_enemyBullet.isFire)
    {
        _enemyBullet.moveGravity();
    }
    
}

//화면출력
void GameStudy::render(HDC hdc)
{

    Rectangle(hdc, 10, 10, 10 + (_power / MAX_POWER) * (WIN_SIZE_X - 20), 20);

    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (_bullet[i].isFire)
        {
            drawLine(hdc, _bulletEnd[i], 0, _bulletEnd[i], WIN_SIZE_Y);
        }
    }
    
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (_bullet[i].isFire)
        {
            drawEllipseCenter(hdc, _bullet[i].getPosition(), 10, 10);
        }
    }

    if (_enemyBullet.isFire)
    {
        drawEllipseCenter(hdc, _enemyBullet.getPosition(), 10, 10);
    }

    drawLine(hdc, _cannon.getPosition(), _cannon.getEndPoint());
    drawEllipse(hdc, _cannon.getSize());

    drawLine(hdc, _enemy.getPosition(), _enemy.getEndPoint());
    drawEllipse(hdc, _enemy.getSize());


    TCHAR a[128];
    sprintf_s(a, "%f", _bulletEnd[0]);
    TextOut(hdc, 10, 50, a, _tcslen(a));

 
}


