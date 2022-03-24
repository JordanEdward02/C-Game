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
	if (getEngine()->isKeyPressed(SDLK_w)) {
		m_iCurrentScreenY -= 3;
		dynamic_cast<Psyjl16Engine*>(getEngine())->yOffset -= 3;
	}
	if (getEngine()->isKeyPressed(SDLK_s)){
		m_iCurrentScreenY += 3;
		dynamic_cast<Psyjl16Engine*>(getEngine())->yOffset += 3;
	}
	if (getEngine()->isKeyPressed(SDLK_a)){
		m_iCurrentScreenX -= 3;
		dynamic_cast<Psyjl16Engine*>(getEngine())->xOffset -= 3;
	}
	if (getEngine()->isKeyPressed(SDLK_d)){
		m_iCurrentScreenX += 3;
		dynamic_cast<Psyjl16Engine*>(getEngine())->xOffset += 3;
	}
	auto myEnemy = getEngine()->getDisplayableObject(1);
	if (CollisionDetection::checkRectangles(this->getDrawingRegionLeft(), this->getDrawingRegionRight(),
		this->getDrawingRegionTop(), this->getDrawingRegionBottom(), myEnemy->getDrawingRegionLeft(),
		myEnemy->getDrawingRegionRight(), myEnemy->getDrawingRegionTop(), myEnemy->getDrawingRegionBottom())) {
		((Psyjl16Engine*)getEngine())->globalRestart(LOSE_STATE);
		return;
	}

	int tempX = ((Psyjl16Engine*)getEngine())->getTileManager().getMapXForScreenX(getDrawingRegionRight() - 1);
	int tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getDrawingRegionBottom() - 1);

	// BOTTOM RIGHT
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == SUGAR) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == WALL) {
		if (getEngine()->isKeyPressed(SDLK_d)) {
			m_iCurrentScreenX -= 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->xOffset -= 3;
		}
		if (getEngine()->isKeyPressed(SDLK_s)) {
			m_iCurrentScreenY -= 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->yOffset -= 3;
		}
	}
	
	// TOP RIGHT
	tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getDrawingRegionTop() - 1);
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == SUGAR) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if(((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == WALL) {
		if (getEngine()->isKeyPressed(SDLK_d)) {
			m_iCurrentScreenX -= 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->xOffset -= 3;
		}
		if (getEngine()->isKeyPressed(SDLK_w)) {
			m_iCurrentScreenY += 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->yOffset += 3;
		}
	}

	// TOP LEFT
	tempX = ((Psyjl16Engine*)getEngine())->getTileManager().getMapXForScreenX(getDrawingRegionLeft() - 1);
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == SUGAR) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == WALL) {
		if (getEngine()->isKeyPressed(SDLK_a)) {
			m_iCurrentScreenX += 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->xOffset += 3;
		}
		if (getEngine()->isKeyPressed(SDLK_w)) {
			m_iCurrentScreenY += 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->yOffset += 3;
		}
	}

	// BOTTOM LEFT
	tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getDrawingRegionBottom() - 1);
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == SUGAR) {
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
	}
	if (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY) == WALL) {
		if (getEngine()->isKeyPressed(SDLK_a)) {
			m_iCurrentScreenX += 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->xOffset += 3;
		}
		if (getEngine()->isKeyPressed(SDLK_s)) {
			m_iCurrentScreenY -= 3;
			dynamic_cast<Psyjl16Engine*>(getEngine())->yOffset -= 3;
		}
	}
	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}

void MyCharacter::reset() {
	setPosition(getEngine()->getWindowWidth() / 2 - getDrawWidth() / 2,
		getEngine()->getWindowHeight() - getDrawHeight());

}