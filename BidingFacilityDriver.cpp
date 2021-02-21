#include "BidingFacility.h";
#include <Windows.h>

int main(int argc, char* argv[]) {

	cout << "Adding Sal, Tony, and Bob to the BidingList." << endl;
	BidingFacility* biding1 = new BidingFacility("Sal");
	BidingFacility* biding2 = new BidingFacility("Tony");
	BidingFacility* biding3 = new BidingFacility("Bob");
	BidingList bidinglist;
	bidinglist.addPlayer(biding1);
	bidinglist.addPlayer(biding2);
	bidinglist.addPlayer(biding3);
	cout << "Bidder wins by highest bidding" << endl;
	BidingFacility highestbidder = bidinglist.bid();
	//By a tie
	cout << "Bidder wins by tie and name in alphabetical order" << endl;
	BidingFacility highestbidder2 = bidinglist.bid();
	//By all bids are 0
	cout << "Bidder wins by tie with all bids being zero" << endl;
	BidingFacility highestbidder3 = bidinglist.bid();
	biding1 = nullptr;
	biding2 = nullptr;
	biding3 = nullptr;
	return 0;
}