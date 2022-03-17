#pragma once
#include "MyBasicButton.h"
class MyToggleButton :
    public MyBasicButton
{
public:
    MyToggleButton(BaseEngine* myEngine, string* firstString, string* newAltString)
        :MyBasicButton(myEngine,firstString),
        state(1),
        altString(newAltString)
    {};

    void toggle();
private:
    int state;
    string* altString;
};

