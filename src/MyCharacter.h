#pragma once
#include "MyObjectB.h"
#include "Psyjl16TileManager.h"
#include "ImagePixelMapping.h"
class MyCharacter 
    :public MyObjectB
{
public:
    MyCharacter(BaseEngine* myEngine, SimpleImage newTexture)
        :MyObjectB(myEngine, newTexture)
    {
        imageSize = 16;
    }

    void virtDoUpdate(int iCurrentTime);
    void reset();
    void togglePause() {
        if (isPaused)
            isPaused = false;
        else
            isPaused = true;
    }
    int getFutureX() {
        return futureX;
    }
    int getFutureY() {
        return futureY;
    }
private:
    bool isPaused = false;
    int movementCalc = 0;
    int futureX, futureY;
};

