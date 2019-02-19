#pragma once
class Cannon
{
private:
    POINT _position;

    float _angleR;
    float _angleD;

    int _size;
    int _length;
    POINT _cannonEndPosition;

    void setCannonEndPosition();

public:
    Cannon();
    ~Cannon();

    void moveX(int speed);
    void setAngleR(float angleR);
    float getAngleR();

    void setAngleD(float angleD);
    float getAngleD();

    POINT getEndPoint(){ return _cannonEndPosition; }
    void setPosition(POINT p){ _position = p; }
    POINT getPosition(){ return _position; }
    RECT getSize(){ return makeRectCenter(_position, _size, _size); }

};

