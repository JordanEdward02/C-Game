#pragma once
#include "BaseEngine.h"

class BaseState
{
public:
	BaseState(BaseEngine* newEngine)
		:myEngine(newEngine)
	{};

	virtual void keyPress(int) {};
	virtual void renderBackground() {};
	virtual void initialiseObjects() {};
	virtual void drawTopString() {};
	virtual void preDraw() {};
	virtual void mouseClick(int, int, int) {};

protected:
	BaseEngine* myEngine;
};