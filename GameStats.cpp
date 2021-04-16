#include "GameStats.h"

using namespace std;

// Constructor
GameStats::GameStats(vector<Player*> playersList, Map* graph) {
    players = playersList;
    map = graph;
}

// Destructor
GameStats::~GameStats() {
    // Delete the players.
    for (std::vector<Player*>::size_type i = 0; i != players.size(); i++) {
        Player* temp = players[i];
        delete temp;
    }
};

// Compute game score for each player based on criteria
void GameStats::computeGameScore() {
    processRegionsScore();
    processContinentsScore();
    listScoreAndStatistics();

    // Determine winner
    if (isGameEnd()) {
        determineWinnerByScore();
    }
}

// Determines whether game is over based on # of players and # of cards in their hand
bool GameStats::isGameEnd() {
    bool isGameEnd = true;

    if (players.size() == 2) {
        for (int i = 0; i < 2; i++) {
            if (players.at(i)->getCardCount() != 13) {
                isGameEnd = false;
            }
        }

        if (isGameEnd) {
            cout << endl << "STOP GAME. " << "All players are currently holding 13 cards." << endl;
        }
    }
    else if (players.size() == 3) {
        for (int i = 0; i < 3; i++) {
            if (players.at(i)->getCardCount() != 10) {
                isGameEnd = false;
            }
        }

        if (isGameEnd) {
            cout << endl << "STOP GAME. " << "All players are currently holding 10 cards." << endl;
        }
    }
    else if (players.size() == 4) {
        for (int i = 0; i < 4; i++) {
            if (players.at(i)->getCardCount() != 8) {
                isGameEnd = false;
            }
        }

        if (isGameEnd) {
            cout << endl << "STOP GAME. " << "All players are currently holding 8 cards." << endl;
        }

    }
    else if (players.size() == 5) {
        for (int i = 0; i < 5; i++) {
            if (players.at(i)->getCardCount() != 7) {
                isGameEnd = false;
            }
        }

        if (isGameEnd) {
            cout << endl << "STOP GAME. " << "All players are currently holding 7 cards." << endl;
        }
    }

    return isGameEnd;
}

// Determine winner for each country/region node
void GameStats::processRegionsScore() {
    
    vector<Node*> countries = map->getCountries();

    // Compute region score
    for (int i = 0; i < countries.size(); i++) {
        vector<Army*> armies = countries.at(i)->getArmies();
        vector<int> playerArmyCityCounts;

        // Instantiate
        for (int i = 0; i < players.size(); i++) {
            playerArmyCityCounts.push_back(0);
        }

        // Army count based on # of soliders placed in node
        for (int d = 0; d < map->getCountries().at(i)->getArmies().size(); d++) {
            int numOfSoldiers = *map->getCountries().at(i)->getArmies()[d]->getNumberOfSoldiers();
            players[*map->getCountries().at(i)->getArmies()[d]->getOwnerNumber() - 1]->setPlayerNumOfArmiesBasedOnSoldiers(numOfSoldiers);
        }

        // Find player with max combo of # of armies and # of cities in a given location
        for (int j = 0; j < armies.size(); j++) {
            int currentOwnerNumber = *armies.at(j)->getOwnerNumber() - 1;
            int numOfCities = 0;

            // Process each city in this location to see to whom it belongs to
            for (int h = 0; h < countries.at(i)->getCities().size(); h++) {
                vector<City*> playerCities = players[currentOwnerNumber]->getCities();
                City* city = countries[i]->getCities()[h]; // Current city in iteration

                if (*city->getOwnerNumber() == (currentOwnerNumber + 1)) {
                    auto result = find(playerCities.begin(), playerCities.end(), city);
                    if (result != playerCities.end()) {
                        numOfCities++;
                    }
                }
            }

            // Store count for comparison later
            int total = *armies.at(j)->getNumberOfSoldiers() + numOfCities;
            playerArmyCityCounts[currentOwnerNumber] += total;
        }

        // Get highest score
        int max = 0;
        for (int i = 0; i < playerArmyCityCounts.size(); i++) {
            if (playerArmyCityCounts[i] > max) {
                max = playerArmyCityCounts[i];
            }
        }

        // Determine country winner by highest score for country
        int counter = 0;
        for (int k = 0; k < playerArmyCityCounts.size(); k++) {
            if (playerArmyCityCounts[k] == max) {
                counter++;
            }
        }

        // There is only one winner per region/country
        if (counter == 1) {
            for (int k = 0; k < playerArmyCityCounts.size(); k++) {
                if (playerArmyCityCounts[k] == max) {
                    players.at(k)->addCountry(countries[i]);
                }
            }
        }
    }
}

