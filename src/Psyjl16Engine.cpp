#include "header.h"
#include "Psyjl16Engine.h"

using namespace std;

void Psyjl16Engine::virtSetupBackgroundBuffer()
{

	switch (currentState) {

	case STARTGAME_STATE:
	{
		fillBackground(0x966F33);
		int iWidth = getWindowWidth();
		int iHeight = getWindowHeight();

		for (int iX = 0; iX < iWidth; iX++)
			for (int iY = 0; iY < iHeight; iY++) {
				switch (iY % 25)
				{
				case 0:
					switch (rand() % 2) {
					case 0:
						setBackgroundPixel(iX, iY, 0x000000);
						break;
					}
					break;
				case 12:
					switch (rand() % 4) {
					case 0:
						setBackgroundPixel(iX, iY, 0x000000);
						break;
					}
					break;
				}
				if (iY < 100) {
					setBackgroundPixel(iX, iY, 0x000000);
				}
			}
		tm.setTopLeftPositionOnScreen(0, 100);
		break;
	}
	case MENU_STATE:
	{
		fillBackground(0x966F33);
		int iWidth = getWindowWidth();
		int iHeight = getWindowHeight();

		for (int iX = 0; iX < iWidth; iX++)
			for (int iY = 0; iY < iHeight; iY++) {
				switch (iY % 25)
				{
				case 0:
					switch (rand() % 2) {
					case 0:
						setBackgroundPixel(iX, iY, 0x000000);
						break;
					}
					break;
				case 12:
					switch (rand() % 4) {
					case 0:
						setBackgroundPixel(iX, iY, 0x000000);
						break;
					}
					break;
				}
			}
		break;
	}
	case WIN_STATE:
	{	
		int iWidth = getWindowWidth();
		int iHeight = getWindowHeight();
		fillBackground(0x000000);
		char buf[64];
		sprintf(buf, "Congrats!! You've eaten all the food");
		drawBackgroundString((iWidth / 2) - 250, 75, buf, 0xFFFFFF);
		break;

	}
	case LOSE_STATE:
	{
		int iWidth = getWindowWidth();
		int iHeight = getWindowHeight();
		fillBackground(0x000000);
		char buf[64];
		sprintf(buf, "You've been squashed!! Better luck next time");
		drawBackgroundString((iWidth / 2) - 300, 75, buf, 0xFFFFFF);
		break;

	}
}
}


void Psyjl16Engine::virtMouseDown(int iButton, int iX, int iY)
{
	switch (currentState) {
	case STARTGAME_STATE:
	{
		if (iButton == SDL_BUTTON_LEFT)
		{
			if (this->getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY))
			{
				((MyEnemy*)this->getDisplayableObject(1))->stun();
			}
		}
		break;
	}
	case MENU_STATE:
	{
		if (iButton == SDL_BUTTON_LEFT) {
			if (getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY))
				globalRestart(STARTGAME_STATE);
			if (getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY))
				globalRestart(WIN_STATE);
				//((MyToggleButton*)getDisplayableObject(1))->toggle();
		}
		break;
	}
	case WIN_STATE:
	{

		if (iButton == SDL_BUTTON_LEFT) {
			if (getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY))
				globalRestart(STARTGAME_STATE);
			if (getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY))
				globalRestart(MENU_STATE);

			MyTextBar* ourObj = dynamic_cast<MyTextBar*>(getDisplayableObject(2));
			if (getDisplayableObject(2)->virtIsPositionWithinObject(iX, iY)) {
				ourObj->startTyping();
			}
			else {
				ourObj->stopTyping();
			}
		}
		break;
	}
	case LOSE_STATE:
	{

		if (iButton == SDL_BUTTON_LEFT) {
			if (getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY))
				globalRestart(STARTGAME_STATE);
			if (getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY))
				globalRestart(MENU_STATE);
		}
		break;
	}
	}
}


void Psyjl16Engine::virtKeyDown(int iKeyCode)
{
	switch (currentState) {
	case STARTGAME_STATE:
		switch (iKeyCode)
		{
		case 'p':
			if (isPaused()) {
				unpause();
				((MyCharacter*)this->getDisplayableObject(0))->togglePause();
			}
			else {
				pause();
				((MyCharacter*)this->getDisplayableObject(0))->togglePause();
			}
			break;
		}

	case WIN_STATE:
	{
		MyTextBar* ourObj = dynamic_cast<MyTextBar*>(getDisplayableObject(2));
		if (ourObj->isTyping())
			ourObj->keyPressed(iKeyCode);
	}
	}
}


