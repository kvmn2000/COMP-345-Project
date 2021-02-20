#include "MapLoader.h"

int main(int argc, const char* argv[]) {
	cout << "Loading valid map, Map.txt\n" << endl;
	MapLoader maploader("Map.txt");
	Map map = maploader.getMap();
	cout << "\nLoading invalid map, Map1.txt\n" << endl;
	maploader.load("Map1.txt");

	cout << "\nLoading invalid map, Map2.jpg\n" << endl;
	maploader.load("Map2.jpg");
}