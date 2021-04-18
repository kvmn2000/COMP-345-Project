#include "ActionObserver.h"
#include <iostream>
using namespace std;

void ActionObserver::update(int code, int type, int num) {
	switch (code) {
	case -1:
		//BUYING CARD CODE
		cout << "Player bought card at index " << type << ", which costed " << num << " coins." << endl;
		break;
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}