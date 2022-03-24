#pragma once
#include "BaseState.h"
#include "MyCharacter.h"


class PauseState :
    public BaseState
{
public:
    PauseState(BaseEngine* myEngine);
    ~PauseState();
    void keyPress(int);
    void drawTopString();
    void preDraw();
};
