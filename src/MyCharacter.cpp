#include "header.h"
#include "MyCharacter.h"
#include "BaseEngine.h"
#include "UtilCollisionDetection.h"
#include "MyEnemy.h"
#include "Psyjl16TileManager.h"
#include "Psyjl16Engine.h"

using namespace std;

void MyCharacter::virtDoUpdate(int iCurrentTime) {

	int myStartX = m_iCurrentScreenX;
	int myStartY = m_iCurrentScreenY;
	bool slowed = false;
	if (isPaused)
		return;
	// Change position if player presses a key
	if (getEngine()->isKeyPressed(SDLK_w)) {
		m_iCurrentScreenY -= 2;
		dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(-2);
		imageY = 0;
	}
	if (getEngine()->isKeyPressed(SDLK_s)) {
		m_iCurrentScreenY += 2;
		dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(2);
		imageY = 16;
	}
	if (getEngine()->isKeyPressed(SDLK_a)) {
		m_iCurrentScreenX -= 2;
		dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(-2);
		imageY = 32;
	}
	if (getEngine()->isKeyPressed(SDLK_d)) {
		m_iCurrentScreenX += 2;
		dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(2);
		imageY = 48;
	}
	/*
	auto myEnemy = getEngine()->getDisplayableObject(1);
	if (CollisionDetection::checkRectangles(this->getDrawingRegionLeft(), this->getDrawingRegionRight(),
		this->getDrawingRegionTop(), this->getDrawingRegionBottom(), myEnemy->getDrawingRegionLeft(),
		myEnemy->getDrawingRegionRight(), myEnemy->getDrawingRegionTop(), myEnemy->getDrawingRegionBottom())) {
		((Psyjl16Engine*)getEngine())->globalRestart(LOSE_STATE);
		return;
	}
	*/
	int tempX = ((Psyjl16Engine*)getEngine())->getTileManager().getMapXForScreenX(getRight() - 1);
	int tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getBottom() - 1);
	// BOTTOM RIGHT
	switch (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY)) {
	case SUGAR:
	{
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
		break;
	}
	case WALL:
	{
		if (getEngine()->isKeyPressed(SDLK_d)) {
			m_iCurrentScreenX -= 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(-2);
		}
		if (getEngine()->isKeyPressed(SDLK_s)) {
			m_iCurrentScreenY -= 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(-2);
		}
		break;
	}
	case FIELD:
	{
		if (getEngine()->isKeyPressed(SDLK_d)) {
			if (slowed)
				break;
			m_iCurrentScreenX -= 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(-1);
			slowed = true;
		}
		if (getEngine()->isKeyPressed(SDLK_s)) {
			if (slowed)
				break;
			m_iCurrentScreenY -= 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(-1);
			slowed = true;
		}
		break;
	}
	}


	// TOP RIGHT
	tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getTop() - 1);
	switch (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY)) {
	case SUGAR:
	{
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
		break;
	}
	case WALL:
	{
		if (getEngine()->isKeyPressed(SDLK_d)) {
			m_iCurrentScreenX -= 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(-2);
		}
		if (getEngine()->isKeyPressed(SDLK_w)) {
			m_iCurrentScreenY += 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(2);
		}
		break;
	}
	case FIELD:
	{
		if (getEngine()->isKeyPressed(SDLK_d)) {
			if (slowed)
				break;
			m_iCurrentScreenX -= 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(-1);
			slowed = true;
		}
		if (getEngine()->isKeyPressed(SDLK_w)) {
			if (slowed)
				break;
			m_iCurrentScreenY += 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(1);
			slowed = true;
		}
		break;
	}
	}

	// TOP LEFT
	tempX = ((Psyjl16Engine*)getEngine())->getTileManager().getMapXForScreenX(getLeft() - 1);
	switch (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY)) {
	case SUGAR:
	{
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
		break;
	}
	case WALL:
	{
		if (getEngine()->isKeyPressed(SDLK_a)) {
			m_iCurrentScreenX += 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(2);
		}
		if (getEngine()->isKeyPressed(SDLK_w)) {
			m_iCurrentScreenY += 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(2);
		}
		break;
	}
	case FIELD:
	{
		if (getEngine()->isKeyPressed(SDLK_a)) {
			if (slowed)
				break;
			m_iCurrentScreenX += 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(1);
			slowed = true;
		}
		if (getEngine()->isKeyPressed(SDLK_w)) {
			if (slowed)
				break;
			m_iCurrentScreenY += 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(1);
			slowed = true;
		}
		break;
	}
	}

	// BOTTOM LEFT
	tempY = ((Psyjl16Engine*)getEngine())->getTileManager().getMapYForScreenY(getBottom() - 1);
	switch (((Psyjl16Engine*)getEngine())->getTileManager().getMyMap(tempX, tempY)) {
	case SUGAR:
	{
		((Psyjl16Engine*)getEngine())->getTileManager().setMyMap(tempX, tempY, EMPTY);
		if (((Psyjl16Engine*)getEngine())->checkFinish())
			return;
		break;
	}
	case WALL:
	{
		if (getEngine()->isKeyPressed(SDLK_a)) {
			m_iCurrentScreenX += 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(2);
		}
		if (getEngine()->isKeyPressed(SDLK_s)) {
			m_iCurrentScreenY -= 2;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(-2);
		}
		break;
	}
	case FIELD:
	{
		if (getEngine()->isKeyPressed(SDLK_a)) {
			if (slowed)
				break;
			m_iCurrentScreenX += 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundX(1);
			slowed = true;
		}
		if (getEngine()->isKeyPressed(SDLK_s)) {
			if (slowed)
				break;
			m_iCurrentScreenY -= 1;
			dynamic_cast<Psyjl16Engine*>(getEngine())->setBackgroundY(-1);
			slowed = true;
		}
		break;
	}
	}


	// This switches the sprite after every 10 refreshes, so it looks smooth.
	if (++movementCalc % 10 == 0) {
		imageX += 16;
		imageX = imageX % 48;
	}
	if (myStartX == m_iCurrentScreenX && myStartY == m_iCurrentScreenY) {
		imageX = 0;
	}
	int xChange = m_iCurrentScreenX - myStartX;
	int yChange = m_iCurrentScreenY - myStartY;
	futureX = m_iCurrentScreenX + (xChange * 150);
	futureY = m_iCurrentScreenY + (yChange * 150);
	redrawDisplay();
}

void MyCharacter::reset() {
	setPosition(getEngine()->getWindowWidth() / 2 - getSize() / 2,
		getEngine()->getWindowHeight() - getSize());

}