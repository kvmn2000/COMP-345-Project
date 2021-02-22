#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Cards.h"
#include <iostream>

void main()
{
    // **check for memory leaks**
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //test Deck and draw() exchange
    std::cout<< "Testing the Deck, the topBoard, hand generation and the draw( )/exchange( ) methods"<< endl;
    Deck deck1;
    std::vector<Cards*> tb = deck1.topBoardGenetor(deck1);
    deck1.exchange(tb, deck1);
    deck1.exchange(tb, deck1);
    deck1.displayTopBoard(tb);
    while (!tb.empty()) {
        delete tb.back();
        tb.back() = nullptr;
        tb.pop_back();
    }
}