#include "header.h"
#include "MenuState.h"
#include "Psyjl16Engine.h"

using namespace std;

void MenuState::renderBackground() {
	myEngine->fillBackground(0x966F33);
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
}

void MenuState::mouseClick(int iButton, int iX, int iY) {

	if (iButton == SDL_BUTTON_LEFT) {
		if (myEngine->getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(STARTGAME_STATE);
			return;
		}
		if (myEngine->getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(WIN_STATE);
			return;
		}
		//((MyToggleButton*)getDisplayableObject(1))->toggle();
	}
}

void MenuState::initialiseObjects() {

	myEngine->createObjectArray(2);
	MyBasicButton* StartGameBut = new MyBasicButton(myEngine, new string("Start Game"));
	StartGameBut->setPosition(myEngine->getWindowWidth() / 2 - 150, myEngine->getWindowHeight() / 2 - 150);
	myEngine->storeObjectInArray(0, StartGameBut);
	MyToggleButton* ToggleColourMode = new MyToggleButton(myEngine, new string("Light Mode"), new string("Dark Mode"));
	ToggleColourMode->setPosition(myEngine->getWindowWidth() / 2 - 150, myEngine->getWindowHeight() / 2 + 50);
	myEngine->storeObjectInArray(1, ToggleColourMode);
}