#pragma once
#include "BaseState.h"
#include "MyCharacter.h"

class PauseState :
    public BaseState
{
public:
    PauseState(BaseEngine* myEngine)
        :BaseState(myEngine)
    {
        dynamic_cast<MyCharacter*>(myEngine->getDisplayableObject(0))->togglePause();
    };

    void keyPress(int);
    void drawTopString();
};
