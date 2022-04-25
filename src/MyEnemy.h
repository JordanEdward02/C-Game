#pragma once
#include "MyObjectB.h"
#include "UtilMovementPosition.h"
#include "ImageManager.h"
#include "SimpleImage.h"

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
        imageSize = 32;
    }
    void stun();
    void reset();
    void virtDoUpdate(int iCurrentTime);

protected:
    MyObjectB* MyTarget;
    MovementPosition m_oMovement;
    int movementCalc, moveDuration, moveStartTime;
    int stunTime;
};

