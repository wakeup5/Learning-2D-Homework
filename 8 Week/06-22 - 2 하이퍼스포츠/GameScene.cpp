#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{

}
HRESULT GameScene::initialize(void)
{
	_background = IMAGEMANAGER->addImage("background", "resource/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	_shooter = IMAGEMANAGER->addImage("shooter", "resource/shooter.bmp", 360, 110, TRUE, RGB(255, 0, 255))->createSprite(3, 1);
	_aimImage = IMAGEMANAGER->addImage("aim", "resource/aim.bmp", 48, 24, TRUE, RGB(255, 0, 255))->createSprite(2, 1);
	_circleImage = IMAGEMANAGER->addImage("circle", "resource/circle.bmp", 32, 16, TRUE, RGB(255, 0, 255))->createSprite(2, 1);

	_shooter->setCenter(WIN_SIZE_X / 2, WIN_SIZE_Y - _shooter->getFrameHeight() / 2 - 17);

	_aim[0] = new GameObject;
	_aim[1] = new GameObject;

	_aim[0]->initialize(WIN_SIZE_X / 2 - 50, WIN_SIZE_X - 75, 24, 24);
	_aim[1]->initialize(WIN_SIZE_X / 2 + 50, WIN_SIZE_X - 75, 24, 24);

	_turnScore = 0;

	_score[0] = 0;
	_score[1] = 0;
	_score[2] = 0;

	_turn = 0;
	_turnState = TURN_START;

	TIMEMANAGER->addTimer("shoot");
	TIMEMANAGER->addTimer("shoot time");
	TIMEMANAGER->addTimer("circle create");

	TIMEMANAGER->addTimer("game turn");
	TIMEMANAGER->addTimer("turn end");

	return S_OK;
}
void GameScene::release(void)
{
	SAFE_RELEASE(_shooter);
	SAFE_RELEASE(_aimImage);
	SAFE_RELEASE(_circleImage);
}
void GameScene::update(void)
{
	switch (_turnState)
	{
	case TURN_START:
		if (_turn > 2)
		{
			SCENEMANAGER->changeScene("ending");
		}
		TIMEMANAGER->checkTime("game turn", 1);
		_turnState = TURN_GAME;
		break;
	case TURN_GAME:
		if (TIMEMANAGER->checkTime("game turn", 15000))
		{
			_turnState = TURN_AFTER;
			TIMEMANAGER->checkTime("turn end", 1);
		}
		game();
		shoot();
		break;
	case TURN_AFTER:
		if (TIMEMANAGER->checkTime("turn end", 5000))
		{
			_turnState = TURN_END;
		}
		shoot();
		break;
	case TURN_END:
		_score[_turn] = _turnScore;
		_turnScore = 0;
		_turn++;
		_turnState = TURN_START;
	}

	move();
}
void GameScene::render(void)
{
	_background->render(getMemDC(), 0, 0);
	for (vector<GameObject*>::iterator i = _vCircle.begin(); i != _vCircle.end(); i++)
	{
		_circleImage->render(getMemDC(), (*i)->getRect().left, (*i)->getRect().top);
	}
	_aimImage->render(getMemDC(), _aim[0]->getRect().left, _aim[0]->getRect().top);
	_aimImage->render(getMemDC(), _aim[1]->getRect().left, _aim[1]->getRect().top);
	_shooter->render(getMemDC());

	TextOut(getMemDC(), 350, 95, to_string(_score[0]).c_str(), to_string(_score[0]).size());
	TextOut(getMemDC(), 350, 112, to_string(_score[1]).c_str(), to_string(_score[1]).size());
	TextOut(getMemDC(), 350, 129, to_string(_score[2]).c_str(), to_string(_score[2]).size());
	TextOut(getMemDC(), 150, 112, to_string(_turnScore).c_str(), to_string(_turnScore).size());
}

void GameScene::game()
{
	if (TIMEMANAGER->checkTime("circle create", 750))
	{
		GameObject* circle = new GameObject;
		if (RANDOM->getInt(2) == 0)
			circle->initialize(50, WIN_SIZE_Y - 120, 10, 10, RANDOM->getFloatTo(10, 50), RANDOM->getFloatTo(1.5, 2.5));
		else
			circle->initialize(WIN_SIZE_X - 50, WIN_SIZE_Y - 120, 10, 10, RANDOM->getFloatTo(170, 130), RANDOM->getFloatTo(1.5, 2.5));

		_vCircle.push_back(circle);
	}
}

void GameScene::shoot()
{
	RECT r;
	if (KEYMANAGER->isOnceKeyDown('S') && TIMEMANAGER->checkTime("shoot time", 200))
	{
		_shooter->setFrameX(2);
		TIMEMANAGER->checkTime("shoot", 1);

		for (vector<GameObject*>::iterator i = _vCircle.begin(); i != _vCircle.end();)
		{
			if (IntersectRect(&r, &_aim[1]->getRect(), &(*i)->getRect()))
			{
				i = _vCircle.erase(i);
				_turnScore += 100;
			}
			else
			{
				i++;
			}
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('A') && TIMEMANAGER->checkTime("shoot time", 200))
	{
		_shooter->setFrameX(1);
		TIMEMANAGER->checkTime("shoot", 1);

		for (vector<GameObject*>::iterator i = _vCircle.begin(); i != _vCircle.end();)
		{
			if (IntersectRect(&r, &_aim[0]->getRect(), &(*i)->getRect()))
			{
				i = _vCircle.erase(i);
				_turnScore += 100;
			}
			else
			{
				i++;
			}
		}
	}
	else if (TIMEMANAGER->checkTime("shoot", 100))
	{
		_shooter->setFrameX(0);
	}
}
void GameScene::move()
{
	for (vector<GameObject*>::iterator i = _vCircle.begin(); i != _vCircle.end();)
	{
		(*i)->activate(0.005);

		if ((*i)->getX() < 0 || (*i)->getX() > WIN_SIZE_X)
			i = _vCircle.erase(i);
		else
			i++;
	}

	GameObject* _neerCircle1 = NULL;
	GameObject* _neerCircle2 = NULL;
	for (vector<GameObject*>::iterator i = _vCircle.begin(); i != _vCircle.end(); i++)
	{
		if (_neerCircle1 == NULL || abs(_neerCircle1->getX() - _aim[0]->getX()) > abs((*i)->getX() - _aim[0]->getX())) _neerCircle1 = *i;
		if (_neerCircle2 == NULL || abs(_neerCircle2->getX() - _aim[1]->getX()) > abs((*i)->getX() - _aim[1]->getX())) _neerCircle2 = *i;

		if (_neerCircle1 != NULL) _aim[0]->setY(_neerCircle1->getY());
		else _aim[0]->setY(WIN_SIZE_Y - 60);
		if (_neerCircle2 != NULL) _aim[1]->setY(_neerCircle2->getY());
		else _aim[1]->setY(WIN_SIZE_Y - 60);
	}
}