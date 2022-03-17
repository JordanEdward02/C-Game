#pragma once
#include "DisplayableObject.h"
#include "BaseEngine.h"

using namespace std;

class MyBasicButton :
    public DisplayableObject
{
public:
    MyBasicButton(BaseEngine* myEngine,string* newString)
        :DisplayableObject(myEngine, 300, 100, false),
        isMouseOver(false),
        myString(newString)
    {};
    ~MyBasicButton()
    {
        if (myString != nullptr) {
            delete myString;
        }
    }

    void virtDraw();
    void virtDoUpdate(int iCurrentTime);
    void setText(string* newString)
    {
        myString = newString;
    }
    string getString() {
        return *myString;
    }
protected:
    string* myString;
    bool isMouseOver;
};

