#pragma once
class Tank
{
private:
    float _x, _y;
    float _angleR;

    int _size;
    int _speed;

    float _cannonAngleR;

    int _cannonSize;
public:
    Tank();
    ~Tank();

    void setPosition(float x, float y){ _x = x; _y = y; }
    POINT getPosition(){ return POINT{ _x, _y }; }

    void setAngleR(float angleR){ _angleR = angleR; }
    float getAngleR(){ return _angleR; }

    void setCannonAngleR(float cannonAngleR){ _cannonAngleR = cannonAngleR; }
    float getCannonAngleR(){ return _cannonAngleR; }

    POINT getCannonEndPoint(){ return POINT{ _x + _cannonSize * cos(_cannonAngleR), _y - _cannonSize * sin(_cannonAngleR) }; }
    void setCannonSize(int size){ _cannonSize = size; }
    void setSize(int size){ _size = size; }
    int getSize(){ return _size; }
    void setSpeed(int speed){ _speed = speed; }

    void moveFront();
    void moveBack();
    void printTank(HDC);

    bool isLive = false;
};

