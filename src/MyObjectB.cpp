#include "header.h"
#include "BaseEngine.h"
#include "MyObjectB.h"

void MyObjectB::virtDraw()
{
	myTexture.renderImageWithMaskAndTransparency(getEngine()->getForegroundSurface(), 0, 0,
		m_iCurrentScreenX, m_iCurrentScreenY,
		myTexture.getWidth(), myTexture.getHeight(), 0xFFFFFF, 100);
}
