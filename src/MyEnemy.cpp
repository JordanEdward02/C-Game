#include "header.h"
#include "MyEnemy.h"
#include "Fire.h"
#include "BaseEngine.h"
#include "Psyjl16Engine.h"

using namespace std;
void MyEnemy::virtDoUpdate(int iCurrentTime) {
	
	if (getEngine()->isPaused())
		return;
	int xDif = 0;
	int yDif = 0;
	int ourTime = 0;
	int tempTime = getEngine()->getModifiedTime();
	// Once a full strafe movement has finished, it does a new one and sets up the movement object with the new parameters.
	if (tempTime-moveDuration > moveStartTime) {

		int dist = abs(dynamic_cast<MyCharacter*>(MyTarget)->getDrawingRegionLeft() + MyTarget->getSize() / 2 - m_iCurrentScreenX) + abs(dynamic_cast<MyCharacter*>(MyTarget)->getDrawingRegionTop() + MyTarget->getSize() / 2 - m_iCurrentScreenY);
		if (dist < 300)
			ourTime = moveDuration = 2000;
		else if (dist < 500)
			ourTime = moveDuration = 2500;
		else if (dist < 800)
			ourTime = moveDuration = 3000;
		else
			ourTime = moveDuration = 4000;
		m_oMovement.setup(m_iCurrentScreenX, m_iCurrentScreenY,
			dynamic_cast<MyCharacter*>(MyTarget)->getFutureX()+MyTarget->getSize()/2, dynamic_cast<MyCharacter*>(MyTarget)->getFutureY()+MyTarget->getSize()/2,
			tempTime, tempTime+ourTime);
		moveStartTime = getEngine()->getModifiedTime();
		if (abs(m_iCurrentScreenX - dynamic_cast<MyCharacter*>(MyTarget)->getFutureX() + MyTarget->getSize() / 2) > abs(m_iCurrentScreenY - dynamic_cast<MyCharacter*>(MyTarget)->getFutureY() + MyTarget->getSize() / 2)) {
			if (m_iCurrentScreenX - dynamic_cast<MyCharacter*>(MyTarget)->getFutureX() + MyTarget->getSize() / 2 > 0)
				imageY = 64;
			else
				imageY = 96;
		}
		else {
			if (m_iCurrentScreenY - dynamic_cast<MyCharacter*>(MyTarget)->getFutureY() + MyTarget->getSize() / 2 > 0)
				imageY = 32;
			else
				imageY = 0;
		}
	}
	// If the enemy stun time was not in the last 2 seconds, then calculates new differences for the movement.
	if (stunTime + 2000 < getEngine()->getModifiedTime()) {
		m_oMovement.calculate(iCurrentTime);
		xDif = m_oMovement.getX() - m_iCurrentScreenX;
		yDif = m_oMovement.getY() - m_iCurrentScreenY;
	}

	// Creates all the antkiller objects randomly below its current position. These are what kill the player and end the game
	// They are added to the object queue and remove themselves upon 5 seconds passing.
	if (movementCalc % 30 == 0) {
		SimpleImage killerImage = ImageManager::loadImage("images/FireballProjectile.png", true);
		Fire* newKiller = new Fire(getEngine(), killerImage, tempTime, MyTarget);
		int spawnY = getBottom() + (rand() % 20) + 5;
		int spawnX = getLeft() + (getSize() / 2) + (rand() % 40) - 20;
		if (imageY == 32)
			spawnY -= 80;
		if (imageY == 64) {
			spawnY -= 25;
			spawnX -= 50;
		}
		if (imageY == 96) {
			spawnY -= 25;
			spawnX += 50;
		}
		newKiller->setPosition(spawnX, spawnY);
		getEngine()->appendObjectToArray(newKiller);
		getEngine()->drawableObjectsChanged();
	}
	m_iCurrentScreenX += xDif;
	m_iCurrentScreenY += yDif;


	// This switches the sprite after every 10 refreshes, so it looks smooth.
	if (++movementCalc % 10 == 0) {
		imageX += 32;
		imageX = imageX % 128;
	}
	// Ensure that the objects get redrawn on the display
	redrawDisplay();
}


void MyEnemy::stun() {

	if (stunTime + 3000 > getEngine()->getModifiedTime())
		return;
	stunTime = getEngine()->getModifiedTime();
	return;

}

void MyEnemy::reset() {
	stunTime = getEngine()->getModifiedTime();
	setPosition(0, 0);

}