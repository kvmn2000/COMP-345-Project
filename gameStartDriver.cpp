#include "Map.h"
#include "GameEngine.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"



using namespace std;

int main(int argc, const char* argv[]) {
	
	const string mapDirectory = "./Maps/";
	GameEngine* game = new GameEngine(mapDirectory);

	return 0;
}