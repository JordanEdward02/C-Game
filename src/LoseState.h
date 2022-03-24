#if 1


#pragma once
#include "BaseState.h"
#include "Psyjl16Engine.h"

class LoseState :
    public BaseState
{
public:
	LoseState(BaseEngine* myEngine);
	~LoseState();
	void renderBackground();
	void initialiseObjects();
	void mouseClick(int,int,int);
	void drawTopString();
	void doBeforeUpdate();
private:
	DrawingSurface* oldSurface;
	DrawingSurface mySur1, mySur2, mySur3, mySur4, mySur5;
	int currentSur=1;
	bool increasing = true;
};

#endif