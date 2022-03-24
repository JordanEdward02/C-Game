#include "header.h"
#include "WinState.h"

WinState::WinState(BaseEngine* myEngine)
	:BaseState(myEngine),
	saveable(true)
{
	dynamic_cast<Psyjl16Engine*>(myEngine)->setScale(1);
	dynamic_cast<Psyjl16Engine*>(myEngine)->setOffset(0, 0);
}

void WinState::renderBackground() {

	int iWidth = myEngine->getWindowWidth();
	int iHeight = myEngine->getWindowHeight();
	myEngine->fillBackground(0x000000);
	char buf[64];
	sprintf(buf, "Congrats!! You've eaten all the food");
	myEngine->drawBackgroundString((iWidth / 2) - 250, 75, buf, 0xFFFFFF);
	char buf2[64];
	sprintf(buf2, "Submit your score!");
	myEngine->drawBackgroundString(900, 300, buf2, 0xFFFFFF);
}

void WinState::keyPress(int iKeyCode) {

	if (dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->isTyping()) {
		dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->keyPressed(iKeyCode);
	}
}

void WinState::mouseClick(int iButton, int iX, int iY) {
	if (iButton == SDL_BUTTON_LEFT) {
		if (myEngine->getDisplayableObject(0)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(STARTGAME_STATE);
			return;
		}
		if (myEngine->getDisplayableObject(1)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<Psyjl16Engine*>(myEngine)->globalRestart(MENU_STATE);
			return;
		}
		if (myEngine->getDisplayableObject(3)->virtIsPositionWithinObject(iX, iY)) {
			saveGame();
		}


		if (myEngine->getDisplayableObject(2)->virtIsPositionWithinObject(iX, iY)) {
			dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->startTyping();
			return;
		}
		else {
			dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->stopTyping();
			return;
		}
	}
}

void WinState::initialiseObjects() {

	myEngine->createObjectArray(4);
	MyBasicButton* RestartBut = new MyBasicButton(myEngine, new string("Start New Game"));
	RestartBut->setPosition(100, 300);
	myEngine->storeObjectInArray(0, RestartBut);
	MyBasicButton* MenuBut = new MyBasicButton(myEngine, new string("Menu"));
	MenuBut->setPosition(100, 500);
	myEngine->storeObjectInArray(1, MenuBut);
	MyTextBar* NameInput = new MyTextBar(myEngine);
	NameInput->setPosition(900, 350);
	myEngine->storeObjectInArray(2, NameInput);
	MyBasicButton* SubmutScore = new MyBasicButton(myEngine, new string("Submit"));
	SubmutScore->setPosition(900, 500);
	myEngine->storeObjectInArray(3, SubmutScore);
}

void WinState::saveGame() {
	// Only lets 1 save per game
	if (saveable) {

		// Reads all the existing data to a vector
		ifstream inFile("Highscores.txt");
		vector<string> ourData;
		string line;
		if (inFile.is_open()) {
			while (getline(inFile, line)) {
				ourData.push_back(line);
			}
			inFile.close();
		}

		// Processes and rewrites all the data including this games data
		ofstream outFile("Highscores.txt");
		bool toAdd = true;
		int writeCount = 0;
		string newName = dynamic_cast<MyTextBar*>(myEngine->getDisplayableObject(2))->getString() + ",";
		if (outFile.is_open()) {
			for (string& item : ourData) {
				string score = item.substr(item.find(",") + 1, 20);
				int itemScore = stoi(score);
				if ((dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getSugar()) > itemScore && toAdd && writeCount<10) {
					outFile << newName << dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getSugar() << "\n";
					toAdd = false;
					writeCount++;
				}
				if (writeCount < 10) {
					outFile << item << "\n";
					writeCount++;
				}
			}
			if (toAdd && writeCount<10) {
				outFile << newName << dynamic_cast<Psyjl16Engine*>(myEngine)->getTileManager().getSugar() << "\n";
				writeCount++;
			}
			outFile.close();
		}
		saveable = false;
	}

}