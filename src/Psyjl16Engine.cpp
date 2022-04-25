#include "header.h"
#include "Psyjl16Engine.h"

using namespace std;

int Psyjl16Engine::virtInitialise()
{
	getBackgroundSurface()->setDrawPointsFilter(&filterScale);
	getForegroundSurface()->setDrawPointsFilter(&filterScale);

	// Call base class version
	return BaseEngine::virtInitialise();
}



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
	m_iDefaultUpdatePeriod = 10;
	bool reloadObjects = true;
	if (currentState == PAUSE_STATE) {
		reloadObjects = false;
	}
	if (newState == MENU_STATE) {
		delete myState;
		myState = new MenuState(this);
	}
	if (newState == STARTGAME_STATE) {
		delete myState;
		myState = new PlayState(this);
		if (reloadObjects) {
			tm.reset();
			setScale(2);
		}
	}
	if (newState == WIN_STATE) {
		delete myState;
		myState = new WinState(this);
	}
	if (newState == LOSE_STATE) {
		delete myState;
		myState = new LoseState(this);
		m_iDefaultUpdatePeriod = 100;
	}
	if (newState == PAUSE_STATE) {
		delete myState;
		myState = new PauseState(this);
		reloadObjects = false;
	}
	currentState = newState;
	if (reloadObjects) {
		lockAndSetupBackground();
		virtInitialiseObjects();
		xOffset = yOffset = 0;
	}
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

void Psyjl16Engine::setScale(int iScale) {

	filterScale.setScale(iScale);

}

void Psyjl16Engine::setOffset(int iX, int iY) {
	filterScale.setOffset(iX, iY);
}

int Psyjl16Engine::getScale() {
	return filterScale.getScale();
}

void Psyjl16Engine::virtMouseWheel(int iX, int iY, int which, int timestamp) {
	myState->mouseWheel(iX,iY,which,timestamp);
}

void Psyjl16Engine::virtMainLoopDoBeforeUpdate() {
	myState->doBeforeUpdate();
}

void Psyjl16Engine::newBackground(DrawingSurface* newSurface) {
	m_pBackgroundSurface = newSurface;
	redrawDisplay();
}
void Psyjl16Engine::setBackgroundX(int newX) {
	xOffset += newX * getScale();
}

void Psyjl16Engine::setBackgroundY(int newY) {
	yOffset += newY * getScale();
}
void Psyjl16Engine::copyAllBackgroundBuffer()
{
	if (xOffset < 0)
		xOffset = getWindowWidth() + xOffset;
	if (yOffset < 0)
		yOffset = getWindowHeight() + yOffset;
	xOffset = xOffset % getWindowWidth();
	yOffset = yOffset % getWindowHeight();
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), xOffset-1, yOffset-1);
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, getWindowWidth() - xOffset, getWindowHeight() - yOffset, getWindowWidth(), getWindowHeight(), xOffset-getWindowWidth()+1, yOffset - getWindowHeight()+1);
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - yOffset, getWindowWidth(), getWindowHeight(), xOffset-1, yOffset - getWindowHeight() + 1);
	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, getWindowWidth() - xOffset, 0, getWindowWidth(), getWindowHeight(), (xOffset - getWindowWidth() + 1), yOffset-1);
}