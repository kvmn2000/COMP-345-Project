
#include "Map.h"
#include "GameEngine.h"
#include "MapLoader.h"
#include "Cards.h"
#include "Player.h"
#include "ActionObserver.h"

using namespace std;

int main(int argc, const char* argv[]) {

	const string mapDirectory = "./Maps/";
	GameEngine* game = new GameEngine(mapDirectory);
	ActionObserver* actionObserver = new ActionObserver(game);
	game->startUp();

	game->~GameEngine();
	delete actionObserver;
	return 0;

}