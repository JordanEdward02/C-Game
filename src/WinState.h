#if 1


#pragma once
#include "BaseState.h"
#include "MyTextBar.h"
#include "Psyjl16Engine.h"


class WinState :
    public BaseState
{
public:
    WinState(BaseEngine* myEngine);

	void keyPress(int);
	void renderBackground();
	void initialiseObjects();
	void drawTopString() {};
	void preDraw() {};
	void mouseClick(int,int,int);
	void saveGame();

private:
	bool saveable;
};



#endif
