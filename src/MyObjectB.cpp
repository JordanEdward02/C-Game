#include "header.h"
#include "BaseEngine.h"
#include "MyObjectB.h"
#include "Psyjl16Engine.h"

using namespace std;
void MyObjectB::virtDraw()
{
	myTexture.setTransparencyColour(INVIS);
	myTexture.renderImage(getEngine()->getForegroundSurface(), imageX, imageY,
		m_iCurrentScreenX, m_iCurrentScreenY,
		imageSize, imageSize);
}

bool MyObjectB::checkCollision(MyObjectB* otherObj) {
	// For every pixel in this objects image
	for (int myX = 0; myX < getSize(); myX++) {
		for (int myY = 0; myY < getSize(); myY++) {
			// If the pixel is part of the object (not invisible)
			if (myTexture.getPixelColour(myX, myY) != INVIS) {
				int realX = getLeft() + myX;
				int realY = getTop() + myY;
				// Find which pixel in the other image is at the exact same real pixel location as this one
				if (realX - otherObj->getLeft() < otherObj->getSize() && realX - otherObj->getLeft() >= 0) {
					if (realY - otherObj->getTop() < otherObj->getSize() && realY - otherObj->getTop() >= 0) {
						// If it is at the same location and not invisible, then return true
						if (otherObj->myTexture.getPixelColour(realX - otherObj->getLeft(), realY - otherObj->getTop()) != INVIS) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}