#pragma once

#include <list>
using namespace std;

class GameObservers {

public:

    virtual ~GameObservers() = default;
    virtual void update(int code, int type, int num) = 0;

protected:

    GameObservers();

};


class Subject {

public:

    Subject();
    ~Subject();
    virtual void attach(GameObservers*);
    virtual void detach(GameObservers*);
    virtual void notify(int code, int type, int num);

private:

    list<GameObservers*>* observers;

};