#if 1

#pragma once
#include "BaseState.h"

class MenuState :
    public BaseState
{
public:
    MenuState(BaseEngine* myEngine)
        :BaseState(myEngine)
    {};

	void renderBackground();
	void initialiseObjects();
	void mouseClick(int,int,int);
};

#endif