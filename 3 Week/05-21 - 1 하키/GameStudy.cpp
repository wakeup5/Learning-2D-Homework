#include "stdafx.h"
#include "GameStudy.h"

//초기화
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();	
    _player1 = POINT{ WIN_SIZE_X / 4, WIN_SIZE_Y / 2 };
    _player2 = POINT{ WIN_SIZE_X * 3 / 4, WIN_SIZE_Y / 2 };
    _goalpost1 = RECT{ -1, WIN_SIZE_Y / 2 - 100, 50, WIN_SIZE_Y / 2 + 100 };
    _goalpost2 = RECT{ WIN_SIZE_X - 50, WIN_SIZE_Y / 2 - 100, WIN_SIZE_X + 1, WIN_SIZE_Y / 2 + 100 };
    _score1 = _score2 = 0;
    
    _ball.setPosition(POINT{ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
    _ball.setAngleD(90);
    _ball.setSpeedX(0);
    _ball.setSpeedY(0);
    _ball.setSpeed(0);

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
 
    if (_player2.y - PLAYER_SIZE / 2 > 0 && KEYMANAGER->isStayKeyDown(VK_UP))
    {
        _player2.y -= 10;
    }
    if (_player2.y + PLAYER_SIZE / 2 < WIN_SIZE_Y && KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        _player2.y += 10;
    }
    if (_player2.x - PLAYER_SIZE / 2 > WIN_SIZE_X / 2 && KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _player2.x -= 10;
    }
    if (_player2.x + PLAYER_SIZE / 2 < WIN_SIZE_X && KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _player2.x += 10;
    }

    if (_player1.y - PLAYER_SIZE / 2 > 0 && KEYMANAGER->isStayKeyDown('W'))
    {
        _player1.y -= 10;
    }
    if (_player1.y + PLAYER_SIZE / 2 < WIN_SIZE_Y && KEYMANAGER->isStayKeyDown('S'))
    {
        _player1.y += 10;
    }
    if (_player1.x - PLAYER_SIZE / 2 > 0 &&  KEYMANAGER->isStayKeyDown('A'))
    {
        _player1.x -= 10;
    }
    if (_player1.x + PLAYER_SIZE / 2 < WIN_SIZE_X / 2 && KEYMANAGER->isStayKeyDown('D'))
    {
        _player1.x += 10;
    }

    if (isCollisionCircle(makeRectCenter(_player1, PLAYER_SIZE, PLAYER_SIZE), makeRectCenter(_ball.getPosition(), BALL_SIZE, BALL_SIZE)))
    {
        /*
        float mx = (_player1.x + _ball.getPositionX()) / 2;
        float my = (_player1.y + _ball.getPositionY()) / 2;
        float dist = sqrt((pow(_player1.x - _ball.getPositionX(), 2) + pow(_player1.y - _ball.getPositionY(), 2)));

        _ball.setPosition(
            POINT{
            mx + (BALL_SIZE / 2) * (_player1.x - _ball.getPositionX()) / dist,
            my + (BALL_SIZE / 2) * (_player1.y - _ball.getPositionY()) / dist });
        */

        _ball.setAngleR(getAngleToCollisionCircle(_player1.x, _player1.y, _ball.getPositionX(), _ball.getPositionY()));
        _ball.setSpeed(15);
    }

    if (isCollisionCircle(makeRectCenter(_player2, PLAYER_SIZE, PLAYER_SIZE), makeRectCenter(_ball.getPosition(), BALL_SIZE, BALL_SIZE)))
    {
        _ball.setAngleR(getAngleToCollisionCircle(_player2.x, _player2.y, _ball.getPositionX(), _ball.getPositionY()));
        _ball.setSpeed(15);
    }

    if (_ball.getSpeed() > 0)
    {
        _ball.setSpeed(_ball.getSpeed() - 0.04);
    }
    if (_ball.getSpeed() < 0)
    {
        _ball.setSpeed(0);
    }

    if (_ball.getPositionY() - BALL_SIZE / 2 < 0 || _ball.getPositionY() + BALL_SIZE / 2 > WIN_SIZE_Y)
    {
        _ball.setAngleD(360 - _ball.getAngleD());
    }
    if (_ball.getPositionX() - BALL_SIZE / 2 < 0 || _ball.getPositionX() + BALL_SIZE / 2 > WIN_SIZE_X)
    {
        _ball.setAngleD(180 - _ball.getAngleD());
    }

    _ball.move();
    //RECT{ -1, WIN_SIZE_Y / 2 - 100, 50, WIN_SIZE_Y / 2 + 100 };
    if (isCollisionEllipse(RECT{ 0, WIN_SIZE_Y / 2 - 100 + BALL_SIZE / 2, 20, WIN_SIZE_Y / 2 + 100 - BALL_SIZE / 2 }, makeRectCenter(_ball.getPosition(), BALL_SIZE, BALL_SIZE)))
    {
        _score2++;
        _player1 = POINT{ WIN_SIZE_X / 4, WIN_SIZE_Y / 2 };
        _player2 = POINT{ WIN_SIZE_X * 3 / 4, WIN_SIZE_Y / 2 };
       
        _ball.setPosition(POINT{ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
        _ball.setAngleD(90);
        _ball.setSpeedX(0);
        _ball.setSpeedY(0);
        _ball.setSpeed(0);
    }

    if (isCollisionEllipse(RECT{ WIN_SIZE_X - 20, WIN_SIZE_Y / 2 - 100 + BALL_SIZE / 2, WIN_SIZE_X, WIN_SIZE_Y / 2 + 100 - BALL_SIZE / 2 }, makeRectCenter(_ball.getPosition(), BALL_SIZE, BALL_SIZE)))
    {
        _score1++;
        _player1 = POINT{ WIN_SIZE_X / 4, WIN_SIZE_Y / 2 };
        _player2 = POINT{ WIN_SIZE_X * 3 / 4, WIN_SIZE_Y / 2 };

        _ball.setPosition(POINT{ WIN_SIZE_X / 2, WIN_SIZE_Y / 2 });
        _ball.setAngleD(90);
        _ball.setSpeedX(0);
        _ball.setSpeedY(0);
        _ball.setSpeed(0);
    }
}

//화면출력
void GameStudy::render(HDC hdc)
{
    drawEllipseCenter(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 200, 200);
    drawLine(hdc, WIN_SIZE_X / 2, 0, WIN_SIZE_X / 2, WIN_SIZE_Y);
    Rectangle(hdc, _goalpost1.left, _goalpost1.top, _goalpost1.right, _goalpost1.bottom);
    Rectangle(hdc, _goalpost2.left, _goalpost2.top, _goalpost2.right, _goalpost2.bottom);

    drawEllipseCenter(hdc, _player1, PLAYER_SIZE, PLAYER_SIZE);
    drawEllipseCenter(hdc, _player2, PLAYER_SIZE, PLAYER_SIZE);

    drawEllipseCenter(hdc, _ball.getPosition(), BALL_SIZE, BALL_SIZE);

    TCHAR score[128];
    sprintf_s(score, "score : %3d", _score1);
    TextOut(hdc, 10, 10, score, _tcslen(score));

    sprintf_s(score, "score : %3d", _score2);
    TextOut(hdc, WIN_SIZE_X - 100, WIN_SIZE_Y - 30, score, _tcslen(score));
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
