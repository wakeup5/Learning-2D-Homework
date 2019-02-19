#include "stdafx.h"
#include "Player.h"


Player::Player()
{

}


Player::~Player()
{
}

bool Player::fire(Enemy* e)
{
	switch (_weaponMode)
	{
	case 0:
		return fireBasic();
	case 1:
		return fireSpecial1();
	case 2:
		return fireSpecial2();
	case 3:
		return fireSpecial3(e);
	}

	return false;
}

bool Player::fireBasic()
{
	if (_cooltimeBasic <= 0)
	{
		for (int i = 0; i < _maxBasic; i++)
		{
			if (_basicBullets[i].getIsFire()) continue;

			_basicBullets[i].setPosition(makePoint(this->getPosition().x, this->getPosition().y - _width));
			_basicBullets[i].setIsFire(true);
			_basicBullets[i].setSpeed(SPEED_BASIC);
			_cooltimeBasic = COOLTIME_BASIC;
			return true;
		}
	}
	else if (_cooltimeBasic > 0)
	{
		_cooltimeBasic -= 10;
	}
	
	return false;
}


bool Player::fireSpecial1()
{
	if (_cooltimeSpecial1 <= 0)
	{
		int j = 0;
		Missile *selectMissile[5];
		for (int i = 0; i < _maxSpecial1 && j < 5; i++)
		{
			if (!_special1Bullets[i].getIsFire())
			{
				selectMissile[j] = &_special1Bullets[i];
				j++;
			}
		}

		if (j == 5)
		{
			for (int i = 0; i < 5; i++)
			{
				selectMissile[i]->setPosition(makePoint(this->getPosition().x, this->getPosition().y - _width));
				selectMissile[i]->setDegree(40 - (20 * i));
				selectMissile[i]->setIsFire(true);
				selectMissile[i]->setSpeed(SPEED_SPECIAL_1);
			}
			_cooltimeSpecial1 = COOLTIME_SPECIAL_1;
			return true;
		}
	}
	else if (_cooltimeSpecial1 > 0)
	{
		_cooltimeSpecial1 -= 10;
	}
	return false;
}

bool Player::fireSpecial2()
{
	if (_cooltimeSpecial2L <= 0 && _smallLeftHp > 0)
	{
		for (int i = 0; i < _maxSpecial2; i++)
		{
			if (_special2LBullets[i].getIsFire()) continue;

			_special2LBullets[i].setPosition(makePoint(_smallLeft.getPosition().x, _smallLeft.getPosition().y - _width));
			_special2LBullets[i].setIsFire(true);
			_special2LBullets[i].setSpeed(SPEED_SPECIAL_2);
			_cooltimeSpecial2L = COOLTIME_SPECIAL_2;
			break;
		}
	}
	else
	{
		_cooltimeSpecial2L -= 10;
	}

	if (_cooltimeSpecial2R <= 0 && _smallRightHp > 0)
	{
		for (int i = 0; i < _maxSpecial2; i++)
		{
			if (_special2RBullets[i].getIsFire()) continue;

			_special2RBullets[i].setPosition(makePoint(_smallRight.getPosition().x, _smallRight.getPosition().y - _width));
			_special2RBullets[i].setIsFire(true);
			_special2RBullets[i].setSpeed(SPEED_SPECIAL_2);
			_cooltimeSpecial2R = COOLTIME_SPECIAL_2;
			break;
		}
	}
	else
	{
		_cooltimeSpecial2R -= 10;
	}

	return fireBasic();
}

bool Player::fireSpecial3(Enemy* e)
{
	if (_cooltimeSpecial3 <= 0)
	{
		for (int i = 0; i < _maxSpecial3; i++)
		{
			if (_special3Bullets[i].getIsFire()) continue;
			_special3Bullets[i].setEnemy(e);
			_special3Bullets[i].setSpeed(SPEED_SPECIAL_3);
			_special3Bullets[i].setIsFire(true);
			
			POINT p = getPosition();
			if (i % 2 == 0)
			{
				p.x += 20;
				_special3Bullets[i].setPosition(p);
				_special3Bullets[i].setDegree(-90);
			}
			else
			{
				p.x -= 20;
				_special3Bullets[i].setPosition(p);
				_special3Bullets[i].setDegree(90);
			}

			_cooltimeSpecial3 = COOLTIME_SPECIAL_3;

			//return true;
			break;
		}
	}
	else
	{
		_cooltimeSpecial3 -= 10;
	}

	return fireBasic();
}

