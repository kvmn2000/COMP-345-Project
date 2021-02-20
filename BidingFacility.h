#pragma once
#include <string>
#include <iostream>
#include <list>

using namespace std;

class BidingFacility {

public:
	BidingFacility();
	BidingFacility(string name);
	BidingFacility(const BidingFacility& copy);
	void setCoins(int n);
	void setName(string name);
	int getCoins();
	string getName();
	BidingFacility& operator=(const BidingFacility& other);
	friend ostream& operator << (ostream& os, const BidingFacility& other);
private:
	int coins;
	string player_name;
};

class BidingList {

public:
	BidingList();
	BidingList(const BidingList& copy);
	~BidingList();
	void addPlayer(BidingFacility* player);
	int getSize();
	void printList();
	BidingFacility& bid();
	BidingList& operator=(const BidingList& other);
	friend ostream& operator << (ostream& os, const BidingList& other);
private:
	list<BidingFacility*> players;
	int size;
	bool startBidding();
	void resetCoins(string winners_name);
};
