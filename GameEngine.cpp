
#include "GameEngine.h"

#include <algorithm>
#include<random>
#include <limits>
#include <stdio.h>
#include <string>


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

    gameDeck->shuffle();
    topBoard = topBoardGenetor();
    displayTopBoard(*topBoard);
    coinDistribution();
    resourceDistribution();
    placingArmy();
    bidingListDisplay();
}

void GameEngine::gameLoop(int t) {
    while (turn < t) {
        cout << "\n\n\n" << players[players_turn]->getName() << "'s Turn:" << endl;
        buyCard();
        endTurn();
    }
}

void GameEngine::createGameMap(const string directory) {

    gameMap = maploader.selectMap(directory);

    cout << endl << " ------------LIST OF COUNTRIES-----------"  << endl;

    for (int i = 0; i < gameMap->getCountries().size(); i++) {
        cout << gameMap->getCountries()[i]->getName() << endl;

    }
}

// Gets input from the user for the amount of players that should be created
void GameEngine::createPlayers() {

    cout << endl << "---CHOOSING THE NUMBER OF PLAYERS---" << endl;
    cout << "Select amount of players (2 - 4): " << endl;
    int numPlayers = getUserInputInteger("Your choice (-1 to quit): ", 2, 6);
    cout << endl;

    for (int i = 0; i < numPlayers; i++) {
        string playerName;
        int type = 0;

        cout << "Created Player with ID: " << (i + 1) << "." << endl;
        cout << "Pick a name for player " << (i + 1) << ": ";
        cin >> playerName;
        Player* thePlayer = new Player(gameMap, playerName, 0, 0, 0);

        cout << "\nChoose mode for Player" << (i + 1) << ": (0 for human players, 1 for greedy computer player or 2 for moderate computer player): "<<endl;
        int numPlayers = getUserInputInteger("Your choice (-1 to quit): ", 0, 2);

       
        if (type == 1) {
            thePlayer->setStrategy(new GreedyComputerStrategy);
        }
        if (type== 2) {
            thePlayer->setStrategy(new ModerateComputerStrategy);
        }
        else {
            thePlayer->setStrategy(new HumanStrategy);
        }
        players.push_back(thePlayer);
        cout << "Added player to a biding list" << endl;
        BidingFacility* biding = new BidingFacility(thePlayer->getName());
        bidinglist->addPlayer(biding);
        cout << endl;

    }

   
     

}

