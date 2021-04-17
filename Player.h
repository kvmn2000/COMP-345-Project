#include "Map.h"
#include "BidingFacility.h"
#include "Cards.h"
#include "PlayerStrategies.h"

using namespace std;

struct Score {
    int* continentScore;
    int* regionScore;
    int* goodScore;
};

class Player {

public:
    typedef pair<Country, int> countryValue;
    Map* map;
    PlayerStrategy* strategy;
    string* name;
    int* disks;
    int* tokens;
    int* armies;
    int* age;
    Score* score;
    int getTotalScore();
    BidingFacility* bidding;
    vector<Card*>* hand;
    vector<countryValue>* citiesIn;
    vector<countryValue>* armiesIn;

    Player(Map* map, string name, int diskNum, int tokenNum, int armyNum);
    void setStrategy(PlayerStrategy* strategy);
    int pickCard(Hand* hand);
    int submitAge();
    bool PayCoin(int coins);
    bool PlaceNewArmies(int armiesNum, Country* country, bool forceAdd);
    bool MoveArmies(int armiesNum, Country* to, Country* from);
    bool MoveOverLand(int armiesNum, Country* to, Country* from);
    bool MoveOverWater(int armiesNum, Country* to, Country* from);
    bool BuildCity(Country* country);
    bool DestroyArmy(Country* country, Player* player);
    bool Ignore();
    void display();
    pair<Country, int>* getArmiesInCountry(Country* country);
    pair<Country, int>* getCitiesInCountry(Country* country);
    void armyDestroyed(Country* country);
    void setDisks(int disk);
    void setTokens(int token);
    void setArmies(int army);
    void printGoods();
    void computeTotalGoodScore();
};