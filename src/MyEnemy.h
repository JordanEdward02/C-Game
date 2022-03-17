#pragma once
#include "MyObjectB.h"
#include "UtilMovementPosition.h"
class MyEnemy :
    public MyObjectB
{
public:
    MyEnemy(BaseEngine* myEngine, SimpleImage newTexture, MyObjectB* newTarget, int startTime)
        :MyObjectB(myEngine, newTexture),
        movementCalc(0),
        stunTime(startTime)
    {
        MyTarget = newTarget;
    }
    void stun();
    void reset();
    void virtDoUpdate(int iCurrentTime);

protected:
    MyObjectB* MyTarget;
    MovementPosition m_oMovement;
    int movementCalc;
    int stunTime;
};

