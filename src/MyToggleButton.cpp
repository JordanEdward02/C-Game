#include "header.h"
#include "MyToggleButton.h"
using namespace std;

void MyToggleButton::toggle() {
	string* temp = myString;
	myString = altString;
	altString = temp;

	if (state)
		state = 0;
	else
		state = 1;
}