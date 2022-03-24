#include "header.h"
#include "LoseState.h"

LoseState::LoseState(BaseEngine* myEngine)
	:BaseState(myEngine),mySur1(myEngine),mySur2(myEngine),mySur3(myEngine),mySur4(myEngine),mySur5(myEngine)
{
	dynamic_cast<Psyjl16Engine*>(myEngine)->setScale(1);
	dynamic_cast<Psyjl16Engine*>(myEngine)->setOffset(0, 0);

	oldSurface = myEngine->getBackgroundSurface();

	int iWidth = myEngine->getWindowWidth();
	int iHeight = myEngine->getWindowHeight();
	mySur1.createSurface(iWidth,iHeight);
	mySur2.createSurface(iWidth, iHeight);
	mySur3.createSurface(iWidth, iHeight);
	mySur4.createSurface(iWidth, iHeight);
	mySur5.createSurface(iWidth, iHeight);
}

LoseState::~LoseState() {
	dynamic_cast<Psyjl16Engine*>(myEngine)->newBackground(oldSurface);
}

void LoseState::renderBackground() {
	int iWidth = myEngine->getWindowWidth();
	int iHeight = myEngine->getWindowHeight();

	myEngine->fillBackground(0x000000);
	mySur1.fillSurface(0x000000);
	mySur2.fillSurface(0x000000);
	mySur3.fillSurface(0x000000);
	mySur4.fillSurface(0x000000);
	mySur5.fillSurface(0x000000);

	mySur1.mySDLLockSurface();
	mySur2.mySDLLockSurface();
	mySur3.mySDLLockSurface();
	mySur4.mySDLLockSurface();
	mySur5.mySDLLockSurface();

	mySur5.drawOval(iWidth/2 - 60, iHeight / 2 - 60, iWidth / 2 + 60, iHeight / 2 + 60, 0x444444);

	mySur4.drawOval(iWidth/2 - 50, iHeight/2 - 50, iWidth/2 + 50, iHeight/2 + 50, 0x888888);
	mySur5.drawOval(iWidth/2 - 50, iHeight/2 - 50, iWidth/2 + 50, iHeight/2 + 50, 0x888888);

	mySur3.drawOval(iWidth/2 - 40, iHeight/2 - 40, iWidth/2 + 40, iHeight/2 + 40, 0xAAAAAA);
	mySur4.drawOval(iWidth/2 - 40, iHeight/2 - 40, iWidth/2 + 40, iHeight/2 + 40, 0xAAAAAA);
	mySur5.drawOval(iWidth/2 - 40, iHeight/2 - 40, iWidth/2 + 40, iHeight/2 + 40, 0xAAAAAA);

	mySur2.drawOval(iWidth/2 - 30, iHeight/2 - 30, iWidth/2 + 30, iHeight/2 + 30, 0xDDDDDD);
	mySur3.drawOval(iWidth/2 - 30, iHeight/2 - 30, iWidth/2 + 30, iHeight/2 + 30, 0xDDDDDD);
	mySur4.drawOval(iWidth/2 - 30, iHeight/2 - 30, iWidth/2 + 30, iHeight/2 + 30, 0xDDDDDD);
	mySur5.drawOval(iWidth/2 - 30, iHeight/2 - 30, iWidth/2 + 30, iHeight/2 + 30, 0xDDDDDD);

	mySur1.drawOval(iWidth/2 - 20, iHeight/2 - 20, iWidth/2 + 20, iHeight/2 + 20, 0xFFFFFF);
	mySur2.drawOval(iWidth/2 - 20, iHeight/2 - 20, iWidth/2 + 20, iHeight/2 + 20, 0xFFFFFF);
	mySur3.drawOval(iWidth/2 - 20, iHeight/2 - 20, iWidth/2 + 20, iHeight/2 + 20, 0xFFFFFF);
	mySur4.drawOval(iWidth/2 - 20, iHeight/2 - 20, iWidth/2 + 20, iHeight/2 + 20, 0xFFFFFF);
	mySur5.drawOval(iWidth/2 - 20, iHeight/2 - 20, iWidth/2 + 20, iHeight/2 + 20, 0xFFFFFF);


	mySur1.mySDLUnlockSurface();
	mySur2.mySDLUnlockSurface();
	mySur3.mySDLUnlockSurface();
	mySur4.mySDLUnlockSurface();
	mySur5.mySDLUnlockSurface();


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
	RestartBut->setPosition(100, 300);
	myEngine->storeObjectInArray(0, RestartBut);
	MyBasicButton* MenuBut = new MyBasicButton(myEngine, new string("Menu"));
	MenuBut->setPosition(100, 500);
	myEngine->storeObjectInArray(1, MenuBut);
}

void LoseState::drawTopString() {
	char buf[64];
	sprintf(buf, "You've been squashed!! Better luck next time");
	myEngine->drawForegroundString((myEngine->getWindowWidth() / 2) - 300, 75, buf, 0xFFFFFF);
}


void LoseState::doBeforeUpdate() {
	if (increasing) {
		currentSur++;
		if (currentSur == 5)
			increasing = false;
	}
	else {
		currentSur--;
		if (currentSur == 1)
			increasing = true;
	}
	switch (currentSur) {
	case 1:
	{
		dynamic_cast<Psyjl16Engine*>(myEngine)->newBackground(&mySur1);
		break;
	}
	case 2:
	{
		dynamic_cast<Psyjl16Engine*>(myEngine)->newBackground(&mySur2);
		break;
	}
	case 3:
	{
		dynamic_cast<Psyjl16Engine*>(myEngine)->newBackground(&mySur3);
		break;
	}
	case 4:
	{
		dynamic_cast<Psyjl16Engine*>(myEngine)->newBackground(&mySur4);
		break;
	}
	case 5:
	{
		dynamic_cast<Psyjl16Engine*>(myEngine)->newBackground(&mySur5);
		break;
	}
	}
	myEngine->redrawDisplay();
}