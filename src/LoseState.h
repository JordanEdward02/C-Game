#if 1


#pragma once
#include "BaseState.h"
#include "Psyjl16Engine.h"

class LoseState :
    public BaseState
{
public:
	LoseState(BaseEngine* myEngine)
		:BaseState(myEngine)
	{};

	void renderBackground();
	void initialiseObjects();
	void mouseClick(int,int,int);
};

#endif