// Determine winner for each continent
void GameStats::processContinentsScore() {
    
    vector<Map*> continents = map->getContinents();

    for (int i = 0; i < continents.size(); i++) {
        vector<int> playerCountryCounts;
        for (int c = 0; c < players.size(); c++) {
            playerCountryCounts.push_back(0);
        }

        // Process each country within given continent
        vector<Node*> countries = continents[i]->getCountries();
        for (int j = 0; j < countries.size(); j++) {

            for (int k = 0; k < players.size(); k++) {
                vector<Node*> playerCountries = players[k]->getCountries();

                auto result = find(playerCountries.begin(), playerCountries.end(), countries[j]);

                if (result != playerCountries.end()) {
                    playerCountryCounts[k]++;
                }
            }
        }

        // Determine which player has highest count of countries
        int max = 0;
        for (int x = 0; x < playerCountryCounts.size(); x++) {
            if (playerCountryCounts[x] > max) {
                max = playerCountryCounts[x];
            }
        }

        int counter = 0;
        for (int y = 0; y < playerCountryCounts.size(); y++) {
            if (playerCountryCounts[y] == max) {
                counter++;
            }
        }

        // There is only one winner with max score
        if (counter == 1) {
            for (int z = 0; z < playerCountryCounts.size(); z++) {
                if (playerCountryCounts[z] == max) {
                    players[z]->addContinent(continents[i]);
                }
            }
        }
    }
}


// Display the score and stats for each player
void GameStats::listScoreAndStatistics() {
    cout << endl << "-------------------- GAME STATS --------------------" << endl;

    for (int i = 0; i < players.size(); i++) {
        int score = 0;

        // Compute regions score
        score += players.at(i)->getCountries().size();

        // Compute continents score
        score += players.at(i)->getContinents().size();

        // Compute goods score
        score += computeGoodsScore(players.at(i));

        // Set and display score & statistics
        players.at(i)->setPlayerScore(score);

        cout << "Player " << to_string(i + 1) << " (" << players.at(i)->getName() << ") - score: " << players.at(i)->getPlayerScore() << ", coins: " << *players.at(i)->getPlayerCoins() << ", armies: " << players.at(i)->getArmyCountBasedOnSoldiers() << ", regions: " << players.at(i)->getCountries().size() << ", continent: " << players.at(i)->getContinents().size() << ", cities: " << players.at(i)->getCities().size() << endl << endl;
    }

    cout << "Note: # of '*' represent the player #." << endl;

    // Display bar graph
    cout << "---------- CONTINENTS ----------" << endl;
    vector<Map*> continents = map->getContinents();
    for (int i = 0; i < continents.size(); i++) {
        cout << *continents[i]->getName() << " ";

        for (int j = 0; j < players.size(); j++) {
            vector<Map*> playerContinents = players[j]->getContinents();

            auto result = find(playerContinents.begin(), playerContinents.end(), continents[i]);

            if (result != playerContinents.end()) {
                // Print stars corresponding to player number
                for (int k = 0; k <= j; k++) {
                    cout << "*";
                }
            }
        }

        cout << endl;
    }

    cout << endl << "---------- COUNTRIES ----------" << endl;
    vector<Node*> countries = map->getCountries();
    for (int i = 0; i < countries.size(); i++) {
        cout << *countries[i]->getName() << " ";

        for (int j = 0; j < players.size(); j++) {
            vector<Node*> playerCountries = players[j]->getCountries();

            auto result = find(playerCountries.begin(), playerCountries.end(), countries[i]);

            if (result != playerCountries.end()) {
                // Print stars corresponding to player number
                for (int k = 0; k <= j; k++) {
                    cout << "*";
                }
            }
        }

        cout << endl;
    }

    cout << endl;
}

// Determine winner based on score
void GameStats::determineWinnerByScore() {
    int max = 0;

    for (int i = 0; i < players.size(); i++) {
        if (players.at(i)->getPlayerScore() > max) {
            max = players.at(i)->getPlayerScore();
        }
    }

    int counter = 0;
    for (int k = 0; k < players.size(); k++) {
        if (players.at(k)->getPlayerScore() == max) {
            counter++;
        }
    }

    // There is only one winner with max score
    if (counter == 1) {
        for (int k = 0; k < players.size(); k++) {
            if (players.at(k)->getPlayerScore() == max) {
                cout << "Winner by score is " << "player " << players.at(k)->getName() << endl;
            }
        }
    }
    else {
        determineWinnerByCoins();
    }
}

