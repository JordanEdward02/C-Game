#include "header.h"
#include "MyEnemy.h"
#include "BaseEngine.h"

using namespace std;
void MyEnemy::virtDoUpdate(int iCurrentTime) {
	

	auto tempTime = getEngine()->getModifiedTime();
	if (movementCalc++ % 5 == 0) {
		m_oMovement.setup(m_iCurrentScreenX, m_iCurrentScreenY,
			MyTarget->getDrawingRegionLeft(), MyTarget->getDrawingRegionTop(),
			tempTime, tempTime+2000);
	}
	if (stunTime + 2000 < getEngine()->getModifiedTime()) {
		m_oMovement.calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMovement.getX();
		m_iCurrentScreenY = m_oMovement.getY();

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