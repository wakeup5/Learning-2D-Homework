#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
    GameNode::initialize();
    gameInit();
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

    //탱크 마우스
    _player.setCannonAngleR(getRadianByTwoPosition(_player.getPosition().x, _player.getPosition().y, _mousePoint.x, _mousePoint.y));

    //탱크 움직임
    if (KEYMANAGER->isStayKeyDown('A'))
    {
        _player.setAngleR(_player.getAngleR() + 0.03);
    }

    if (KEYMANAGER->isStayKeyDown('D'))
    {
        _player.setAngleR(_player.getAngleR() - 0.03);
    }

    if (KEYMANAGER->isStayKeyDown('W'))
    {
        _player.moveFront();
    }

    if (KEYMANAGER->isStayKeyDown('S'))
    {
        _player.moveBack();
    }

    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < MAX_BULLET; i++)
        {
            if (_bullet[i].isFire) continue;

            _bullet[i].isFire = true;
            _bullet[i].setAngleR(_player.getCannonAngleR());
            _bullet[i].setPosition(_player.getCannonEndPoint());
            _bullet[i].setSpeed(10);
            break;
        }
    }

    //총알 움직임, 벽 닿으면 사라짐
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (!_bullet[i].isFire) continue;

        _bullet[i].move();

        if (_bullet[i].getPositionX() < 0 ||
            _bullet[i].getPositionX() > WIN_SIZE_X ||
            _bullet[i].getPositionY() < 0 ||
            _bullet[i].getPositionY() > WIN_SIZE_Y)
        {
            _bullet[i].isFire = false;
        }
    }

    //적 탱크 랜덤 출현
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (_enemy[i].isLive)
        {
            _enemy[i].setCannonAngleR(getAngleToCollisionCircle(_enemy[i].getPosition().x, _enemy[i].getPosition().y, _player.getPosition().x, _player.getPosition().y));
            _enemy[i].moveFront();

            if (_enemy[i].getPosition().x < 0 ||
                _enemy[i].getPosition().x > WIN_SIZE_X ||
                _enemy[i].getPosition().y < 0 ||
                _enemy[i].getPosition().y > WIN_SIZE_Y)
            {
                _enemy[i].isLive = false;
            }

            if (_enemyBullet[i].isFire)
            {
                _enemyBullet[i].move();

                if (_enemyBullet[i].getPosition().x < 0 ||
                    _enemyBullet[i].getPosition().x > WIN_SIZE_X ||
                    _enemyBullet[i].getPosition().y < 0 ||
                    _enemyBullet[i].getPosition().y > WIN_SIZE_Y)
                {
                    _enemyBullet[i].isFire = false;
                }
            }
            else
            {
                _enemyBullet[i].isFire = true;
                _enemyBullet[i].setAngleR(_enemy[i].getCannonAngleR());
                _enemyBullet[i].setSpeed(5);
                _enemyBullet[i].setPosition(_enemy[i].getCannonEndPoint());
            }
        }
        else
        {
            float enemyAngle = RANDOM->getFloat(2 * M_PI);
            _enemy[i].setAngleR(enemyAngle);
            _enemy[i].setCannonAngleR(enemyAngle);

            if (enemyAngle > M_PI / 4 && enemyAngle <= M_PI * 3 / 4) //랜덤 각도가 45도 ~ 135도 사이면
            {
                _enemy[i].setPosition(RANDOM->getInt(WIN_SIZE_X), WIN_SIZE_Y);
            }
            else if (enemyAngle > M_PI * 3 / 4 && enemyAngle <= M_PI * 5 / 4) // 135 ~ 225
            {
                _enemy[i].setPosition(WIN_SIZE_X, RANDOM->getInt(WIN_SIZE_Y));
            }
            else if (enemyAngle > M_PI * 5 / 4 && enemyAngle <= M_PI * 7 / 4) // 225 ~ 315
            {
                _enemy[i].setPosition(RANDOM->getInt(WIN_SIZE_X), 0);
            }
            else
            {
                _enemy[i].setPosition(0, RANDOM->getInt(WIN_SIZE_Y));
            }

            _enemy[i].isLive = true;
        }
    }

    //총알 충돌 체크
    //플레이어 총알
    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (!_bullet[i].isFire) continue;

        for (int j = 0; j < MAX_ENEMY; j++)
        {
            POINT bulletPosition = _bullet[i].getPosition();
            int size = _enemy[j].getSize() * 2;
            if (isCollisionEllipse(bulletPosition, makeRectCenter(_enemy[j].getPosition(), size, size)))
            {
                _enemy[j].isLive = false;
                _bullet[i].isFire = false;
            }
        }
    }

    //적총알

    for (int i = 0; i < MAX_ENEMY; i++)
    {
        if (!_enemyBullet[i].isFire) continue;

        POINT bulletPosition = _enemyBullet[i].getPosition();
        int size = _player.getSize() * 2;
        if (isCollisionEllipse(bulletPosition, makeRectCenter(_player.getPosition(), size, size)))
        {
            _enemyBullet[i].isFire = false;
            _playerHp--;
        }
    }

	if (_playerHp < 0)
	{
		PostQuitMessage(0);
	}
    
}

//화면출력
void GameStudy::render(HDC hdc)
{
    _player.printTank(hdc);

    for (int i = 0; i < MAX_BULLET; i++)
    {
        if (!_bullet[i].isFire) continue;

        drawEllipseCenter(hdc, _bullet[i].getPosition(), 10, 10);
    }

    for (int i = 0; i < MAX_ENEMY; i++)
    {
        _enemy[i].printTank(hdc);
        if (_enemyBullet[i].isFire)
        {
            drawEllipseCenter(hdc, _enemyBullet[i].getPosition(), 10, 10);
        }
    }

    Rectangle(hdc, 
        _player.getPosition().x - 50, 
        _player.getPosition().y + 60, 
        _player.getPosition().x - 50 + (static_cast<float>(_playerHp) / 20 * 100), 
        _player.getPosition().y + 56);

    TCHAR hpStr[128];
    sprintf_s(hpStr, "%d", _playerHp);
    TextOut(hdc, 10, 10, hpStr, _tcslen(hpStr));
}

//게임 초기화
void GameStudy::gameInit()
{
    _player.setPosition(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
    _player.setAngleR(M_PI / 2);
    _player.setCannonAngleR(M_PI / 2);
    _player.setCannonSize(60);
    _player.setSpeed(3);
    _player.setSize(50);

    _playerHp = 20;

    for (int i = 0; i < MAX_ENEMY; i++)
    {
        _enemy[i].setCannonSize(60);
        _enemy[i].setSpeed(1);
        _enemy[i].setSize(50);
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