#include "BidingFacility.h"
#include <Windows.h>
//Kevin Nguyen Comp-345 Biding Facilities let players bid coins against one another to see who is the highest bidder
//Constructors for BidingFacilities

//Default Constructor
BidingFacility::BidingFacility(){
	coins = 0;
	player_name = "";
}

//Constructor with name parameter
BidingFacility::BidingFacility(string name) {
	coins = 0;
	player_name = name;
}

//Copy Constructor, only shallow copy
BidingFacility::BidingFacility(const BidingFacility& b) {
	coins = b.coins;
	player_name = b.player_name;
}

//Assignment operator for BidingFacility
BidingFacility& BidingFacility::operator=(const BidingFacility& copy) {
	return *(new BidingFacility(copy));
}

//Insetion operator for BidingFacility
ostream& operator<<(ostream& os, BidingFacility& copy) {
	os << copy.getName() << "'s Biding Facility, Coins put in: " << copy.getCoins();
	return os;
}

//Getters and Setters
//Returns name
string BidingFacility::getName() {
	return player_name;
}

//Returns amount of coins
int BidingFacility::getCoins() {
	return coins;
}

//Changes name of BidingFacility to name in parameter
void BidingFacility::setName(string name) {
	player_name = name;
}

//Changes coins of BidingFacility to int in parameter
void BidingFacility::setCoins(int n) {
	coins = n;
}

//Default constructor
BidingList::BidingList() {
	size = 0;
}

//Copy constructor for biding list
BidingList::BidingList(const BidingList& copy) {
	for (BidingFacility* i : copy.players) {
		addPlayer(new BidingFacility(*i));
		i = nullptr;
	}
	size = players.size();
}

//Assignment operator for biding list
BidingList& BidingList::operator=(const BidingList& copy) {
	return *(new BidingList(copy));
}

//insertion operator for biding list
ostream& operator<<(ostream& os, const BidingList& copy) {
	for (BidingFacility* i : copy.players) {
		os << i;
		i = nullptr;
	}
	return os;
}

//Returns size of list
int BidingList::getSize() {
	return size;
}

//Adds a player's bidingfacility in the list, increments size by 1
void BidingList::addPlayer(BidingFacility* player){
	players.push_back(player);
	size++;
}

//Asks user input, input is hidden from the console. Asks for how many coins the player would like to bid. This cycles through all the players in the BidingList
bool BidingList::startBidding() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	string hidden_input;
	for (BidingFacility* i : players) {
		int coins;
		cout << "Enter how many coins you would like to bid " << i->getName()<< ":" << endl;
		getline(cin, hidden_input);
		coins = std::stoi(hidden_input);
		i->setCoins(coins);
		i = nullptr;
	}

	SetConsoleMode(hStdin, mode);
	return false;
}

//Destructor of BidingList
BidingList::~BidingList() {
	while (!players.empty()) {
		delete players.front();
		players.front() = nullptr;
		players.pop_front();
	}
	players.clear();
}

//Goes through bidding process with startBidding(), then from the user input, it chooses the highest bidder.
/*
If there is a tie for the highest bid, it chooses the winner based on their name by alphabetical order
Consequently, this also applies when all bids are zero.
*/
BidingFacility& BidingList::bid() {
	startBidding();
	printList();
	int max = 0;
	for (BidingFacility* i : players) {
		if (i->getCoins() >= max) {
			max = i->getCoins();
		}
		i = nullptr;
	}
	list<BidingFacility*> winners;
	for (BidingFacility* i : players) {
		if (i->getCoins() >= max) {
			winners.push_back(i);
		}
		i = nullptr;
	}
	if (winners.size() == 1) {
		BidingFacility& winner = *winners.front();
		winners.front() = nullptr;
		resetCoins(winner.getName());
		cout << winner.getName() << " won with the highest bid!" << endl;
		return winner;
	}
	else {
		string winners_name = winners.front()->getName();
		for (BidingFacility* i : winners) {
			if (winners_name.compare(i->getName())>0) {
				winners_name = i->getName();
			}
			i = nullptr;
		}
		BidingFacility* winnerptr = winners.front();
		while (!winners.empty()) {
			if (winners.front()->getName() == winners_name) {
				winnerptr = winners.front();
			}
			winners.front() = nullptr;
			winners.pop_front();
		}
		BidingFacility& winner = *winnerptr;
		resetCoins(winners_name);
		cout << winners_name << " won in a tie!" << endl;
		return winner;
	}
}

//resets all of the BidingLists's BidingFacilitys' coins except for the winner
//Eventually, there will be a method that takes the winners coins and puts them in a supply as well as remove said amount of coins from the player object
void BidingList::resetCoins(string winners_name) {
	for (BidingFacility* i : players) {
		if (winners_name != i->getName()) {
			i->setCoins(0);
		}
		i = nullptr;
	}
}

//prints the list of BidingFacilities in the BidingList
void BidingList::printList() {
	for (BidingFacility* i : players) {
		cout << i->getName() << "'s BidingFacility, they put in " << i->getCoins() << " coin(s)." << endl;
		i = nullptr;
	}
}
