#include "header.h"
#include "MyCharacter.h"
#include "BaseEngine.h"
#include "UtilCollisionDetection.h"
#include "MyEnemy.h"
#include "Psyjl16TileManager.h"
#include "Psyjl16Engine.h"

using namespace std;

void MyCharacter::virtDoUpdate(int iCurrentTime) {

	if (isPaused)
		return;
	// Change position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_w))
		m_iCurrentScreenY -= 3;
	if (getEngine()->isKeyPressed(SDLK_s))
		m_iCurrentScreenY += 3;
	if (getEngine()->isKeyPressed(SDLK_a))
		m_iCurrentScreenX -= 3;
	if (getEngine()->isKeyPressed(SDLK_d))
		m_iCurrentScreenX += 3;
	auto myEnemy = getEngine()->getDisplayableObject(1);
	if (CollisionDetection::checkRectangles(this->getDrawingRegionLeft(), this->getDrawingRegionRight(),
		this->getDrawingRegionTop(), this->getDrawingRegionBottom(), myEnemy->getDrawingRegionLeft(),
		myEnemy->getDrawingRegionRight(), myEnemy->getDrawingRegionTop(), myEnemy->getDrawingRegionBottom())) {
		((Psyjl16Engine*)getEngine())->globalRestart(LOSE_STATE);
		return;
	}

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() -
		m_iDrawWidth)
		m_iCurrentScreenX = getEngine()->getWindowWidth() -
		m_iDrawWidth;
	if (m_iCurrentScreenY < 100)
		m_iCurrentScreenY = 100;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() -
		m_iDrawHeight)
		m_iCurrentScreenY = getEngine()->getWindowHeight() -
		m_iDrawHeight;



	int tempX = ((Psyjl16Engine*)getEngine())->getTileManager().getMapXForScreenX(getDrawingRegionRight() - 1);
	int tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getDrawingRegionBottom() - 1);
	// TO GET ITEM VALUE AT SET COORDS USE ((JordanDemo*)getEngine())->getTileManager().getMyMap(0, 0)
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == 1) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, 0);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getDrawingRegionTop() - 1);
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == 1) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, 0);
		if(((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	tempX = ((Psyjl16Engine*)getEngine())->getTileManager().getMapXForScreenX(getDrawingRegionLeft() - 1);
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == 1) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, 0);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getDrawingRegionBottom() - 1);
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == 1) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, 0);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}

void MyCharacter::reset() {
	setPosition(getEngine()->getWindowWidth() / 2 - getDrawWidth() / 2,
		getEngine()->getWindowHeight() - getDrawHeight());

}