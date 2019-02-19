#include "stdafx.h"
#include "JangGi.h"
using namespace std;
inline float getCoorXByPointX(const long x){
	return WIN_SIZE_X / 2 + ((x - 4) * 55);
}
inline float getCoorYByPointY(const long y){
	return WIN_SIZE_Y / 2 + ((y - 4) * 50) - 25;
}
inline int changeCamp(int camp){
	return (camp + 1) & 1;
}
JangGi::JangGi():_turn(BLUE), _turnState(PLAY_TURN_START), _isGameEnd(false), _isJangGun(false), _jangGunCamp(RED){}
HRESULT JangGi::initialize(){
	_backImage = IMAGEMANAGER->findImage("janggi back");
	_backImage->setCenter(WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	for (int i = 0; i < 2; i++) {
		_mal[i][0] = new JangGiMal(4, (i == BLUE) ? 9 - 1 : 1, KING, CAMP(i));
		_mal[i][1] = new JangGiMal(3, (i == BLUE) ? 9 - 0 : 0, OFFICER, CAMP(i));
		_mal[i][2] = new JangGiMal(5, (i == BLUE) ? 9 - 0 : 0, OFFICER, CAMP(i));
		_mal[i][3] = new JangGiMal(0, (i == BLUE) ? 9 - 0 : 0, CAR, CAMP(i));
		_mal[i][4] = new JangGiMal(8, (i == BLUE) ? 9 - 0 : 0, CAR, CAMP(i));
		_mal[i][5] = new JangGiMal(1, (i == BLUE) ? 9 - 0 : 0, HORSE, CAMP(i));
		_mal[i][7] = new JangGiMal(6, (i == BLUE) ? 9 - 0 : 0, HORSE, CAMP(i));
		_mal[i][6] = new JangGiMal(7, (i == BLUE) ? 9 - 0 : 0, ELEPHANT, CAMP(i));
		_mal[i][8] = new JangGiMal(2, (i == BLUE) ? 9 - 0 : 0, ELEPHANT, CAMP(i));
		_mal[i][9] = new JangGiMal(1, (i == BLUE) ? 9 - 2 : 2, CANNON, CAMP(i));
		_mal[i][10] = new JangGiMal(7, (i == BLUE) ? 9 - 2 : 2, CANNON, CAMP(i));
		for (int j = 0; j < 5; j++)
			_mal[i][11 + j] = new JangGiMal(0 + (2 * j), (i == BLUE) ? 9 - 3 : 3, SOLDIER, CAMP(i));
	}
	for (int i = 0; i < 10; i++) for (int j = 0; j < 9; j++) _pan[i][j] = new JangGiPan(makeRectCenter(getCoorXByPointX(j), getCoorYByPointY(i), 30, 30));
	for (int i = 0; i < 2; i++) for (int j = 0; j < 16; j++) _pan[_mal[i][j]->getY()][_mal[i][j]->getX()]->mal = _mal[i][j];
	return S_OK;
}
void JangGi::release(){
	for (int i = 0; i < 2; i++) for (int j = 0; j < 16; j++) SAFE_RELEASE(_mal[i][j]);
}
void JangGi::update(){
	if (_isGameEnd) return;
	switch (_turnState){
	case PLAY_TURN_START: 
		selectMal(); 
		break;
	case PLAY_MAL_CLICK: 
		moveMal(); 
		break;
	case PLAY_MAL_MOVE: 
		changeTurn(); 
	case PLAY_MAL_MOVE_FAIL: 
		_turnState = PLAY_TURN_START; 
		break;
	}
}
list<POINT> JangGi::movablePoint(JangGiMal* mal){
	list<POINT> lPoint;
	if (mal->getKind() == ELEPHANT || mal->getKind() == HORSE) { //»ó¸¶ÀÏ¶§
		addMovablePoint(mal->getX() - 1, mal->getY(), ((mal->getKind() == ELEPHANT) ? 3 : 2), ((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
		addMovablePoint(mal->getX() - 1, mal->getY(), ((mal->getKind() == ELEPHANT) ? 3 : 2), -((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
		addMovablePoint(mal->getX() + 1, mal->getY(), -((mal->getKind() == ELEPHANT) ? 3 : 2), ((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
		addMovablePoint(mal->getX() + 1, mal->getY(), -((mal->getKind() == ELEPHANT) ? 3 : 2), -((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() - 1, ((mal->getKind() == ELEPHANT) ? 3 : 2), ((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() - 1, -((mal->getKind() == ELEPHANT) ? 3 : 2), ((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() + 1, ((mal->getKind() == ELEPHANT) ? 3 : 2), -((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY() + 1, -((mal->getKind() == ELEPHANT) ? 3 : 2), -((mal->getKind() == ELEPHANT) ? 3 : 2), mal, &lPoint);
	} else if (mal->getKind() == KING || mal->getKind() == OFFICER) { //±Ã »çÀÏ¶§
		if ((mal->getCamp() == RED && mal->getY() < 2) || (mal->getCamp() == BLUE && mal->getY() < 9)) addMovablePoint(mal->getX(), mal->getY(), 0, 1, mal, &lPoint);
		if ((mal->getCamp() == RED && mal->getY() > 0) || (mal->getCamp() == BLUE && mal->getY() > 7)) addMovablePoint(mal->getX(), mal->getY(), 0, -1, mal, &lPoint);
		if (mal->getX() < 5) addMovablePoint(mal->getX(), mal->getY(), 1, 0, mal, &lPoint);
		if (mal->getX() > 3) addMovablePoint(mal->getX(), mal->getY(), -1, 0, mal, &lPoint);
		if (((mal->getY() == 2 || mal->getY() == 9) || (mal->getY() == 0 || mal->getY() == 7)) && (mal->getX() == 5 || mal->getX() == 3))
			addMovablePoint(mal->getX(), mal->getY(), ((mal->getX() == 3) ? 1 : -1), ((mal->getY() == 0 || mal->getY() == 7) ? 1 : -1), mal, &lPoint);
		if ((mal->getY() == 1 || mal->getY() == 8) && mal->getX() == 4)
			for (int i = 0; i < 4; i++) addMovablePoint(mal->getX(), mal->getY(), ((i / 2 == 0) ? 1 : -1), ((i % 2 == 0) ? 1 : -1), mal, &lPoint);
	} else if (mal->getKind() == SOLDIER) { //Á¹º´ÀÏ¶§
		addMovablePoint(mal->getX(), mal->getY(), 0, ((mal->getCamp() == RED) ? 1 : -1), mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY(), 1, 0, mal, &lPoint);
		addMovablePoint(mal->getX(), mal->getY(), -1, 0, mal, &lPoint);
		if ((((mal->getCamp() == BLUE && mal->getY() == 2) || mal->getY() == 9) || (mal->getY() == 0 || (mal->getCamp() == RED && mal->getY() == 7))) && (mal->getX() == 5 || mal->getX() == 3))
			addMovablePoint(mal->getX(), mal->getY(), ((mal->getX() == 3) ? 1 : -1), ((mal->getY() == 0 || mal->getY() == 7) ? 1 : -1), mal, &lPoint);
		if (((mal->getCamp() == BLUE && mal->getY() == 1) || (mal->getCamp() == RED && mal->getY() == 8)) && mal->getX() == 4)
			for (int i = 0; i < 2; i++) addMovablePoint(mal->getX(), mal->getY(), ((i == 0) ? 1 : -1), ((mal->getCamp() == RED) ? 1 : -1), mal, &lPoint);
	} else { //Â÷ Æ÷ ÀÏ¶§
		for (int i = 0; i < 9; i++) addMovablePoint(mal->getX(), mal->getY(), i - mal->getX(), 0, mal, &lPoint);
		for (int i = 0; i < 10; i++) addMovablePoint(mal->getX(), mal->getY(), 0, i - mal->getY(), mal, &lPoint);
		if (((mal->getY() == 2 || mal->getY() == 9) || (mal->getY() == 0 || mal->getY() == 7)) && (mal->getX() == 5 || mal->getX() == 3)){
			addMovablePoint(mal->getX(), mal->getY(), ((mal->getX() == 3) ? 1 : -1), ((mal->getY() == 0 || mal->getY() == 7) ? 1 : -1), mal, &lPoint);
			addMovablePoint(mal->getX(), mal->getY(), ((mal->getX() == 3) ? 2 : -2), ((mal->getY() == 0 || mal->getY() == 7) ? 2 : -2), mal, &lPoint);
		}
		if ((mal->getY() == 1 || mal->getY() == 8) && mal->getX() == 4)
			for (int i = 0; i < 4; i++) addMovablePoint(mal->getX(), mal->getY(), ((i / 2 == 0) ? 1 : -1), ((i % 2 == 0) ? 1 : -1), mal, &lPoint);
	}
	return lPoint;
}
bool JangGi::checkMovablePoint(int startX, int startY, int endX, int endY, JangGiMal *mal){
	if (endX < 0 || endX > 8 || endY < 0 || endY > 9) return false;
	startX += (startX == endX) ? 0 : ((endX - startX) / abs(endX - startX));
	startY += (startY == endY) ? 0 : ((endY - startY) / abs(endY - startY));
	if ((startY == endY) && (startX == endX))
		if (_pan[startY][startX]->mal != NULL)
			if (_pan[startY][startX]->mal->getCamp() == mal->getCamp())	return false;
			else return true;
		else return true;
	else
		if (_pan[startY][startX]->mal != NULL) return false;
		else return checkMovablePoint(startX, startY, endX, endY, mal);
}
bool JangGi::checkMovablePointByCannon(int startX, int startY, int endX, int endY, JangGiMal *mal, bool isExistWall){
	if (endX < 0 || endX > 8 || endY < 0 || endY > 9) return false;
	startX += (startX == endX) ? 0 : ((endX - startX) / abs(endX - startX));
	startY += (startY == endY) ? 0 : ((endY - startY) / abs(endY - startY));
	if (startX == endX && startY == endY)
		if (isExistWall)
			if (_pan[startY][startX]->mal != NULL)
				if (_pan[startY][startX]->mal->getCamp() == mal->getCamp()) return false;
				else
					if (_pan[startY][startX]->mal->getKind() == CANNON)	return false;
					else return true;
			else return true;
		else return false;
	else
		if (isExistWall)
			if (_pan[startY][startX]->mal != NULL) return false;
			else return checkMovablePointByCannon(startX, startY, endX, endY, mal, true);
		else
			if (_pan[startY][startX]->mal != NULL)
				if (_pan[startY][startX]->mal->getKind() != CANNON) return checkMovablePointByCannon(startX, startY, endX, endY, mal, true);
				else return false;
			else return checkMovablePointByCannon(startX, startY, endX, endY, mal, false);
}
void JangGi::addMovablePoint(int malX, int malY, int moveX, int moveY, JangGiMal* mal, std::list<POINT> * lPoint){
	if ((mal->getKind() == CANNON && checkMovablePointByCannon(malX, malY, malX + moveX, malY + moveY, mal, false)) ||
		(mal->getKind() != CANNON && checkMovablePoint(malX, malY, malX + moveX, malY + moveY, mal))) 
		lPoint->push_back(makePoint(malX + moveX, malY + moveY));
}
void JangGi::render(){
	_backImage->render(getMemDC(), (WIN_SIZE_X - _backImage->getWidth()) / 2, (WIN_SIZE_Y - _backImage->getHeight()) / 2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 16; j++) _mal[i][j]->getImage()->render(getMemDC());
	for (list<POINT>::iterator liPoint = _movablePoint.begin(); liPoint != _movablePoint.end(); liPoint++) 
		_selectMal->getImage()->render(getMemDC(), getCoorXByPointX(liPoint->x) - _selectMal->getImage()->getFrameWidth() / 2, getCoorYByPointY(liPoint->y) - _selectMal->getImage()->getFrameHeight() / 2, 100);
	if (_isGameEnd) TextOut(getMemDC(), WIN_SIZE_X / 2, WIN_SIZE_Y / 2, (_turn == RED ? "Àû½Â" : "Ã»½Â"), strlen((_turn == RED ? "Àû½Â" : "Ã»½Â")));
	if (_isJangGun) TextOut(getMemDC(), WIN_SIZE_X / 2, (_jangGunCamp == BLUE ? 200 : WIN_SIZE_Y - 200), "Àå±º!", strlen("Àå±º!"));
}
void JangGi::changeTurn(){
	_turn = (CAMP)changeCamp(_turn);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 9; j++)
			if (_pan[i][j]->mal != NULL)	{
				list<POINT> lPoint = movablePoint(_pan[i][j]->mal);
				_isJangGun = false;
				for (list<POINT>::iterator iter = lPoint.begin(); iter != lPoint.end(); iter++)
					if (_pan[iter->y][iter->x]->mal != NULL && _pan[iter->y][iter->x]->mal->getKind() == KING) {
						_jangGunCamp = _pan[iter->y][iter->x]->mal->getCamp();
						_isJangGun = true;
						return;
					}
			}
}
void JangGi::selectMal(){
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_backImage->boundingBox(), _mousePoint))
		for (int i = 0; i < 16; i++)
			if (PtInRect(&_mal[_turn][i]->getImage()->getRect(), _mousePoint)){
				_selectMal = _mal[_turn][i];
				_movablePoint = movablePoint(_selectMal);
				_turnState = PLAY_MAL_CLICK;
				return;
			}
}
void JangGi::moveMal(){
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && PtInRect(&_backImage->boundingBox(), _mousePoint)){
		for (list<POINT>::iterator liPoint = _movablePoint.begin(); liPoint != _movablePoint.end(); liPoint++)
			if (PtInRect(&_pan[liPoint->y][liPoint->x]->rc, _mousePoint) && !(_selectMal->getY() == liPoint->y && _selectMal->getX() == liPoint->x)) {
				if (_pan[liPoint->y][liPoint->x]->mal != NULL) takeMal(_pan[liPoint->y][liPoint->x]->mal);
				_pan[_selectMal->getY()][_selectMal->getX()]->mal = NULL;
				_selectMal->move(makePoint(liPoint->x, liPoint->y));
				_pan[liPoint->y][liPoint->x]->mal = _selectMal;
				_movablePoint.clear();
				_turnState = PLAY_MAL_MOVE;
				return;
			}
		_movablePoint.clear();
		_turnState = PLAY_MAL_MOVE_FAIL;
	}
}
void JangGi::takeMal(JangGiMal* mal){
	mal->move((changeCamp(_turn) == RED) ? (makePoint(10, 9 - _takeMal[changeCamp(_turn)]++)) : (makePoint(-2, _takeMal[changeCamp(_turn)]++)));
	if (mal->getKind() == KING) _isGameEnd = true;
}
JangGiMal::JangGiMal(const int x, const int y, const JANGGIMAL mal, const CAMP camp) : _x(x), _y(y), _kind(mal), _camp(camp){
	_image = IMAGEMANAGER->findImage("janggi mal")->createSprite(getCoorXByPointX(_x), getCoorYByPointY(_y), 7, 2, _kind, _camp);
}
void JangGiMal::release(){
	SAFE_RELEASE(_image);
}
void JangGiMal::move(POINT point){
	_image->setCenter(getCoorXByPointX(_x = point.x), getCoorYByPointY(_y = point.y));
}