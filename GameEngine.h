#pragma once

#include "Map.h"
#include "Player.h"
#include "MapLoader.h"
#include "Cards.h"
#include "BidingFacility.h"
#include "GameObserver.h"


#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <math.h> 

using namespace std;

class GameEngine : public Subject {

public:

    GameEngine();
    GameEngine(const string mapDirectory);
    GameEngine(const GameEngine& obj);
    ~GameEngine();
    friend ostream& operator<<(ostream&, const GameEngine&);
    GameEngine& operator=(const GameEngine& copy);

    Deck* getDeck();
    vector<Player*> getPlayers();
    Map* getMap();
    Hand* topBoardGenetor();
    void displayTopBoard(Hand& topBoard);

    void buyCard();
    void useCard(Card& card);
    void endTurn();

    void gameLoop();
    void startUp();



private:

    Map* gameMap;
    Deck* gameDeck;
    BidingList* bidinglist;
    vector<Player*> players; //vector of all players that has been created
    int players_turn = 1;
    int turn = 0;
    Hand* topBoard;
    MapLoader maploader;
    int posArray[6] = { 0, 1, 1, 2, 2, 3 };
    int coinPool;

    void gameStart(const string mapDirectory);
    void createPlayers();
    void createGameMap(const string mapDirectory);
    void createDeck();
    void coinDistribution();
    void resourceDistribution();
    void bidingListDisplay();
    void placingArmy();

    int getUserInputInteger(string, int, int);
    string getUserInputString(string, string, string);
  
};