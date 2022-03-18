#include "header.h"
#include "WinState.h"



void WinState::renderBackground() {

	int iWidth = myEngine->getWindowWidth();
	int iHeight = myEngine->getWindowHeight();
	myEngine->fillBackground(0x000000);
	char buf[64];
	sprintf(buf, "Congrats!! You've eaten all the food");
	myEngine->drawBackgroundString((iWidth / 2) - 250, 75, buf, 0xFFFFFF);
}

void WinState::keyPress(int iKeyCode) {

	if (dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->isTyping())
		dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->keyPressed(iKeyCode);
}

void WinState::mouseClick(int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT) {
		if (myEngine->getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(STARTGAME_STATE);
			return;
		}
		if (myEngine->getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(MENU_STATE);
			return;
		}

		if (myEngine->getDisplayableObject(2)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->startTyping();
			return;
		}
		else {
			dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->stopTyping();
			return;
		}
	}
}

void WinState::initialiseObjects() {

	myEngine->createObjectArray(3);
	MyBasicButton* RestartBut = new MyBasicButton(myEngine, new string("Start New Game"));
	RestartBut->setPosition(myEngine->getWindowWidth() / 2 - 150, myEngine->getWindowHeight() / 2 - 150);
	myEngine->storeObjectInArray(0, RestartBut);
	MyBasicButton* MenuBut = new MyBasicButton(myEngine, new string("Menu"));
	MenuBut->setPosition(myEngine->getWindowWidth() / 2 - 150, myEngine->getWindowHeight() / 2 + 50);
	myEngine->storeObjectInArray(1, MenuBut);
	MyTextBar* NameInput = new MyTextBar(myEngine);
	NameInput->setPosition(myEngine->getWindowWidth() / 2 - 150, myEngine->getWindowHeight() / 2 + 250);
	myEngine->storeObjectInArray(2, NameInput);
}