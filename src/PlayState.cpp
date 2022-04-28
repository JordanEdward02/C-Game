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

	myEngine->fillBackground(0x424a44);
	int iWidth = myEngine->getWindowWidth();
	int iHeight = myEngine->getWindowHeight();
	auto myImage = ImageManager::loadImage("images/SandBackground.jpg", false);
	myImage.renderImage(myEngine->getBackgroundSurface(), 0, 0, 0, 0, 1300, 800);

	dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().setTopLeftPositionOnScreen(0,0);
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
	case 'l':
	{
		if (myEngine->isPaused())
			myEngine->unpause();
		else
			myEngine->pause();
		break;
	}
	case 'o':
	{
		if (dynamic_cast<MyObjectB*>(myEngine->getDisplayableObject(0))->getTexture().getImageURL() == "images/GiantCrab.png") {
			dynamic_cast<MyObjectB*>(myEngine->getDisplayableObject(0))->setTexture(ImageManager::loadImage("images/DemoCurve.png", false));
		}
		else {
			dynamic_cast<MyObjectB*>(myEngine->getDisplayableObject(0))->setTexture(ImageManager::loadImage("images/GiantCrab.png", false));
		}
		break;
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

	SimpleImage myCharImage = ImageManager::loadImage("images/GiantCrab.png", false);
	MyCharacter* myPlayer = new MyCharacter(myEngine, myCharImage);
	myPlayer->setPosition(dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getMapWidth()*25 - myPlayer->getDrawWidth()/2,
		dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getMapHeight()*25 - myPlayer->getDrawHeight()/2);


	SimpleImage myEnemyImage = ImageManager::loadImage("images/YellowDragon.png", false);
	MyEnemy* myEnemy = new MyEnemy(myEngine, myEnemyImage, myPlayer, myEngine->getModifiedTime());
	myEnemy->setPosition(60, 60);


	myEngine->storeObjectInArray(0, myPlayer);
	myEngine->storeObjectInArray(1, myEnemy);
}

void PlayState::drawTopString() {

	char buf[128];
	int iSugar = dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getSugar();
	sprintf(buf, "Score: %d", dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getSugar());
	myEngine->drawForegroundString(myEngine->getDisplayableObject(0)->getDrawingRegionLeft()-50, myEngine->getDisplayableObject(0)->getDrawingRegionTop()-(25*(dynamic_cast<Psyjl16Engine*>(myEngine)->getScale()%3+1)), buf, 0xFFFFFF, NULL);
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