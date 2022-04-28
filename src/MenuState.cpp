#include "header.h"
#include "MenuState.h"
#include "Psyjl16Engine.h"

using namespace std;

MenuState::MenuState(BaseEngine* myEngine)
	:BaseState(myEngine)
{
	dynamic_cast<Psyjl16Engine*>(myEngine)->setScale(1);
	dynamic_cast<Psyjl16Engine*>(myEngine)->setOffset(0, 0);
}

void MenuState::renderBackground() {
	myEngine->fillBackground(0x424a44);
	int iWidth = myEngine->getWindowWidth();
	int iHeight = myEngine->getWindowHeight();

	for (int iX = 0; iX < iWidth; iX++)
		for (int iY = 0; iY < iHeight; iY++) {
			switch (iY % 25)
			{
			case 0:
				switch (rand() % 2) {
				case 0:
					myEngine->setBackgroundPixel(iX, iY, 0x000000);
					break;
				}
				break;
			case 12:
				switch (rand() % 4) {
				case 0:
					myEngine->setBackgroundPixel(iX, iY, 0x000000);
					break;
				}
				break;
			}
		}
	char buf[64];
	sprintf(buf, "HIGHSCORES");
	myEngine->drawBackgroundString(900, 100, buf, 0x000000);
	msv.setTopLeftPositionOnScreen(900,150);
	msv.drawAllTiles(myEngine, myEngine->getBackgroundSurface());
}

void MenuState::mouseClick(int iButton, int iX, int iY) {

	if (iButton == SDL_BUTTON_LEFT) {
		if (myEngine->getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(STARTGAME_STATE);
			return;
		}
		if (myEngine->getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<MyToggleButton*>(myEngine->getDisplayableObject(1))->toggle();
			return;
		}
		//((MyToggleButton*)getDisplayableObject(1))->toggle();
	}
}

void MenuState::initialiseObjects() {

	myEngine->createObjectArray(2);
	MyBasicButton* StartGameBut = new MyBasicButton(myEngine, new string("Start Game"));
	StartGameBut->setPosition(100, 300);
	myEngine->storeObjectInArray(0, StartGameBut);
	MyToggleButton* ToggleColourMode = new MyToggleButton(myEngine, new string("On"), new string("Off"));
	ToggleColourMode->setPosition(100, 500);
	myEngine->storeObjectInArray(1, ToggleColourMode);
}