#pragma once
#include "MyObjectB.h"
#include "BaseEngine.h"
class AntKiller :
    public MyObjectB
{
public:
    AntKiller(BaseEngine* myEngine, SimpleImage newTexture, int Time);

    void virtDoUpdate(int iCurrentTime);
private:
    int creationTime;
};

