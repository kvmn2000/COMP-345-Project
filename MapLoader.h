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
	MapLoader();
	MapLoader(string path);
	~MapLoader();

	string getPath(MapLoader maploader);
	Map getMap();
	void load(string path);
private:
	string fpath;
	Map* map;
	bool valid;
	bool readFile(string name);
	bool validFile(string path);
};