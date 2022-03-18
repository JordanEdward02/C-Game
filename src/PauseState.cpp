#include "header.h"
#include "PauseState.h"
#include "Psyjl16Engine.h"

void PauseState::keyPress(int iKeyCode) {
	if (iKeyCode == 'p')
	{
		myEngine->unpause();
		(dynamic_cast<Psyjl16Engine*>(myEngine))->globalRestart(STARTGAME_STATE);
		return;
	}
}

void PauseState::drawTopString() {
	myEngine->drawForegroundString((myEngine->getWindowWidth() / 2) - 75, 0, "PAUSED", 0xFFFFFF, NULL);
}