void Player::update()
{
	for (int i = 0; i < _maxBasic; i++)
	{
		if (!_basicBullets[i].getIsFire()) continue;
		_basicBullets[i].move();

		if (_basicBullets[i].getPosition().y < 0) _basicBullets[i].setIsFire(false);
	}

	for (int i = 0; i < _maxSpecial1; i++)
	{
		if (_special1Bullets[i].getIsFire())
		{
			_special1Bullets[i].move();
			if (_special1Bullets[i].getPosition().y < 0) _special1Bullets[i].setIsFire(false);
		}
	}

	if (_weaponMode == 2)
	{
		if (_smallLeft.getPosition().x > getPosition().x - 30) _smallLeft.moveX(-2);
		if (_smallRight.getPosition().x < getPosition().x + 30) _smallRight.moveX(2);
		_smallLeftHp -= 0.2;
		_smallRightHp -= 0.2;
		if (_smallLeftHp < 0 && _smallRightHp < 0)
		{
			_weaponMode = 0;
			_special2Cooltime = SPECIAL_2_COOLTIME;
		}
	}

	for (int i = 0; i < _maxSpecial2; i++)
	{
		if (_special2LBullets[i].getIsFire())
		{
			_special2LBullets[i].move();
			if (_special2LBullets[i].getPosition().y < 0) _special2LBullets[i].setIsFire(false);
		}
	}
	for (int i = 0; i < _maxSpecial2; i++)
	{
		if (_special2RBullets[i].getIsFire())
		{
			_special2RBullets[i].move();
			if (_special2RBullets[i].getPosition().y < 0) _special2RBullets[i].setIsFire(false);
		}
	}

	if (_special2Cooltime > 0)
	{
		_special2Cooltime -= 10;
	}

	for (int i = 0; i < _maxSpecial3; i++)
	{
		if (_special3Bullets[i].getIsFire())
		{
			_special3Bullets[i].guideMove();
			if (_special3Bullets[i].getPosition().y < 0 || _special3Bullets[i].getPosition().y > WIN_SIZE_Y ||
				_special3Bullets[i].getPosition().x < 0 || _special3Bullets[i].getPosition().x > WIN_SIZE_X) _special3Bullets[i].setIsFire(false);
		}
	}

	if (_shieldCooltime > 0)
	{
		_shieldCooltime -= 10;
	}

	if (_shieldHp > 0)
	{
		_shieldHp -= 1;
		if (_shieldHp <= 0)
		{
			_shieldCooltime = SHIELD_COOLTIME;
		}
	}

}

void Player::printBullet(HDC hdc)
{
	if (_shieldHp > 0)
	{
		drawEllipseCenter(hdc, getPosition(), 100, 100);
		Rectangle(hdc, getPosition().x - 50, getPosition().y - 60, getPosition().x - 50 + (100 * (float)_shieldHp / SHIELD_HP), getPosition().y - 58);
	}

	for (int i = 0; i < _maxBasic; i++)
	{
		if (!_basicBullets[i].getIsFire()) continue;
		drawEllipse(hdc, _basicBullets[i].getSize());
	}

	for (int i = 0; i < _maxSpecial1; i++)
	{
		if (!_special1Bullets[i].getIsFire()) continue;
		drawEllipse(hdc, _special1Bullets[i].getSize());
	}

	if (_weaponMode == 2)
	{
		if (_smallLeftHp > 0)
		{
			RECT r = _smallLeft.getSize();
			drawEllipse(hdc, r);
			Rectangle(hdc, r.left - 2, r.bottom + 2, r.left + (12 * _smallLeftHp / 100), r.bottom + 4);
		}
		if (_smallRightHp > 0)
		{
			RECT r = _smallRight.getSize();
			drawEllipse(hdc, r);
			Rectangle(hdc, r.left - 2, r.bottom + 2, r.left + (12 * _smallRightHp / 100), r.bottom + 4);
		}
	}

	for (int i = 0; i < _maxSpecial2; i++)
	{
		if (!_special2LBullets[i].getIsFire()) continue;
		drawEllipse(hdc, _special2LBullets[i].getSize());
	}
	for (int i = 0; i < _maxSpecial2; i++)
	{
		if (!_special2RBullets[i].getIsFire()) continue;
		drawEllipse(hdc, _special2RBullets[i].getSize());
	}

	for (int i = 0; i < _maxSpecial3; i++)
	{
		if (!_special3Bullets[i].getIsFire()) continue;
		drawEllipse(hdc, _special3Bullets[i].getSize());
	}

	TCHAR weaponStr[128];
	sprintf_s(weaponStr, "1(basic)");
	TextOut(hdc, 10, WIN_SIZE_Y - 140, weaponStr, _tcslen(weaponStr));

	sprintf_s(weaponStr, "2(S1)");
	TextOut(hdc, 10, WIN_SIZE_Y - 120, weaponStr, _tcslen(weaponStr));

	sprintf_s(weaponStr, "3(S2) %d", _special2Cooltime);
	TextOut(hdc, 10, WIN_SIZE_Y - 100, weaponStr, _tcslen(weaponStr));

	sprintf_s(weaponStr, "4(S3)");
	TextOut(hdc, 10, WIN_SIZE_Y - 80, weaponStr, _tcslen(weaponStr));

	sprintf_s(weaponStr, "5(SD) %d", _shieldCooltime);
	TextOut(hdc, 10, WIN_SIZE_Y - 60, weaponStr, _tcslen(weaponStr));

	TCHAR modeStr[128];
	if (_weaponMode == 0)
	{
		sprintf_s(modeStr, "Mode - Basic");
	}
	else if (_weaponMode == 1)
	{
		sprintf_s(modeStr, "Mode - Special 1 (5 way attack)");
	}
	else if(_weaponMode == 2)
	{
		sprintf_s(modeStr, "Mode - special 2 (2 small plane)");
	}
	else if(_weaponMode == 3)
	{
		sprintf_s(modeStr, "Mode - special 3 (guide missile)");
	}
	TextOut(hdc, 10, WIN_SIZE_Y - 30, modeStr, _tcslen(modeStr));

}

