#include "Player.h"
void PlayerDriver() {


     // Info from guest players
     std::cout << "Eight-Minute-Empire!!!!! Enter number of players: " << "\n";
     std::cin >> numOfPlayers;
     std::cout << "Enter your name?" << "\n";
     std::cin >> name;

     // Create user
     Player* guestPlayer = new Player(name, numOfPlayers);

     // Output Information about the test user
     std::cout << "Hello " << guestPlayer->getName() << "\n";
     std::cout << "Each Guest Player will start with: " << "\n";
     std::cout << "- " << guestPlayer->getCoins() << " coins." << "\n";
     std::cout << "- " << guestPlayer->getArmies() << " armies." << "\n";
     std::cout << "- " << guestPlayer->getCities() << " cities." << "\n";
 }