#include "Player.h"
#include "Map.h"

#include <string>
#include <iostream>



Player::Player(int playerId, string playerName)
{
    id = playerId;
    name = playerName;
}

//default constructor with parameter
Player::Player(string playerName)
{
    name = playerName;
    id = 0;
    cities = 0;
    armies = 0;
    coins = 0;
    bidingFacility = new BidingFacility(playerName);

}

//default constructor with number of players.
Player::Player(string playerName, int numOfPlayers)
{
    name = playerName;
    id = 0;
    cities = 0;
    armies = 0;
   // bidingFacility = new BidingFacility(playerName);

    //Number of players decides how many coins they will recieve. 2 players = 14 coins, 3=11 coins and so on.
    switch (numOfPlayers)
    {
    case 2:
        Player::coins = 14;
        break;
    case 3:
        Player::coins = 11;
        break;
    case 4:
        Player::coins = 9;
        break;
    case 5:
        Player::coins = 8;
        break;
    }

}
//Copy Constructor
Player::Player(const Player& copy) {

}

Player::~Player() {

   cout << endl << "---------- DELETING PLAYER "<<id<<" -----------" << endl;
   delete bidingFacility;
   bidingFacility = NULL;
}

Player& Player::operator=(const Player& copy)
{
    cout << "Creating a Player copy:" << endl;
    return *(new Player(copy));
}

ostream& operator<<(ostream& out, const Player& copy)
{
    out << "Player name is : " << copy.name << endl;
    return out;
}

istream& operator>>(istream& in, Player& copy)
{
    cout << "Input Player name: ";
    in >> copy.name;
    return in;
}


//below are the accessors

int Player::getArmies()
{ 
    return armies; 
}

int Player::getCoins()
{ return coins; 
}

int Player::getCities() 
{ 
    return cities;
}

string Player::getName()
{
    return name;
}

int Player::getId() 
{ 
    return id; 
}


//std::vector<Cards*> *Player::getGameHand() const { return gameHand; }

BidingFacility* Player::getBidingFacility() {
    return bidingFacility;
}


//below are the Mutators
void Player::setId(int id) { this->id = id; }

void Player::setArmies(int armies) { this->armies = armies; }

void Player::setCoins(int coins) { this->coins = coins; }

void Player::setCities(int cities) { this->cities = cities; }

void Player::setName(std::string name) { this->name = name; }

//Here is the PayCoin method. Using if else, we can determine the purchess succession. 
bool Player::payCoin(int cost)
{
    if (coins < cost) {
        std::cout << "INSUFFICIENT FUNDS" << "\n";
        return false;
    }
    else {
        setCoins(coins - cost);
        std::cout << "Success!!!!! " << name << ", you have " << coins << " coins left." << "\n" << "\n";
        return true;
    }
}

void Player::placeNewArmies()
{
    /*
    // below we test to see if the player has sufficienmt armies to place.
    if (armies == 0) {
        std::cout << "Error! " << name << "INSUFFICIENT armies." << "\n";
        return;
    }

    int disposableArmies;
    std::string regionName;
    std::vector<std::string> placementRegions;

    // place remainding armies if the player cannot fufill ard value.
    if (totalArmies > armies) {
        disposableArmies = armies;
    }
    else {
        disposableArmies = totalArmies;
    }
    */
}

void Player::buildCity()
{
    // Veryify players cities and if they can place them.
    if (cities == 0) {
        std::cout << "ERRROR " << name << "INSUFFICIENT cities." << "\n";
        return;
    }
}

//below is the method that enables the player to destroy the army of an opponent
void Player::destroyArmy()
{
    /*
        std::string playerName;
        std::string regionName;
        bool invalidPlayerName = false;

        gameBoard.destroyArmy(regionName, playerName);
        std::cout << "SUCCESS!!! Please removed one of " << playerName << "'s armies from " << regionName<< "\n";
    */
}
//Note*** a vector? will be implemented later on to represent which cards the player has in hand. 