void GameEngine::createDeck() {
    gameDeck = new Deck();
    gameDeck->generateDeck();
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
Hand* GameEngine::topBoardGenetor() {
    topBoard = new Hand(gameDeck);
    return topBoard;
}

//This diplays the availible cards at the top of the board.
void GameEngine::displayTopBoard(Hand& topBoard) {

    cout << endl << "---------- DISPLAYING TOP BOARD -----------" << endl;
    topBoard.printHand();
}

void GameEngine::coinDistribution() {

    cout << endl << "----------- DISTRIBUTING COINS TO PLAYERS ------------" << endl;

    switch (players.size()) {

    case 2:
        for (int i = 0; i < players.size(); i++) {
            cout << players[i]->getName() << " will receive 14 coins" << endl;
            players[i]->setTokens(14);
            coinPool = coinPool - 14;
        }
        break;
    case 3:
        for (int i = 0; i < players.size(); i++) {
            cout << players[i]->getName() << " will receive 11 coins" << endl;
            players[i]->setTokens(11);
            coinPool = coinPool - 11;
        }
        break;
    case 4:
        for (int i = 0; i < players.size(); i++) {
            cout << players[i]->getName() << " will receive 9 coins" << endl;
            players[i]->setTokens(9);
            coinPool = coinPool - 9;
        }
        break;
    default: {}

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
        cout << players[i]->getName() << " will receive 18 armies" << endl;
        players[i]->setArmies(18);
    }

    cout << endl;

    for (int i = 0; i < players.size(); i++) {
        cout << players[i]->getName() << " will receive 3 cities" << endl;
        players[i]->setDisks(3);
    }
}

void GameEngine::placingArmy() {


    cout << endl << "----------- PLACING PLAYERS ARMY ------------" << endl;

    //place armies at starting point
    cout << "Place 4 armies on the starting region of the board! (" << gameMap->startingRegion->getName() << ")" << endl;
    for (auto player : players) {
        cout <<"Player " << player->getName() <<" ";
        player->PlaceNewArmies(4, gameMap->startingRegion, true);
    }

    //place cities at starting point
    cout << "\nPlace 1 city on the starting region of the board! (" << gameMap->startingRegion->getName() << ")" << endl;
    for (auto player : players) {
        cout << "Player " << player->getName() << " ";
        player->BuildCity(gameMap->startingRegion);
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

void GameEngine::endTurn() {
  
    if (players_turn == players.size()) {
        players_turn = 0;
    }
    else {
        players_turn++;
    }
    turn++;
}

void GameEngine::buyCard() {
    displayTopBoard(*topBoard);
    Card* card = nullptr;
    int index = 0;
    while (card == nullptr) {
        cout << "Write a number from 0 to 5 to choose the card you want. " << endl;
        index = getUserInputInteger("Choose -1 to quit the game. ", 0, 5);
        card = topBoard->exchange(index, players[players_turn]);

    }
    //will print bought card statement
    notify(-1, index, topBoard->cardCost(index));
    card->printCard();
    useCard(*card);
}

void GameEngine::useCard(Card& card) {
    Card::CombinationType comboType = card.combinationType;
    vector<Action> actionsTaken;

    cout << "Using Card:" << endl;
    //finds which combo type the card has
    switch (comboType) {
    case Card::OR: {
        int input = 0;
        while (input < 1 || input > 2) {
            cout << "Write a numbers 1 or 2 to choose between the 2 actions: " << endl;
            card.printCard();
            cin >> input;
        }
        actionsTaken.push_back(card.actions[input - 1]);
        break;
    }
    case Card::SINGLE:
        actionsTaken.push_back(card.actions[0]);
        break;
    case Card::AND:
        actionsTaken.push_back(card.actions[0]);
        actionsTaken.push_back(card.actions[1]);
        break;
    }

    //takes care of all the actions on the card
    while (!actionsTaken.empty()) {
        cout << actionsTaken.back().getName() << endl;
        int count = actionsTaken.back().count;
        int code = 0;
        int armiesNum = 0;
        string countryName;
        string playerName;
        bool success;

        switch (actionsTaken.back().type) {
        case Action::ACTION_ADD_ARMY: {
            Country* country = nullptr;
            code = 0;
            while (count > 0) {
                while (!country) {
                    cout << "Name the country you wish to add armies in:" << endl;
                    cin >> ws;
                    getline(cin, countryName);
                    country = gameMap->findCountry(countryName);
                }
                do {
                    cout << "\n How many armies to add? " << endl;
                    cin >> armiesNum;
                } while (armiesNum < 0 || cin.fail() || armiesNum > count);
                success = players[players_turn]->PlaceNewArmies(armiesNum, country, false);
                if (success) {
                    count -= armiesNum;
                    country = nullptr;
                    cout << "You have " << count << " actions left." << endl;
                }
            }
            break;
        }
        case Action::ACTION_BUILD_CITY: {
            Country* country = nullptr;
            code = 1;
            players[players_turn]->setDisks(*players[players_turn]->disks + count);
            while (count > 0) {
                while (!country) {
                    cout << "Name the country to build your city in: " << endl;
                    cin >> ws;
                    getline(cin, countryName);
                    country = gameMap->findCountry(countryName);
                }
                success = players[players_turn]->BuildCity(country);
                if (success) {
                    count--;
                    cout << "You have " << count << " actions left." << endl;
                }
            }
            break;
        }
        case Action::ACTION_DESTROY_ARMY: {
            Player* playerToDestroy = nullptr;
            Country* countryToDestroy = nullptr;
            code = 2;
            while (count > 0) {
                while (!playerToDestroy) {
                    cout << "Name the player of which you want to destroy their army: ";
                    cin >> playerName;
                    playerToDestroy = findPlayer(playerName);
                }
                while (!countryToDestroy) {
                    cout << "Name the country of which you want to destroy its army: " << endl;
                    cin >> ws;
                    getline(cin, countryName);
                    countryToDestroy = gameMap->findCountry(countryName);
                }
                success = players[players_turn]->DestroyArmy(countryToDestroy, playerToDestroy);
                if (success) {
                    count--;
                    cout << "You have " << count << " actions left." << endl;
                }
            }
            cout << endl;
            break;
        }
        case Action::ACTION_MOVE_OVER_LAND: {
            Country* to = nullptr;
            Country* from = nullptr;
            code = 3;
            while (count > 0) {
                armiesNum = 0;
                while (!from) {
                    cout << "Name the country you want to move your armies from: " << endl;
                    cin >> ws;
                    getline(cin, countryName);
                    from = gameMap->findCountry(countryName);
                }
                while (!to) {
                    cout << "Name the country you want to move your armies to: " << endl;
                    cin >> ws;
                    getline(cin, countryName);
                    to = gameMap->findCountry(countryName);
                }
                do {
                    cout << "How many armies to move? ";
                    cin >> armiesNum;
                } while (armiesNum < 0 || armiesNum > players[players_turn]->getArmiesInCountry(from)->second);
                success = players[players_turn]->MoveOverLand(armiesNum, to, from);
                if (success) {
                    count--;
                    to = nullptr;
                    from = nullptr;
                    cout << "You have " << count << " actions left." << endl;
                }
            }
            break;
        }
        case Action::ACTION_MOVE_OVER_LAND_OR_WATER: {
            Country* to = nullptr;
            Country* from = nullptr;
            code = 4;
            while (count > 0) {
                armiesNum = 0;
                while (!from) {
                    cout << "Name the country you want to move your armies from: " << endl;
                    cin >> ws;
                    getline(cin, countryName);
                    from = gameMap->findCountry(countryName);
                }
                while (!to) {
                    cout << "Name the country you want to move your armies to: " << endl;
                    cin >> ws;
                    getline(cin, countryName);
                    to = gameMap->findCountry(countryName);
                }
                do {
                    cout << "\n How many armies to move? " << endl;
                    cin >> armiesNum;
                } while (armiesNum < 0 || cin.fail() || armiesNum > players[players_turn]->getArmiesInCountry(from)->second);

                success = players[players_turn]->MoveOverWater(armiesNum, to, from) || players[players_turn]->MoveOverLand(armiesNum, to, from);
                if (success) {
                    count--;
                    to = nullptr;
                    from = nullptr;
                    cout << "You have " << count << " actions left." << endl;
                }
            }
            break;
        }
        }
        // notifies the action observer for which action was done
        notify(code, 0, actionsTaken.back().count);
        actionsTaken.pop_back();
    }
}

Player* GameEngine::findPlayer(string player_name) {
    for (auto& i : players) {
        if (player_name == i->getName()) {
            return i;
        }
    }
}