int Psyjl16Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);

	switch (currentState) {
	case STARTGAME_STATE:
	{
		createObjectArray(2);

		SimpleImage myCharImage = ImageManager::loadImage("images/Ant.png", true);
		MyCharacter* myPlayer = new MyCharacter(this, myCharImage);
		myPlayer->setPosition(getWindowWidth() / 2 - myPlayer->getDrawWidth() / 2,
			getWindowHeight() - myPlayer->getDrawHeight());


		SimpleImage myEnemyImage = ImageManager::loadImage("images/Swatter.png", true);
		MyEnemy* myEnemy = new MyEnemy(this, myEnemyImage, myPlayer, getModifiedTime());
		myEnemy->setPosition(0, 0);


		// You MUST set the array entry after the last one that you create to NULL,
		// so that the system knows when to stop.
		storeObjectInArray(0, myPlayer);
		storeObjectInArray(1, myEnemy);
		break;
	}
	case MENU_STATE:
	{
		createObjectArray(2);
		MyBasicButton* StartGameBut = new MyBasicButton(this, new string("Start Game"));
		StartGameBut->setPosition(getWindowWidth() / 2-150, getWindowHeight() / 2-150);
		storeObjectInArray(0, StartGameBut);
		MyToggleButton* ToggleColourMode = new MyToggleButton(this, new string("Light Mode"), new string("Dark Mode"));
		ToggleColourMode->setPosition(getWindowWidth() / 2-150, getWindowHeight() / 2+50);
		storeObjectInArray(1, ToggleColourMode);
		break;

	}
	case WIN_STATE:
	{
		createObjectArray(3);
		MyBasicButton* RestartBut = new MyBasicButton(this, new string("Start New Game"));
		RestartBut->setPosition(getWindowWidth() / 2 - 150, getWindowHeight() / 2 - 150);
		storeObjectInArray(0, RestartBut);
		MyBasicButton* MenuBut = new MyBasicButton(this, new string("Menu"));
		MenuBut->setPosition(getWindowWidth() / 2 - 150, getWindowHeight() / 2 + 50);
		storeObjectInArray(1, MenuBut);
		MyTextBar* NameInput = new MyTextBar(this);
		NameInput->setPosition(getWindowWidth() / 2 - 150, getWindowHeight() / 2 + 250);
		storeObjectInArray(2, NameInput);
		break;
	}

	case LOSE_STATE:
	{
		createObjectArray(2);
		MyBasicButton* RestartBut = new MyBasicButton(this, new string("Start New Game"));
		RestartBut->setPosition(getWindowWidth() / 2 - 150, getWindowHeight() / 2 - 150);
		storeObjectInArray(0, RestartBut);
		MyBasicButton* MenuBut = new MyBasicButton(this, new string("Menu"));
		MenuBut->setPosition(getWindowWidth() / 2 - 150, getWindowHeight() / 2 + 50);
		storeObjectInArray(1, MenuBut);
		break;
	}

	}

	setAllObjectsVisible(true);
	return 0;
}


void Psyjl16Engine::virtDrawStringsOnTop() {
	switch (currentState) {
	case STARTGAME_STATE:
		char buf[128];
		int iSugar = tm.getSugar();
		sprintf(buf, "Sugar eaten : %d", iSugar);
		drawForegroundString((getWindowWidth() / 2) - 150, 75, buf, 0xFFFFFF, NULL);
		if (isPaused())
			drawForegroundString((getWindowWidth()/2)-75, 0, "PAUSED", 0xFFFFFF, NULL);
	}
}

void Psyjl16Engine::globalRestart(int myState) {
	currentState = myState;
	tm.reset();
	lockAndSetupBackground();
	virtInitialiseObjects();
	redrawDisplay();
}

void Psyjl16Engine::virtPreDraw() {
	switch (currentState) {
	case STARTGAME_STATE:
	{
		tm.drawAllTiles(this, getForegroundSurface());
		break;
	}
	}

}

bool Psyjl16Engine::checkFinish() {
	if (tm.isDone()) {
		globalRestart(WIN_STATE);
		return true;
	}
	return false;
}