void Player::setMode(int i)
{
	if (i == 1)
	{
		_weaponMode = 1;
	}
	else if (i == 2)
	{
		if (_weaponMode != 2)
		{
			_smallLeft.setPosition(getPosition());
			_smallLeft.setSize(10, 15);
			_smallLeftHp = 100;
			_smallRight.setPosition(getPosition());
			_smallRight.setSize(10, 15);
			_smallRightHp = 100;
		}
		if (_special2Cooltime <= 0)
		{
			_weaponMode = 2;
		}
	}
	else if (i == 3)
	{
		_weaponMode = 3;
	}
	//else if (i == 4)
	//{
	//	_weaponMode = 4;
	//}
	else
	{
		_weaponMode = 0;
	}
}

void Player::move(int x, int y)
{
	GameObject::move(x, y); 
	if (_weaponMode == 2)
	{
		_smallLeft.move(x, y);
		_smallRight.move(x, y);
	}
}

bool Player::collision(RECT enemy)
{
	for (int i = 0; i < _maxBasic; i++)
	{
		if (_basicBullets[i].getIsFire() && isCollisionRectangle(_basicBullets[i].getSize(), enemy))
		{
			_basicBullets[i].setIsFire(false);
			return true;
		}
	}
	for (int i = 0; i < _maxSpecial1; i++)
	{
		if (_special1Bullets[i].getIsFire() && isCollisionRectangle(_special1Bullets[i].getSize(), enemy))
		{
			_special1Bullets[i].setIsFire(false);
			return true;
		}
	}

	for (int i = 0; i < _maxSpecial2; i++)
	{
		if (_special2LBullets[i].getIsFire() && isCollisionRectangle(_special2LBullets[i].getSize(), enemy))
		{
			_special2LBullets[i].setIsFire(false);
			return true;
		}
	}
	for (int i = 0; i < _maxSpecial2; i++)
	{
		if (_special2RBullets[i].getIsFire() && isCollisionRectangle(_special2RBullets[i].getSize(), enemy))
		{
			_special2RBullets[i].setIsFire(false);
			return true;
		}
	}

	for (int i = 0; i < _maxSpecial3; i++)
	{
		if (_special3Bullets[i].getIsFire() && isCollisionRectangle(_special3Bullets[i].getSize(), enemy))
		{
			_special3Bullets[i].setIsFire(false);
			return true;
		}
	}

	if (isCollisionRectangle(enemy, getSize()))
	{
		damageHp();
		return true;
	}

	if (isCollisionRectangle(enemy, _smallLeft.getSize()))
	{
		_smallLeftHp -= 25;
		return true;
	}

	if (isCollisionRectangle(enemy, _smallRight.getSize()))
	{
		_smallRightHp -= 25;
		return true;
	}

	if (_shieldHp > 0 && isCollisionEllipse(enemy, makeRectCenter(getPosition(), 100, 100)))
	{
		shieldDamage();
		return true;
	}

	return false;
}

void Player::damageHp()
{
	_hp -= 25.0;
	if (_hp < 0)
	{
		_hp = 0;
		_isDead = true;
	}
}
void Player::recoveryHp()
{
	if (_hp < 100 && _hp > 0)
		_hp += 0.1;
}

void Player::shield()
{
	if (_shieldCooltime <= 0 && _shieldHp <= 0)
	{
		_shieldHp = SHIELD_HP;
	}
}

void Player::shieldDamage()
{
	if (_shieldHp > 0)
	{
		_shieldHp -= 25;
		if (_shieldHp <= 0)
		{
			_shieldCooltime = SHIELD_COOLTIME;
		}
	}
}