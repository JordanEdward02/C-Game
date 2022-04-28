#pragma once
#include "MyObjectB.h"
#include "BaseEngine.h"
class Fire :
    public MyObjectB
{
public:
    Fire(BaseEngine* myEngine, SimpleImage newTexture, int Time, MyObjectB* playerObject);

    void virtDoUpdate(int iCurrentTime);
private:
    int creationTime;
    MyObjectB* target;
};

