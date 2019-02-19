#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}


RECT GameObject::getSize()
{
	return makeRectCenter(_point, _width, _height);
}

void GameObject::move(int x, int y)
{
	_point.x += x;
	_point.y += y;
}
void GameObject::moveX(int x)
{
	move(x, 0);
}
void GameObject::moveY(int y)
{
	move(0, y);
}