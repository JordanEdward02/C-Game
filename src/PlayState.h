#if 1


#pragma once
#include "BaseState.h"
class PlayState :
    public BaseState
{
public:
    PlayState(BaseEngine* myEngine)
        :BaseState(myEngine)
    {
	};

	void keyPress(int);
	void renderBackground();
	void initialiseObjects();
	void drawTopString();
	void preDraw();
	void mouseClick(int,int,int);
};


#endif
