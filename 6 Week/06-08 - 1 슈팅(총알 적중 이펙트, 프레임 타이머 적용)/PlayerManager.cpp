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
	_bullet->initialize(50, 350, 1, IMAGEMANAGER->findImage("player bullet"), 1, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_BULLET, _bullet);

	_missile = new Bullet;
	_missile->initialize(10, 800, 2, IMAGEMANAGER->findImage("player missile"), 13, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_MISSILE, _missile);

	_tonado = new TonadoBullet;
	_tonado->initialize(100, 1000, 5, IMAGEMANAGER->findImage("player tonado"), 2, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_TONADO, _tonado);

	_piece = new PieceBullet;
	_piece->initialize(
		10, 500, 3,
		IMAGEMANAGER->findImage("player m bullet"),
		IMAGEMANAGER->findImage("player p bullet"),
		8, 1, 2, 1);
	OBJECTMANAGER->addObject(GUID_PLAYER_PIECE, _piece);

	return S_OK;
}
void PlayerManager::release(void)
{
	if (_player) _player->release();
	_bullet->release();
	_missile->release();
	_tonado->release();
	_piece->release();
}
void PlayerManager::update(void)
{
	if (_player)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getRect().left > 0)
		{
			_player->setX(_player->getX() - 3 * TIMEMANAGER->getElapsedTime() * 100);
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getRect().right < WIN_SIZE_X)
		{
			_player->setX(_player->getX() + 3 * TIMEMANAGER->getElapsedTime() * 100);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && _player->getRect().top > 0)
		{
			_player->setY(_player->getY() - 3 * TIMEMANAGER->getElapsedTime() * 100);
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _player->getRect().bottom < WIN_SIZE_Y)
		{
			_player->setY(_player->getY() + 3 * TIMEMANAGER->getElapsedTime() * 100);
		}

		if (KEYMANAGER->isStayKeyDown('A') && TIMEMANAGER->addTimer("player bullet")->checkTime(150))
		{
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 3, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 1, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 1.5, 10);
			_bullet->fire(_player->getX(), _player->getY() - 50, M_PI / 4 * 2.5, 10);
		}
		if (KEYMANAGER->isStayKeyDown('S') && TIMEMANAGER->addTimer("player missile")->checkTime(250))
		{
			_missile->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 3);
		}
		if (KEYMANAGER->isStayKeyDown('D') && TIMEMANAGER->addTimer("player tonado")->checkTime(170))
		{
			_tonado->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 3);
		}
		if (KEYMANAGER->isOnceKeyDown('F') && TIMEMANAGER->addTimer("player piece")->checkTime(250))
		{
			_piece->fire(_player->getX(), _player->getY() - 50, M_PI / 2, 3);
		}
		if (KEYMANAGER->isOnceKeyDown('G'))
		{
			_piece->popBullet();
		}

		_player->update();

		if (_player->getHp() <= 0)
		{
			if (_player) _player->release();
			SAFE_DELETE(_player);
			OBJECTMANAGER->removeObject(GUID_PLAYER);
		}
	}

	_bullet->update();
	_missile->update();
	_tonado->update();
	_piece->update();

	//利 醚舅苞 面倒贸府
	Bullet* eBullet = OBJECTMANAGER->findObject<Bullet>(GUID_ENEMYS_BULLET);
	Bullet::VPBullet* vEBullet = eBullet->getBullets();
	Bullet::VIPBullet viEBullet;
	RECT r;

	Bullet::collitionCheck<Player>(_player, vEBullet, [](Player* player, Bullet::BulletObject* bullet){
		player->setHp(player->getHp() - bullet->getDamage());
		SpriteImage* effect = IMAGEMANAGER->findImage("bullet down effect")->getSpriteImage(bullet->getX(), bullet->getRect().bottom, 15, 1);
		EFFECTMANAGER->addEffect(effect);
	});

}
void PlayerManager::render()
{
	if (_player) _player->render();
	_bullet->render();
	_missile->render();
	_tonado->render();
	_piece->render();
}