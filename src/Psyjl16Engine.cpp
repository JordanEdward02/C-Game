#include "header.h"
#include "Psyjl16Engine.h"

using namespace std;

void Psyjl16Engine::virtSetupBackgroundBuffer()
{
	myState->renderBackground();
}


void Psyjl16Engine::virtMouseDown(int iButton, int iX, int iY)
{
	myState->mouseClick(iButton, iX, iY);
}


void Psyjl16Engine::virtKeyDown(int iKeyCode)
{
	myState->keyPress(iKeyCode);
}


int Psyjl16Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	// Destroy any existing objects
	destroyOldObjects(true);

	myState->initialiseObjects();


	setAllObjectsVisible(true);
	return 0;
}


void Psyjl16Engine::virtDrawStringsOnTop() {
	myState->drawTopString();
}

void Psyjl16Engine::globalRestart(int newState) {
	currentState = newState;
	tm.reset();
	if (newState == MENU_STATE) {
		delete myState;
		myState = new MenuState(this);
	}
	if (newState == STARTGAME_STATE) {
		delete myState;
		myState = new PlayState(this);
	}
	if (newState == WIN_STATE) {
		delete myState;
		myState = new WinState(this);
	}
	if (newState == LOSE_STATE) {
		delete myState;
		myState = new LoseState(this);
	}
	if (newState == PAUSE_STATE) {
		delete myState;
		myState = new PauseState(this);
	}
	lockAndSetupBackground();
	if (newState != PAUSE_STATE)
		virtInitialiseObjects();
	redrawDisplay();
}

void Psyjl16Engine::virtPreDraw() {
	myState->preDraw();
}

bool Psyjl16Engine::checkFinish() {
	if (tm.isDone()) {
		globalRestart(WIN_STATE);
		return true;
	}
	return false;
}