#pragma once
#include <stdio.h>
#include "Player.h"
#include "Cards.h"
#include "Map.h"

using namespace std;


class GameStats {

public:

    // Constructors/Destructor
    GameStats(vector<Player*> players, Map* graph);
    ~GameStats();

    // Methods
    void computeGameScore();
    void computeGameStatsOnCardDraw();

private:

    // Properties
    vector<Player*> players;
    Map* map;

    // Methods
    bool isGameEnd();
    void processRegionsScore();
    void processContinentsScore();

    void listScoreAndStatistics();
    void determineWinnerByScore();
    void determineWinnerByArmies();
    void determineWinnerByCoins();
    void determineWinnerByControlledRegions();
    bool isPlayerCardsRequirementMet();
    void checkRoundScoring(Player*);
};