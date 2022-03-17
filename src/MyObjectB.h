#pragma once
#include "DisplayableObject.h"
#include "SimpleImage.h"
class MyObjectB :
    public DisplayableObject
{
public:
    MyObjectB(BaseEngine* myEngine, SimpleImage newTexture)
        :DisplayableObject(400,400,myEngine,newTexture.getWidth(),newTexture.getHeight(),true)
    {
        myTexture = newTexture;
    }
    MyObjectB(BaseEngine* myEngine)
        :DisplayableObject(400, 400, myEngine, 100, 100, true)
    {
    }

    void virtDraw();
protected:
    SimpleImage myTexture;
};
