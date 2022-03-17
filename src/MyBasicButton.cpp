#include "header.h"
#include "MyBasicButton.h"
#include "Psyjl16Engine.h"
using namespace std;

void MyBasicButton::virtDraw() {

	switch (isMouseOver) {
	case true:
	{
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
			m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight - 1,
			0x555555);
		if (myString->length() == 0)
			return;
		getEngine()->drawForegroundString(m_iCurrentScreenX + m_iStartDrawPosX + 5, m_iCurrentScreenY + m_iStartDrawPosY + 30,
			myString->c_str(), 0xAAAAAA, NULL);
		break;
	}
	case false:
	{
		getEngine()->drawForegroundRectangle(
			m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
			m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight - 1,
			0xFFFFFF);
		if (myString->length() == 0)
			return;
		getEngine()->drawForegroundString(m_iCurrentScreenX + m_iStartDrawPosX + 5, m_iCurrentScreenY + m_iStartDrawPosY + 30,
			myString->c_str(), 0x000000, NULL);
		break;
	}
	}

}

void MyBasicButton::virtDoUpdate(int iCurrentTime) {

	if (virtIsPositionWithinObject(getEngine()->getCurrentMouseX(), getEngine()->getCurrentMouseY())){
		isMouseOver = true;
	}
	else {
		isMouseOver = false;
	}
	redrawDisplay();
}