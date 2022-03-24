#pragma once
#include "FilterPoints.h"
#include "header.h"
#include "DrawingSurface.h"

class CustomFilter :
    public FilterPoints
{
public:

	virtual bool filter(DrawingSurface* surface, int& x, int& y, unsigned int& uiColour) override
	{
		if (x - myXOffset < 0) 
			return 0;
		if (y - myYOffset < 0)
			return 0;
		if ((x-myXOffset) * myScale < surface->getSurfaceWidth() && (y-myYOffset) * myScale < surface->getSurfaceHeight()) {
			x = (x - myXOffset) * myScale;
			y = (y - myYOffset) * myScale;
			for (int i = 0; i < myScale; i++) {
				for (int j = 0; j < myScale; j++) {
					if (x+i < 1300 && x+i>0 && y+j<800 && y+j>0)
						surface->rawSetPixel(x+i, y+j, uiColour);
				}
			}
			return 0;
		}
		return 0;
	};

	/*
	If your filter is implementing virtual positions then this converts from a real screen pixel position to a virtual position, according to the translation that the filter applies.
	*/
	virtual int filterConvertRealToVirtualXPosition(int x) override 
	{
			return x/ myScale + myXOffset;
	}
	/*
	If your filter is implementing virtual positions then this converts from a real screen pixel position to a virtual position, according to the translation that the filter applies.
	*/
	virtual int filterConvertRealToVirtualYPosition(int y) override
	{ 
			return y/ myScale + myYOffset;
	}
	/*
	If your filter is implementing virtual positions then this converts from a virtual pixel position to a real screen position, according to the translation that the filter applies.
	*/
	virtual int filterConvertVirtualToRealXPosition(int x) override
	{ 
			return (x - myXOffset) * myScale;
	}
	/*
	If your filter is implementing virtual positions then this converts from a virtual pixel position to a real screen position, according to the translation that the filter applies.
	*/
	virtual int filterConvertVirtualToRealYPosition(int y) override
	{
		return (y - myYOffset) * myScale;

	}

	void setScale(int iScale) {
		myScale = iScale;
	}
	void setOffset(int iX, int iY) {
		myXOffset = iY;
		myYOffset = iX;
	}
	int getScale() {
		return myScale;
	}

	void upScale() {
		if (myScale < 3)
			myScale++;
	}
	void downScale() {
		if (myScale > 1)
			myScale--;
	}

private:
	int myScale = 1;
	int myXOffset = 0;
	int myYOffset = 0;
};


