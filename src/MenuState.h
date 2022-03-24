#if 1

#pragma once
#include "BaseState.h"
#include "MyScoreViewer.h"

class MenuState :
    public BaseState
{
public:
	MenuState(BaseEngine* myEngine);
	void renderBackground();
	void initialiseObjects();
	void mouseClick(int,int,int);


private: 
    MyScoreViewer msv;
};

#endif