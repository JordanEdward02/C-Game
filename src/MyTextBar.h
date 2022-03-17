#pragma once
#include "MyBasicButton.h"

class MyTextBar :
    public MyBasicButton
{
public:
    MyTextBar(BaseEngine* myEngine)
        :MyBasicButton(myEngine, new string("")),
        typing(false)
    {}

    void startTyping() {
        typing = true;
    }
    void stopTyping() {
        typing = false;
    }
    bool isTyping() {
        return typing;
    }
    void keyPressed(int iKeyCode);
private:
    bool typing;
};

