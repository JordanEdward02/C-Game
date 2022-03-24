#include "header.h"
#include "PlayState.h"
#include "Psyjl16Engine.h"


PlayState::PlayState(BaseEngine* myEngine)
	:BaseState(myEngine)
{
}

PlayState::~PlayState() {
}

void PlayState::renderBackground() {

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


	dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().setTopLeftPositionOnScreen(-100, -100);
}

void PlayState::keyPress(int iKeyCode) {
	switch (iKeyCode)
	{
	case 'p':
	{
		myEngine->pause();
		dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(PAUSE_STATE);
		return;
	}
	}

}

void PlayState::mouseClick(int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT)
	{
		
		if (myEngine->getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY))
		{
			(dynamic_cast<MyEnemy*>(myEngine->getDisplayableObject(1)))->stun();
		}
		
	}
}

void PlayState::initialiseObjects() {
	myEngine->createObjectArray(2);

	SimpleImage myCharImage = ImageManager::loadImage("images/Ant.png", true);
	MyCharacter* myPlayer = new MyCharacter(myEngine, myCharImage);
	myPlayer->setPosition(myEngine->getWindowWidth() / 2 - myPlayer->getDrawWidth() / 2,
		myEngine->getWindowHeight() - myPlayer->getDrawHeight());


	SimpleImage myEnemyImage = ImageManager::loadImage("images/Swatter.png", true);
	MyEnemy* myEnemy = new MyEnemy(myEngine, myEnemyImage, myPlayer, myEngine->getModifiedTime());
	myEnemy->setPosition(0, 0);


	myEngine->storeObjectInArray(0, myPlayer);
	myEngine->storeObjectInArray(1, myEnemy);
}

void PlayState::drawTopString() {

	char buf[128];
	int iSugar = dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getSugar();
	sprintf(buf, "Sugar eaten : %d", iSugar);
	myEngine->drawForegroundString(myEngine->getDisplayableObject(0)->getDrawingRegionLeft()-100, myEngine->getDisplayableObject(0)->getDrawingRegionTop()-(60*dynamic_cast<Psyjl16Engine*>(myEngine)->getScale()), buf, 0xFFFFFF, NULL);
}

void PlayState::preDraw() {
	dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().drawAllTiles(myEngine, myEngine->getForegroundSurface());
	int iX = dynamic_cast<MyCharacter*>(myEngine->getDisplayableObject(0))->getDrawingRegionTop() - myEngine->getWindowHeight()/dynamic_cast<Psyjl16Engine*>(myEngine)->getScale()/2 + myEngine->getDisplayableObject(0)->getDrawHeight()/2;
	int iY = dynamic_cast<MyCharacter*>(myEngine->getDisplayableObject(0))->getDrawingRegionLeft() - myEngine->getWindowWidth() / dynamic_cast<Psyjl16Engine*>(myEngine)->getScale() / 2 + myEngine->getDisplayableObject(0)->getDrawWidth()/2;
	dynamic_cast<Psyjl16Engine*>(myEngine)->setOffset(iX, iY);
}

void PlayState::mouseWheel(int iX, int iY, int which, int timestamp) {
	if (iY<0)
		dynamic_cast<Psyjl16Engine*>(myEngine)->downScale();
	if (iY > 0)
		dynamic_cast<Psyjl16Engine*>(myEngine)->upScale();
}