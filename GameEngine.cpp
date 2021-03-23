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
    bidingList = new BidingList();
    players = {};
}

GameEngine::GameEngine(const string mapDirectory)
{
    bidingList = new BidingList();
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
    delete gameMap;
    gameMap = NULL;

    delete gameDeck;
    gameDeck = NULL;

    delete bidingList;
    bidingList = NULL;

    for (int i = 0; i < players.size(); ++i) {
        delete players[i];
        players[i] = NULL;
    }
    players.clear();
}

// create new player objectinitializing its ID and pushing it into vector players
void GameEngine::gameStart(const string mapDirectory)
{
    createGameMap(mapDirectory);
    createPlayers();
    createDeck();
};

void GameEngine::createGameMap(const string directory) {
   
    gameMap = maploader.selectMap(directory);
    cout << endl << "AMOUNT OF COUNTRIES:" << gameMap->countryCount() << endl;

}

// Gets input from the user for the amount of players that should be created
void GameEngine::createPlayers() {

    cout << endl << "---CHOOSING THE NUMBER OF PLAYERS---" << endl;
    cout << "Select amount of players (2 - 5): " << endl;
    int numPlayers = getUserInputInteger("Your choice (-1 to quit): ", 2, 6);
    cout << endl;

    for (int i = 0; i < numPlayers; i++) {
        cout << "Created Player with ID: " << (i + 1) << "." << endl;
        Player* thePlayer = new Player(i + 1);
        players.push_back(thePlayer);

        cout << "Added player to a biding list" << endl;
        bidingList->addPlayer((thePlayer)->getBidingFacility());
        cout << endl;
    }
}

void GameEngine::createDeck() {
    gameDeck = new Deck();
    cout << endl << "---A DECK HAS BEEN CREATED---" << endl;
    cout << endl << "---EACH PLAYER HAS ALSO BEEN ASSIGNED A EMPTY HAND---" << endl;
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


