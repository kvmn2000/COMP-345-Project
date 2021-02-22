#pragma once

#include "Map.h"

#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include <fstream>

using namespace std;

class MapLoader {

public:
	MapLoader();
	MapLoader(string path);
	MapLoader(const MapLoader& copy);
	~MapLoader();

	string getPath(MapLoader maploader);
	Map getMap();
	void load(string path);
	MapLoader& operator=(const MapLoader& other);
	friend ostream& operator <<(ostream& os, const MapLoader& other);
	friend istream& operator >>(istream& is, MapLoader& other);

private:
	string fpath;
	Map* map;
	bool valid;
	bool readFile(string name);
	bool validFile(string path);
};