#pragma once
#define _DEBUG
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
#include <string>
#include <ostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace std;

class Cards
{

private:
    int* numOfGood;
    string* good;
    string* action;

public:
    // The constructors
    Cards();
    Cards(int numOfGood, string good, string action);
    ~Cards();

    // The accessor methods
    string getGood() const;
    string getAction() const;
    int getNumOfGood() const;

    // The mutator methods
    void setGood(string good);
    void setAction(string action);
    void setNumOfGood(int numOfGood);

    // operator overides
    friend ostream& operator<<(ostream& os, const Cards& cards);
};

class Deck
{

private:
    int* cost;
    int* position;
    int posArray[6] = { 0, 1, 1, 2, 2, 3 };
    vector<Cards*> topBoard;
    vector<Cards*> deck;

public:
    // constructor
    Deck();
    ~Deck();

    // gameplay methods
    Cards* draw();
    vector<Cards*> topBoardGenetor(Deck& deck);
    void displayTopBoard(vector<Cards*>& topBoard);
    void updateTopBoard(int& position, vector<Cards*>& topBoard, Deck& deck);
    vector<Cards*> handGenetor(Cards*& card);
    void displayHand(vector<Cards*>& hand);
    void exchange(vector<Cards*>& topBoard, Deck& deck);
    bool payCoin(int cost);
};