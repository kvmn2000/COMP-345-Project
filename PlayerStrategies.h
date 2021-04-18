#pragma once
#include "Cards.h"

class PlayerStrategy {
public:
    virtual int pickCard(Hand* hand) = 0;
    virtual bool interaction();
    virtual int submitAge();
};


class HumanStrategy : public PlayerStrategy {
public:
    int pickCard(Hand* hand);
    virtual bool interaction();
    int submitAge();
};

class GreedyComputerStrategy : public PlayerStrategy {
    // greedy computer player that focuses on building cities or destroying opponents
public:
    int pickCard(Hand* hand);
    virtual bool interaction();
    int submitAge();
};

class ModerateComputerStrategy : public PlayerStrategy {
    //a moderate computer player that control a region in which it just needs to occupy it with more armies than the opponents
public:
    int pickCard(Hand* hand);
    virtual bool interaction();
    int submitAge();
};


