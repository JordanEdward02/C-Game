#include "header.h"
#include "BaseEngine.h"
#include "MyObjectB.h"

void MyObjectB::virtDraw()
{
	myTexture.setTransparencyColour(0xFF00E2);
	myTexture.renderImage(getEngine()->getForegroundSurface(), imageX, imageY,
		m_iCurrentScreenX, m_iCurrentScreenY,
		imageSize, imageSize);
}
