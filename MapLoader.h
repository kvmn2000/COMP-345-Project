#pragma once

#include "Map.h"
#include "dirent.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class MapLoader {

public:

	MapLoader();
	~MapLoader();
	MapLoader(const MapLoader& copy);

	Map* selectMap(const string mapDirectory);
	string getFileName();

	MapLoader& operator = (const MapLoader& copy);
	friend ostream& operator <<(ostream& os, const MapLoader& other);
	friend istream& operator >>(istream& is, MapLoader& other);

private:

	string fileName;

	Map* loadMap(string fileName);
	vector<string>displayAllMaps(const string mapDirectory);
	int getUserInputInteger(string, int, int);
	string getUserInputString(string, string, string);

};