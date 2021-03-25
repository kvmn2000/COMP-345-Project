#include "Cards.h"



//Card Constructor
Cards::Cards(int numOfGood, string good, string action) {
    this->numOfGood = numOfGood;
    this->good = good;
    this->action = action;
}

ostream& operator<<(ostream& os, const Cards& cards) {
    os << cards.getGood() << " (" << cards.getNumOfGood() << ") - " << cards.getAction();
    return os;
}

Cards::~Cards() {

}

//Accessor methods.
string Cards::getGood() const {
    return good;
}

//Mutator methods.
void Cards::setGood(string good) {
    this->good = good;
}

//Accessor methods.
string Cards::getAction() const {
    return action;
}

//Mutator methods.
void Cards::setAction(string action) {
    this->action = action;
}


//Accessor methods.
int Cards::getNumOfGood() const {
    return numOfGood;
}

//Mutator methods.
void Cards::setNumOfGood(int numOfGood) {
    this->numOfGood = numOfGood;
}

//All cards in the deck by good and action

Cards* cards01 = new Cards(1, "Wild", "MOVE_OVER_WATER 2");
Cards* cards02 = new Cards(1, "Wild", "MOVE_OVER_WATER 2");
Cards* cards03 = new Cards(1, "Wild", "PLACE_NEW_ARMIES_ON_BOARD 2");
Cards* cards04 = new Cards(1, "Crystal", "PLACE_NEW_ARMIES_ON_BOARD 2");
Cards* cards05 = new Cards(1, "Crystal", "PLACE_NEW_ARMIES_ON_BOARD 2");
Cards* cards06 = new Cards(1, "Crystal", "PLACE_NEW_ARMIES_ON_BOARD 2");
Cards* cards07 = new Cards(1, "Crystal", "PLACE_NEW_ARMIES_ON_BOARD 1");
Cards* cards08 = new Cards(1, "Crystal", "MOVE_OVER_GROUND 2");
Cards* cards09 = new Cards(1, "Rock", "MOVE_OVER_GROUND 2");
Cards* cards10 = new Cards(1, "Rock", "MOVE_OVER_WATER 2");
Cards* cards11 = new Cards(1, "Rock", "MOVE_OVER_WATER 2");
Cards* cards12 = new Cards(1, "Rock", "MOVE_OVER_WATER 3");
Cards* cards13 = new Cards(1, "Rock", "PLACE_NEW_ARMIES_ON_BOARD 3");
Cards* cards14 = new Cards(1, "Rock", "PLACE_NEW_ARMIES_ON_BOARD 3");
Cards* cards15 = new Cards(1, "Rock", "PLACE_NEW_ARMIES_ON_BOARD 2 OR BUILD_A_CITY 1");
Cards* cards16 = new Cards(1, "Carrot", "BUILD_A_CITY 1");
Cards* cards17 = new Cards(1, "Carrot", "DESTROY_ARMY 1 AND PLACE_NEW_ARMIES_ON_BOARD 1");
Cards* cards18 = new Cards(1, "Carrot", "PLACE_NEW_ARMIES_ON_BOARD 3");
Cards* cards19 = new Cards(1, "Carrot", "MOVE_OVER_GROUND 4");
Cards* cards20 = new Cards(1, "Carrot", "MOVE_OVER_GROUND 4");
Cards* cards21 = new Cards(1, "Carrot", "PLACE_NEW_ARMIES_ON_BOARD 4 OR MOVE_OVER_GROUND 2");
Cards* cards22 = new Cards(1, "Carrot", "MOVE_OVER_GROUND 5");
Cards* cards23 = new Cards(1, "Carrot", "BUILD_A_CITY 1");
Cards* cards24 = new Cards(1, "Carrot", "MOVE_OVER_WATER 3");
Cards* cards25 = new Cards(2, "Carrot", "PLACE_NEW_ARMIES_ON_BOARD 3");
Cards* cards26 = new Cards(1, "Tree", "MOVE_OVER_GROUND 5");
Cards* cards27 = new Cards(1, "Tree", "MOVE_OVER_GROUND 6");
Cards* cards28 = new Cards(1, "Tree", "PLACE_NEW_ARMIES_ON_BOARD 2 OR MOVE_OVER_GROUND 3");
Cards* cards29 = new Cards(1, "Tree", "DESTROY_ARMY 1 OR BUILD_A_CITY 1");
Cards* cards30 = new Cards(1, "Tree", "PLACE_NEW_ARMIES_ON_BOARD 3");
Cards* cards31 = new Cards(1, "Tree", "MOVE_OVER_WATER 4");
Cards* cards32 = new Cards(1, "Tree", "MOVE_OVER_WATER 3");
Cards* cards33 = new Cards(1, "Tree", "BUILD_A_CITY 1");
Cards* cards34 = new Cards(1, "Anvil", "PLACE_NEW_ARMIES_ON_BOARD 3");
Cards* cards35 = new Cards(1, "Anvil", "PLACE_NEW_ARMIES_ON_BOARD 3");
Cards* cards36 = new Cards(1, "Anvil", "MOVE_OVER_WATER 3");
Cards* cards37 = new Cards(1, "Anvil", "BUILD_A_CITY 1");
Cards* cards38 = new Cards(2, "Anvil", "MOVE_OVER_GROUND 4");
Cards* cards39 = new Cards(1, "Anvil", "MOVE_OVER_GROUND 5");
Cards* cards40 = new Cards(1, "Anvil", "MOVE_OVER_GROUND 4");
Cards* cards41 = new Cards(1, "Anvil", "PLACE_NEW_ARMIES_ON_BOARD 3 OR MOVE_OVER_GROUND 4");
Cards* cards42 = new Cards(1, "Anvil", "PLACE_NEW_ARMIES_ON_BOARD 3 OR MOVE_OVER_GROUND 3");


