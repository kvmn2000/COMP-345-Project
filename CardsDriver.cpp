#include "Cards.h"
#include <iostream>

void cardsDriverExamples()
{
    //test Deck and draw() exchange
    std::cout<< "Testing the Deck, the topBoard, hand generation and the draw( )/exchange( ) methods"<< endl;
    Deck deck1;
    std::vector<Cards*> tb = deck1.topBoardGenetor(deck1);
    std::vector<Cards*> *hand = new std::vector<Cards*>();
    deck1.exchange(*hand, tb, deck1);
    deck1.exchange(*hand, tb, deck1);
    deck1.displayTopBoard(tb);
}