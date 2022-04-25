#include "header.h"
#include "AntKiller.h"
#include "BaseEngine.h"
#include "Psyjl16Engine.h"

AntKiller::AntKiller(BaseEngine* myEngine, SimpleImage newTexture, int Time)
	:MyObjectB(myEngine, newTexture)
	, creationTime(Time)
{
	imageSize = 16;
	imageX = 48;
}

void AntKiller::virtDoUpdate(int iCurrentTime) {

	if (iCurrentTime > creationTime + 5000) {
		getEngine()->removeDisplayableObject(this);
		getEngine()->drawableObjectsChanged();
		delete this;
	}
}