#include "header.h"
#include "PauseState.h"
#include "Psyjl16Engine.h"

PauseState::PauseState(BaseEngine* myEngine)
	:BaseState(myEngine)
	{
		dynamic_cast<MyCharacter*>(myEngine->getDisplayableObject(0))->togglePause();
		int iX = dynamic_cast<MyCharacter*>(myEngine->getDisplayableObject(0))->getDrawingRegionTop() - myEngine->getWindowHeight() / dynamic_cast<Psyjl16Engine*>(myEngine)->getScale() / 2 + myEngine->getDisplayableObject(0)->getDrawHeight() / 2;
		int iY = dynamic_cast<MyCharacter*>(myEngine->getDisplayableObject(0))->getDrawingRegionLeft() - myEngine->getWindowWidth() / dynamic_cast<Psyjl16Engine*>(myEngine)->getScale() / 2 + myEngine->getDisplayableObject(0)->getDrawWidth() / 2;
		dynamic_cast<Psyjl16Engine*>(myEngine)->setOffset(iX, iY);
	};

PauseState::~PauseState() {
}

void PauseState::keyPress(int iKeyCode) {
	if (iKeyCode == 'p')
	{
		myEngine->unpause();
		dynamic_cast<MyCharacter*>(myEngine->getDisplayableObject(0))->togglePause();
		(dynamic_cast<Psyjl16Engine*>(myEngine))->globalRestart(STARTGAME_STATE);
		return;
	}
}

void PauseState::drawTopString() {
	myEngine->drawForegroundString(myEngine->getDisplayableObject(0)->getDrawingRegionLeft() - 50, myEngine->getDisplayableObject(0)->getDrawingRegionTop() - (75 * dynamic_cast<Psyjl16Engine*>(myEngine)->getScale()), "PAUSED", 0xFFFFFF, NULL);
	char buf[128];
	int iSugar = dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getSugar();
	sprintf(buf, "Sugar eaten : %d", iSugar);
	myEngine->drawForegroundString(myEngine->getDisplayableObject(0)->getDrawingRegionLeft() - 100, myEngine->getDisplayableObject(0)->getDrawingRegionTop() - (60 * dynamic_cast<Psyjl16Engine*>(myEngine)->getScale()), buf, 0xFFFFFF, NULL);
}

void PauseState::preDraw() {

	dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().drawAllTiles(myEngine, myEngine->getForegroundSurface());
}