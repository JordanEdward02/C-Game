#pragma once
#include "MyObjectB.h"
#include "Psyjl16TileManager.h"
class MyCharacter 
    :public MyObjectB
{
public:
    MyCharacter(BaseEngine* myEngine, SimpleImage newTexture)
        :MyObjectB(myEngine, newTexture)
    {
    }

    void virtDoUpdate(int iCurrentTime);
    void reset();
    void togglePause() {
        if (isPaused)
            isPaused = false;
        else
            isPaused = true;
    }

private:
    bool isPaused = false;
};

