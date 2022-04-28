#include "header.h"
#include "Fire.h"
#include "BaseEngine.h"
#include "Psyjl16Engine.h"

Fire::Fire(BaseEngine* myEngine, SimpleImage newTexture, int Time, MyObjectB* playerObject)
	:MyObjectB(myEngine, newTexture)
	, creationTime(Time)
	, target(playerObject)
{
	imageSize = 16;
	imageX = 48;
}

void Fire::virtDoUpdate(int iCurrentTime) {
	if (checkCollision(target)) {
		dynamic_cast<Psyjl16Engine*>(getEngine())->globalRestart(LOSE_STATE);
		return;
	}
	if (iCurrentTime > creationTime + 5000) {
		getEngine()->removeDisplayableObject(this);
		getEngine()->drawableObjectsChanged();
		delete this;
	}
}