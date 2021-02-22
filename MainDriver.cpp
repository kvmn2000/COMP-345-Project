#include "Map.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"
#include "BidingFacility.h"


using namespace std;

int main(int argc, const char* argv[]) {


	cout << "Loading map with file name Map.txt\n" << endl;
	MapLoader maploader("Map.txt");
	Map gameMap = maploader.getMap();
    cout << endl;


    vector<Country*> countrylist = gameMap.getCountries();
    vector<Continent*> continentlist = gameMap.getContinents();


    for (auto& temp : continentlist) {

        cout << "Continent Name: " << temp->getName();

        for (auto& temp2 : temp->getContinentCountries()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    for (auto& temp : countrylist) {

        cout << "Country Name: " << temp->getName();

        for (auto& temp2 : temp->getNeighbors()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    int numOfPlayers;
    cout << "Enter number of players: " << "\n";
    cin >> numOfPlayers;

    vector<Player*> playerList(numOfPlayers);
    BidingList bidinglist;

    for (int i = 0; i < numOfPlayers; i++) {
        string name;
        cout << "Enter a player name?" << "\n";
        cin >> name;

        // Create player list
        playerList[i] = new Player(name,numOfPlayers);
    }

    cout << endl;
    cout << "Players have been added"<< "\n";
    cout << endl;

    //vector<Player*>current_player;
    vector<Player*>::iterator iter, end;
    for (iter = playerList.begin(), end = playerList.end(); iter != end; ++iter) {
        // Output Information about the test user
        cout << "Player name:" << (*iter)->getName() << "\n";
        cout << "Each Player will start with: " << "\n";
        cout << "- " << (*iter)->getCoins() << " coins." << "\n";
        cout << "- " << (*iter)->getArmies() << " armies." << "\n";
        cout << "- " << (*iter)->getCities() << " cities." << "\n";

        cout << "Adding player to BidingList." << endl;
        bidinglist.addPlayer((*iter)->getBidingFacility());
        cout << endl;
      
    }

   cout << "Bidder wins by highest bidding" << endl;
   BidingFacility highestbidder = bidinglist.bid();

  

    return 0;
}