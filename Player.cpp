#include "Player.h"
#include <string>
#include <iostream>
#include "Map.h"

//default constructor with parameter
Player::Player(std::string name)
{
    Player::cities;
    Player::armies;
    Player::coins;
    Player::name;
    Player::gameHand;
    Player::biddingFacility;

}

//default constructor with number of players.
Player::Player(std::string name, int numOfPlayers)
{
    Player::cities;
    Player::armies;
    Player::coins;
    Player::name;
    Player::gameHand;
    Player::biddingFacility;

//Number of players decides how many coins they will recieve. 2 players = 14 coins, 3=11 coins and so on.
    switch (numOfPlayers)
    {
        case 2:
            Player::coins = new int(14);
            break;
        case 3:
            Player::coins = new int(11);
            break;
        case 4:
            Player::coins = new int(9);
            break;
        case 5:
            Player::coins = new int(8);
            break;
    }
}
//below are the accessors

int Player::getArmies() const { return *armies; }

int Player::getCoins() const { return *coins; }

int Player::getCities() const { return *cities; }

std::string Player::getName() const { return *name; }

std::vector<Cards*> *Player::getGameHand() const { return gameHand; }

BiddingFacility *Player::getBiddingFacility() const { return biddingFacility; }

//below are the Mutators

void Player::setArmies(int armies) { *Player::armies = armies; }

void Player::setCoins(int coins) { *Player::coins = coins; }

void Player::setCities(int cities) { *Player::cities = cities; }

void Player::setName(std::string name) { *Player::name = name; }


//Here is the PayCoin method. Using if else, we can determine the purchess succession. 
bool Player::payCoin(int cost)
{
    if (coins < cost) {
        std::cout << "INSUFFICIENT FUNDS" << "\n";
        return false;
    }
    else {
        setCoins(coins - cost);
        std::cout << "Success!!!!! " << name << ", you have " << coins << " coins left." << "\n"<< "\n";
        return true;
    }
}


void Player::placeNewArmies(int totalArmies, Map &gameBoard)
{
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

}

void Player::buildCity(Map &gameBoard)
{
    // Veryify players cities and if they can place them.
    if (cities == 0) {
        std::cout << "ERRROR " << name << "INSUFFICIENT cities." << "\n";
        return;
    }

//below is the method that enables the player to destroy the army of an opponent
void destroyArmy(Map &gameBoard, std::vector<Player *> allPlayers)
{
    std::string playerName;
    std::string regionName;
    bool invalidPlayerName = false;

    gameBoard.destroyArmy(regionName, playerName);
    std::cout << "SUCCESS!!! Please removed one of " << playerName << "'s armies from " << regionName<< "\n";
}


