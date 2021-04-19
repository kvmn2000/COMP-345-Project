#include "ActionObserver.h"
#include <iostream>
using namespace std;

ActionObserver::ActionObserver() {
}

ActionObserver::ActionObserver(GameEngine* game) {
	gameEngine = game;
	game->attach(this);
}

ActionObserver::~ActionObserver() {
	gameEngine->detach(this);
	gameEngine = nullptr;
}

void ActionObserver::update(int code, int type, int num) {
	switch (code) {
	case -1:
		//BUYING CARD CODE
		cout << "You bought card at index " << type << ", which costed " << num << " coins." << endl;
		break;
	case 0:
		//ADD ARMY CODE
		cout << "You added " << num << " armies." << endl;
		break;
	case 1:
		//ADD CITY CODE
		cout << "You added " << num << " cities." << endl;
		break;
	case 2:
		//DESTROY ARMY
		cout << "You destroyed " << num << " armies." << endl;
		break;
	case 3:
		//MOVE OVER LAND
		cout << "You moved over " << num << " land." << endl;
		break;
	case 4:
		//MOVE OVER WATER AND LAND
		cout << "You moved over " << num << " land." << endl;
		break;
	}
}