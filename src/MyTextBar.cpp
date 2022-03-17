#include "header.h"
#include "MyTextBar.h"

void MyTextBar::keyPressed(int iKeyCode) {

	// Backspace, removes from string but only is string is not empty
	if (iKeyCode == 8 && myString->length() > 0)
		myString->pop_back();

	// Limits input length to 12, just to stop people putting in dumb long names
	if (myString->length() > 12)
		return;

	// Adds the letter to the string, This is then automatically displayed when the virtDraw is called in MyBasicButton
	if ((iKeyCode >= 97 && iKeyCode <= 122) || iKeyCode == 32) {
		myString->push_back(char(iKeyCode));
	}
}