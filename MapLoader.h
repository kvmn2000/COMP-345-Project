#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include "Map.h"
#include <fstream>

using namespace std;

class MapLoader {

public:
	MapLoader() = default;
	MapLoader(string path);

	string getPath(MapLoader maploader);
	Map load();
private:
	string fpath;
	Map map;
	void readFile(string name);
};