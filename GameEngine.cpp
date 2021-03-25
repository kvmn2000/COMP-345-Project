#include "GameEngine.h"

#include <algorithm>
#include<random>
#include <limits>
#include <stdio.h>
#include <string.h>


GameEngine::GameEngine()
{
    gameMap = NULL;
    gameDeck = NULL;
    bidinglist = NULL;
    players = {};
}

GameEngine::GameEngine(const string mapDirectory)
{
    bidinglist = new BidingList();
    coinPool = 36;
    gameStart(mapDirectory);
}

GameEngine::GameEngine(const GameEngine& obj)
{
    this->gameMap = new Map(*(obj.gameMap));
    this->gameDeck = new Deck(*(obj.gameDeck));


    for (int index = 0; index < obj.players.size(); index++)
        this->players[index] = new Player(*(obj.players[index]));

}

GameEngine& GameEngine::operator=(const GameEngine& copy)
{
    this->gameMap = new Map(*(copy.gameMap));
    this->gameDeck = new Deck(*(copy.gameDeck));

    for (int index = 0; index < copy.players.size(); index++)
        this->players[index] = new Player(*(copy.players[index]));
    return *this;
}

GameEngine::~GameEngine()
{
    cout << endl << endl << "----------- DELETING GAME COMPONENTS -----------" << endl << endl;

    gameMap->~Map();
    gameMap = NULL;

    gameDeck->~Deck();
    gameDeck = NULL;

    // Need to fix
    cout << "---------- DELETING BIDING LIST -----------" << endl;
    // Need to fix
    cout << "---------- DELETING PLAYERS -----------" << endl;
   

}

// create new player objectinitializing its ID and pushing it into vector players
void GameEngine::gameStart(const string mapDirectory)
{
    createGameMap(mapDirectory);
    createPlayers();
    createDeck();
};

void GameEngine::startUp() {
    
    gameDeck->shuffleDeck();
    topBoard = topBoardGenetor(*gameDeck);
    displayTopBoard(topBoard);
    coinDistribution();
    resourceDistribution();
    bidingListDisplay();
   
}

void GameEngine::createGameMap(const string directory) {
   
    gameMap = maploader.selectMap(directory);
    cout << endl << "AMOUNT OF COUNTRIES:" << gameMap->countryCount() << endl;

}

// Gets input from the user for the amount of players that should be created
void GameEngine::createPlayers() {

    cout << endl << "---CHOOSING THE NUMBER OF PLAYERS---" << endl;
    cout << "Select amount of players (2 - 4): " << endl;
    int numPlayers = getUserInputInteger("Your choice (-1 to quit): ", 2, 6);
    cout << endl;

    for (int i = 0; i < numPlayers; i++) {
        string playerName;
        cout << "Created Player with ID: " << (i + 1) << "." << endl;
        cout << "Pick a name for player " << (i + 1) << ": ";
        cin >> playerName;
        Player* thePlayer = new Player(i + 1, playerName);
        players.push_back(thePlayer);

        cout << "Added player to a biding list" << endl;
        BidingFacility* biding = new BidingFacility(thePlayer->getName());
        bidinglist->addPlayer(biding);
        cout << endl;
    }
}

void GameEngine::createDeck() {
    gameDeck = new Deck();
    cout << endl << "---A DECK HAS BEEN CREATED---" << endl;
}

Deck* GameEngine::getDeck()
{
    return gameDeck;
}

vector<Player*> GameEngine::getPlayers()
{
    return players;
}

Map* GameEngine::getMap()
{
    return gameMap;
}

//This generates what cards will be at the top of the board. 
vector<Cards*> GameEngine::topBoardGenetor(Deck& deck) {
    auto tb = new std::vector<Cards*>();
    for (auto i = 0; i < 6; i++) {
        tb->emplace_back(deck.draw());
    }
    return *tb;
}

