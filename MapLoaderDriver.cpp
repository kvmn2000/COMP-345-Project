#include "MapLoader.h"

int main(int argc, const char* argv[]) {
	
	MapLoader maploader("Map.txt");
	Map map = *(maploader.load());
}