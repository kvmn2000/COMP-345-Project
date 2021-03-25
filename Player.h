#pragma once

#include "Map.h"
#include "Cards.h"
#include "BidingFacility.h"

#include <iostream>
#include <string>
#include <vector>

#define _DEBUG
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

using namespace std;

//declaring classes from other parts

class Player {

public:
    //below are the constructors 
    Player() = default;
    Player(string name);
    Player(int playerId, string playerName);
    Player(string name, int amountOfPlayer);
    Player(const Player& copy);
    ~Player();
    Player& operator=(const Player& copy);
    friend ostream& operator << (ostream& out, const Player& copy);
    friend istream& operator >> (istream& in, Player& copy);


    //payCoin method
    bool payCoin(int cost);

    //other gameplay methods
    void placeNewArmies();
    void moveArmies();
    void moveOverLand();
    void buildCity();
    void destroyArmy();
    bool ignore();
    void andOrAction();
    void takeAction();

    //below are the accessors
    int getArmies();
    int getCoins();
    int getCities();
    string getName();
    int getId();


    //vector<Cards*> getGameHand() const;
   BidingFacility* getBidingFacility();

    //below are the Mutators
    void setArmies(int armies);
    void setCoins(int coins);
    void setCities(int cities);
    void setName(string name);
    void setId(int i);

    //our private constructors
private:

    int id;
    int coins;
    int armies;
    int cities;
    string name;
    //vector <Country*> countryOwned;
    //vector <Cards*> gameHand;
   BidingFacility* bidingFacility;


};