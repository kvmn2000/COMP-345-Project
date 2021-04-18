#pragma once
#include "GameObserver.h"

class ActionObserver : public GameObservers {
public:
	ActionObserver();
	virtual ~ActionObserver();
	void update(int code, int type, int num);
};
