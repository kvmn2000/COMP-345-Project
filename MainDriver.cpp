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


    vector<Player*>current_player;
    vector<Player*>::iterator iter, end;
    for (iter = current_player.begin(), end = current_player.end(); iter != end; ++iter) {
        // Output Information about the test user
        cout << "Player name:" << (*iter)->getName() << "\n";
        cout << "Each Player will start with: " << "\n";
        cout << "- " << (*iter)->getCoins() << " coins." << "\n";
        cout << "- " << (*iter)->getArmies() << " armies." << "\n";
        cout << "- " << (*iter)->getCities() << " cities." << "\n";

        cout << "Adding player to BidingList." << endl;
        bidinglist.addPlayer((*iter)->getBidingFacility());
      
    }

    cout << "Bidder wins by highest bidding" << endl;
    BidingFacility highestbidder = bidinglist.bid();
    //By a tie
    cout << "Bidder wins by tie and name in alphabetical order" << endl;
    BidingFacility highestbidder2 = bidinglist.bid();
    //By all bids are 0
    cout << "Bidder wins by tie with all bids being zero" << endl;
    BidingFacility highestbidder3 = bidinglist.bid();
  
    /*

    cout << "Testing the Deck, the topBoard, hand generation and the draw( )/exchange( ) methods" << endl;
    Deck deck1;
    std::vector<Cards*> tb = deck1.topBoardGenetor(deck1);
    std::vector<Cards*>* hand = new std::vector<Cards*>();
    deck1.exchange(*hand, tb, deck1);
    deck1.exchange(*hand, tb, deck1);
    deck1.displayTopBoard(tb);
    */

    return 0;
}