#include "header.h"
#include "LoseState.h"

void LoseState::renderBackground() {
	int iWidth = myEngine->getWindowWidth();
	int iHeight = myEngine->getWindowHeight();
	myEngine->fillBackground(0x000000);
	char buf[64];
	sprintf(buf, "You've been squashed!! Better luck next time");
	myEngine->drawBackgroundString((iWidth / 2) - 300, 75, buf, 0xFFFFFF);
}

void LoseState::mouseClick(int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT) {
		if (myEngine->getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(STARTGAME_STATE);
			return;
		}
		if (myEngine->getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(MENU_STATE);
			return;
		}
	}
}

void LoseState::initialiseObjects() {

	myEngine->createObjectArray(2);
	MyBasicButton* RestartBut = new MyBasicButton(myEngine, new string("Start New Game"));
	RestartBut->setPosition(myEngine->getWindowWidth() / 2 - 150, myEngine->getWindowHeight() / 2 - 150);
	myEngine->storeObjectInArray(0, RestartBut);
	MyBasicButton* MenuBut = new MyBasicButton(myEngine, new string("Menu"));
	MenuBut->setPosition(myEngine->getWindowWidth() / 2 - 150, myEngine->getWindowHeight() / 2 + 50);
	myEngine->storeObjectInArray(1, MenuBut);
}