// Determine winner based on on # of armies
void GameStats::determineWinnerByArmies() {
    int max = 0;

    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getArmyCountBasedOnSoldiers() > max) {
            max = players[i]->getArmyCountBasedOnSoldiers();
        }
    }

    int counter = 0;
    for (int k = 0; k < players.size(); k++) {
        if (players[k]->getArmyCountBasedOnSoldiers() == max) {
            counter++;
        }
    }

    // There is only one winner with max armies
    if (counter == 1) {
        for (int k = 0; k < players.size(); k++) {
            if (players[k]->getArmyCountBasedOnSoldiers() == max) {
                cout << "Winner by armies is " << "player " << players.at(k)->getName() << endl;
            }
        }
    }
    else {
        determineWinnerByControlledRegions();
    }
}

// Determine winner based on # of coins
void GameStats::determineWinnerByCoins() {
    int maxCoins = 0;

    for (int i = 0; i < players.size(); i++) {
        if (*players.at(i)->getPlayerCoins() > maxCoins) {
            maxCoins = *players.at(i)->getPlayerCoins();
        }
    }

    int coinsCounter = 0;
    for (int k = 0; k < players.size(); k++) {
        if (*players.at(k)->getPlayerCoins() == maxCoins) {
            coinsCounter++;
        }
    }

    // There is only one winner with max armies
    if (coinsCounter == 1) {
        for (int k = 0; k < players.size(); k++) {
            if (*players.at(k)->getPlayerCoins() == maxCoins) {
                cout << "Winner by coins is " << "player " << players.at(k)->getName() << endl;
            }
        }
    }
    else {
        determineWinnerByArmies();
    }
}

// Determine winner based on highest # of controlled region
void GameStats::determineWinnerByControlledRegions() {
    int maxRegions = 0;

    for (int i = 0; i < players.size(); i++) {
        if (players[i]->getCountries().size() > maxRegions) {
            maxRegions = players[i]->getCountries().size();
        }
    }

    int counter = 0;
    for (int k = 0; k < players.size(); k++) {
        if (players[k]->getCountries().size() == maxRegions) {
            counter++;
        }
    }

    // There is only one winner with max # of controlled regions
    if (counter == 1) {
        for (int k = 0; k < players.size(); k++) {
            if (players.at(k)->getCountries().size() == maxRegions) {
                cout << "Winner by controlled regions is " << "player " << players.at(k)->getName() << endl;
            }
        }
    }
    else {
        cout << "There is no winner." << endl;
    }
}

// Displays game stats
void GameStats::computeGameStatsOnCardDraw() {
    if (isPlayerCardsRequirementMet()) {
        if (players.size() == 2) {
            cout << endl << "A player is currently holding 13 cards." << endl;
        }
        else if (players.size() == 3) {
            cout << endl << "A player is currently holding 10 cards." << endl;
        }
        else if (players.size() == 4) {
            cout << endl << "A player is currently holding 8 cards." << endl;
        }
        else if (players.size() == 5) {
            cout << endl << "A player is currently holding 7 cards." << endl;
        }
    }

    computeGameScore();
}

// Determines if the required # of cards in a player's hands is met
bool GameStats::isPlayerCardsRequirementMet() {
    bool isRequirementMet = false;

    if (players.size() == 2) {
        for (int i = 0; i < 2; i++) {
            if (players.at(i)->getCardCount() == 13) {
                isRequirementMet = true;
                break;
            }
        }
    }
    else if (players.size() == 3) {
        for (int i = 0; i < 3; i++) {
            if (players.at(i)->getCardCount() == 10) { // Change to 3 cards to test driver with 3 players
                isRequirementMet = true;
                break;
            }
        }
    }
    else if (players.size() == 4) {
        for (int i = 0; i < 4; i++) {
            if (players.at(i)->getCardCount() == 8) {
                isRequirementMet = true;
                break;
            }
        }
    }
    else if (players.size() == 5) {
        for (int i = 0; i < 5; i++) {
            if (players.at(i)->getCardCount() == 7) {
                isRequirementMet = true;
                break;
            }
        }
    }

    return isRequirementMet;
}