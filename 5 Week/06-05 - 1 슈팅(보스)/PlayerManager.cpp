#include "stdafx.h"
#include "PlayerManager.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

HRESULT PlayerManager::initialize(void)
{
	_player = new Player;
	_player->initialize();
	OBJECTMANAGER->addObject(GUID_PLAYER, _player);

	_bullet = new Bullet;
	_bullet->initialize(50, 350, 1, IMAGEMANAGER->addImage("player bullet", "resource/missile.bmp", 5, 30, TRUE, RGB(255, 0, 255)), 1, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_BULLET, _bullet);

	_missile = new Bullet;
	_missile->initialize(10, 800, 2, IMAGEMANAGER->addImage("player missile", "resource/missile2.bmp", 390, 61, TRUE, RGB(255, 0, 255)), 13, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_MISSILE, _missile);

	_tonado = new TonadoBullet;
	_tonado->initialize(100, 1000, 5, IMAGEMANAGER->addImage("player tonado", "resource/player bullet.bmp", 48, 24, TRUE, RGB(255, 0, 255)), 2, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_TONADO, _tonado);

	_piece = new PieceBullet;
	_piece->initialize(
		10, 500, 3,
		IMAGEMANAGER->addImage("player m bullet", "resource/player m bullet.bmp", 300, 30, TRUE, RGB(255, 0, 255)),
		IMAGEMANAGER->addImage("player p bullet", "resource/player bullet.bmp", 48, 24, TRUE, RGB(255, 0, 255)),
		8, 1, 2, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_PIECE, _piece);

	_bulletTimer = new Timer;
	_bulletTimer->initialize(120);

	_missileTimer = new Timer;
	_missileTimer->initialize(200);

	return S_OK;
}
void PlayerManager::release(void)
{
	_player->release();
	_bullet->release();
	_missile->release();
	_tonado->release();
	_piece->release();
}
void PlayerManager::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getRect().left > 0)
	{
		_player->setX(_player->getX() - 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getRect().right < WIN_SIZE_X)
	{
		_player->setX(_player->getX() + 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _player->getRect().top > 0)
	{
		_player->setY(_player->getY() - 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player->getRect().bottom < WIN_SIZE_Y)
	{
		_player->setY(_player->getY() + 3);
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_bulletTimer->getTiming())
		{
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 3, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 1, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 1.5, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 2.5, 10);
		}
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_missileTimer->getTiming())
		{
			_missile->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 3);
		}
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_missileTimer->getTiming())
		{
			_tonado->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 3);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_piece->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 3);
	}
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		_piece->popBullet();
	}

	_player->update();
	_bullet->update();
	_missile->update();
	_tonado->update();
	_piece->update();

	//利 醚舅苞 面倒贸府
	Bullet* eBullet = OBJECTMANAGER->findObject<Bullet>(GUID_ENEMYS_BULLET);
	Bullet::VPBullet* vEBullet = eBullet->getBullets();
	Bullet::VIPBullet viEBullet;
	RECT r;

	for (viEBullet = vEBullet->begin(); viEBullet != vEBullet->end();)
	{
		if (IntersectRect(&r, &_player->getRect(), &(*viEBullet)->getRect()))
		{
			viEBullet = vEBullet->erase(viEBullet);
			_player->setHp(_player->getHp() - 1);
		}
		else
		{
			viEBullet++;
		}
	}

	if (_player->getHp() <= 0)
	{
		//_player->release();
		//SAFE_DELETE(_player);
	}
}
void PlayerManager::render()
{
	_player->render();
	_bullet->render();
	_missile->render();
	_tonado->render();
	_piece->render();
}