Deck::Deck() {

 
    position = 0;
    deck.push_back(cards01);
    deck.push_back(cards02);
    deck.push_back(cards03);
    deck.push_back(cards04);
    deck.push_back(cards05);
    deck.push_back(cards06);
    deck.push_back(cards07);
    deck.push_back(cards08);
    deck.push_back(cards09);
    deck.push_back(cards10);
    deck.push_back(cards11);
    deck.push_back(cards12);
    deck.push_back(cards13);
    deck.push_back(cards14);
    deck.push_back(cards15);
    deck.push_back(cards16);
    deck.push_back(cards17);
    deck.push_back(cards18);
    deck.push_back(cards19);
    deck.push_back(cards20);
    deck.push_back(cards21);
    deck.push_back(cards22);
    deck.push_back(cards23);
    deck.push_back(cards24);
    deck.push_back(cards25);
    deck.push_back(cards26);
    deck.push_back(cards27);
    deck.push_back(cards28);
    deck.push_back(cards29);
    deck.push_back(cards30);
    deck.push_back(cards31);
    deck.push_back(cards32);
    deck.push_back(cards33);
    deck.push_back(cards34);
    deck.push_back(cards35);
    deck.push_back(cards36);
    deck.push_back(cards37);
    deck.push_back(cards38);
    deck.push_back(cards39);
    deck.push_back(cards40);
    deck.push_back(cards41);
    deck.push_back(cards42);
}

//Deck Generation 

Deck::~Deck() {

    cout << "---------- DELETING DECK -----------" << endl;
   
    while (!deck.empty()) {
        delete deck.back();
        deck.back() = nullptr;
        deck.pop_back();
    }

    while (!deck.empty()) {
        delete topBoard.back();
        topBoard.back() = nullptr;
        topBoard.pop_back();
    }

}

//The draw method shuffles the deck and draws (returns) the cards for the user. 
Cards* Deck::draw() {

    std::srand(unsigned(std::time(0)));
    std::random_shuffle(deck.begin(), deck.end());

    auto card = deck.back();
    deck.pop_back();

    return card;

}

//This generates what cards will be at the top of the board. 
std::vector<Cards*> Deck::topBoardGenetor(Deck& deck) {
    auto tb = new std::vector<Cards*>();
    for (auto i = 0; i < 6; i++) {
        tb->emplace_back(deck.draw());
    }
    return *tb;
}

//This diplays the availible cards at the top of the board.
void Deck::displayTopBoard(std::vector<Cards*>& topBoard) {
    int j = 0;
    int index = 0;
    for (auto it = topBoard.begin(); it != topBoard.end(); ++it) {
        cout << ++j << ") " << posArray[index++] << " Coins - " << **it << endl;
    }
}

//Updates what cards are at the top of the board. 
void Deck::updateTopBoard(int& position, std::vector<Cards*>& topBoard, Deck& deck) {
    int index = position - 1;
    topBoard.erase(topBoard.begin() + index);
    cout << "Top Board cards series size is " << topBoard.size() << endl;
    topBoard.emplace_back(deck.draw());
    cout << "Top Board cards series size is " << topBoard.size() << endl;
    displayTopBoard(topBoard);
}

//Generates the user's hand of cards.
std::vector<Cards*> Deck::handGenetor(Cards*& card) {
    std::vector<Cards*> hand;
    hand.emplace_back(card);
    return hand;
}

//Displays the user's hand of cards. 
void Deck::displayHand(std::vector<Cards*>& hand) {
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        std::cout << ' ' << *it << endl;
    }
}

//Here is the echange method to exchange the user's cards. 
//Eventually we will add a way for players to pay for the card using their coins, right now it shows the cost of the card.
void Deck::exchange(std::vector<Cards*>& topBoard, Deck& deck) {
    bool successfullPurchase = false;
    int cost, position, index;

    // Displays the top board before user purchases a card
    cout << "Top Board:" << endl;
    displayTopBoard(topBoard);

    // Prompt/Allows the user to purchase a card.
    cout << "Which card do you want to buy? Please enter an integer from 1 to 6: " << endl;
    do {
        cin >> position;
        if (position < 1 || position > 6) {
            cout << "Invalid input: " << position << ". Please enter an integer from 1 to 6: " << endl;
            continue;
        }
        if (position == 1) {
            cost = 0;
        }
        else if (position == 2 || position == 3) {
            cost = 1;
        }
        else if (position == 4 || position == 5) {
            cost = 2;
        }
        else if (position == 6) {
            cost = 3;
        }
        successfullPurchase = payCoin(cost);
    } while (!successfullPurchase);

    // purchase confirmation
    index = position - 1;
    cout << "You have bought: " << topBoard.front()->getAction() << endl;
    // update gamehand and update top board
    delete topBoard[index];
    topBoard[index] = nullptr;
    topBoard.erase(topBoard.begin() + index);
    topBoard.emplace_back(deck.draw());
}

//Eventually Players will be made to pay their coins for cards, but right now it just shows the price of the card
bool Deck::payCoin(int cost) {
    cout << "The cost of this card is " << cost << " coins." << endl;
    return true;
}

void Deck::shuffleDeck() {

    cout << endl << "---------- SHUFFLING DECK -----------" << endl;
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(deck.begin(), deck.end());
}