//This diplays the availible cards at the top of the board.
void GameEngine::displayTopBoard(std::vector<Cards*>& topBoard) {
    
    cout << endl << "---------- DISPLAYING TOP BOARD -----------" << endl;

    int j = 0;
    int index = 0;
    for (auto it = topBoard.begin(); it != topBoard.end(); ++it) {
        cout << ++j << ") " << posArray[index++] << " Coins - " << **it << endl;
    }
}

void GameEngine::coinDistribution(){
   
    cout << endl << "----------- DISTRIBUTING COINS TO PLAYERS ------------" << endl;

    switch (players.size()) {
    
    case 2:
        for (int i = 0; i < players.size(); i++) {
            cout << "Player with ID:" << players[i]->getId() << " will receive 14 coins" << endl;
            players[i]->setCoins(14);
            coinPool = coinPool - 14;
        }
        break;
    case 3:
        for (int i = 0; i < players.size(); i++) {
            cout << "Player with ID:" << players[i]->getId() << " will receive 11 coins" << endl;
            players[i]->setCoins(11);
            coinPool = coinPool - 11;
        }
        break;
    case 4:
        for (int i = 0; i < players.size(); i++) {
            cout << "Player with ID:" << players[i]->getId() << " will receive 9 coins" << endl;
            players[i]->setCoins(9);
            coinPool = coinPool - 9;
        }
        break;
    default:{}

    }
}

void GameEngine::bidingListDisplay() {

    cout << endl << "----------- DISTRIBUTING COINS TO PLAYERS ------------" << endl;

    cout << "Bidder wins by highest bidding" << endl;
    BidingFacility highestbidder = bidinglist->bid();
 
 
}

void GameEngine::resourceDistribution() {

    cout << endl << "----------- DISTRIBUTING RESOURCES TO PLAYERS ------------" << endl;

    for (int i = 0; i < players.size(); i++) {
        cout << "Player with ID " << players[i]->getId() << " will receive 18 armies" << endl;
        players[i]->setArmies(18);
    }

    cout << endl;

    for (int i = 0; i < players.size(); i++) {
        cout << "Player with ID " << players[i]->getId() << " will receive 3 cities" << endl;
        players[i]->setCities(3);
    }
}
   
// Helper function for getting user integer input
int GameEngine::getUserInputInteger(string output, int min, int max) {
    string inputString;
    int input;
    bool failFlag;

    cout << output;
    cin >> inputString;

    try {
        input = stoi(inputString);
        failFlag = false;
    }
    catch (invalid_argument e) {
        failFlag = true;
    }

    // While the input is invalid
    while (input < min || input > max || cin.fail() || failFlag || inputString.find(".") != string::npos) {
        if (input == -1) {
            cout << "Quitting..." << endl;
            exit(1);
        }

        cin.clear();
        //cin.ignore(numeric_limits<streamsize> std::max, '\n');
        cout << "Invalid input" << endl;

        if (inputString.find(".") == string::npos) {
            cout << "Must be greater than " << min - 1 << " and less than " << max + 1 << " and must be an integer" << endl;
        }
        else {
            cout << "Must be an integer" << endl;
        }
        cout << "Try again (-1 to quit): ";
        cin >> inputString;

        try {
            input = stoi(inputString);
            failFlag = false;
        }
        catch (invalid_argument e) {
            failFlag = true;
        }
    }

    return input;
}

// Helper function for getting user string input
string GameEngine::getUserInputString(string output, string choice1, string choice2) {

    string input;

    cout << output;
    cin >> input;

    // While the input is invalid
    while ((input != choice1 && input != choice2) || cin.fail() || input == "q" || input == "Q") {
        if (input == "q" || input == "Q") {
            cout << "Quitting..." << endl;
            exit(1);
        }

        // Clear the stream
        cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input" << endl;
        cout << "Must be " << choice1 << " or " << choice2 << " and must be a string" << endl;
        cout << "Try again ('q' to quit): ";
        cin >> input;
    }

    return input;
}


