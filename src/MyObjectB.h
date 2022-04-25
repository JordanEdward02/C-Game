#pragma once
#include "DisplayableObject.h"
#include "SimpleImage.h"

class MyObjectB :
    public DisplayableObject
{
public:
    MyObjectB(BaseEngine* myEngine, SimpleImage newTexture)
        :DisplayableObject(400,400,myEngine,newTexture.getWidth(),newTexture.getHeight(),true),
        imageX(0),imageY(0)
    {
        myTexture = newTexture;
    }
    ~MyObjectB() {
    }

    void virtDraw();
    int getSize() {
        return imageSize;
    }
    int getBottom() {
        return m_iCurrentScreenY + imageSize;
    }
    int getTop() {
        return m_iCurrentScreenY;
    }
    int getLeft() {
        return m_iCurrentScreenX;
    }
    int getRight() {
        return m_iCurrentScreenX + imageSize;
    }
protected:
    SimpleImage myTexture;
    int imageX, imageY, imageSize;
};
