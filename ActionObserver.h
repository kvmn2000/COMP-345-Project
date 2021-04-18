#pragma once
#include "GameObserver.h"
#include "GameEngine.h"

class ActionObserver : public GameObservers {
public:
	ActionObserver();
	ActionObserver(GameEngine* game);
	virtual ~ActionObserver();
	void update(int code, int type, int num);

private:
	GameEngine* gameEngine;
};
