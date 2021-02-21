#include <iostream>
#include <string>
#include <vector>
#include Map.h
#include BuildingFacility.h

using namespace std;

//declaring classes from other parts
class BiddingFacility;
class Cards;
class Map;

class Player {

        public:
            //below are the constructors 
            Player();
            Player(string name);
            Player(string name, int numOfPlayers);
            Player(const Player& copy);

            //payCoin method
            bool payCoin(int cost);

            //other gameplay methods
            void placeNewArmies(int totalArmies, Map &gameBoard);
            void moveArmies(int totalMoves, Map &gameBoard);
            void moveOverLand(int totalMoves, Map &gameBoard);
            void buildCity(Map &gameBoard);
            void destroyArmy(Map &gameBoard, vector<Player *> allPlayers);
            bool ignore();
            void andOrAction(string action, Map &gameBoard, vector<Player *> &allPlayers);
            void takeAction(string action, Map &gameBoard, vector<Player *> &allPlayers);

            //below are the accessors
             int getArmies() const;
             int getCoins() const;
             int getCities() const;
             string getName() const;
             vector<Cards*> getGameHand() const;
             BiddingFacility getBiddingFacility() const;

            //below are the Mutators
             void setArmies(int armies);
             void setCoins(int coins);
             void setCities(int cities);
             void setName(string name);

            //our private constructors
            private:
            int coins;
            int armies;
            int cities;
            string name;
            vector <Cards*> gameHand;
            BiddingFacility *biddingFacility; 


};