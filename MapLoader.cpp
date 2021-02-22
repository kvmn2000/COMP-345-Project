#include "MapLoader.h"
//Kevin Nguyen Comp-345
//MAP LOADER COMPILATION UNIT This program is used to load in maps from .txt files into the program.

//default constructor
MapLoader::MapLoader() {
	map = new Map();
	fpath = "";
}

//constructor with string parameter, calls readfile
MapLoader::MapLoader(string path) {
	map = new Map();
	fpath = path;
	valid = readFile(fpath);
}

//copy constructor
MapLoader::MapLoader(const MapLoader& copy) {
	map = new Map(*copy.map);
	fpath = copy.fpath;
	valid = copy.valid;
}

//assignment operator
MapLoader& MapLoader::operator=(const MapLoader& copy) {
	return *(new MapLoader(copy));
}

//stream insertion operator
ostream& operator<<(ostream& os, const MapLoader& copy) {
	os << "path: " << copy.fpath << ", validity: " << copy.valid << ", Map Loaded: " << copy.map;
	return os;
}

//stream extraction operator
istream& operator>>(istream& is, MapLoader& copy) {
	cout << "Enter new file path: " << endl;
	is >> copy.fpath;
	copy.load(copy.fpath);
	return is;
}

//destructor
MapLoader::~MapLoader() {
	map = NULL;
}

//returns file path
string MapLoader::getPath(MapLoader maploader) {
	return fpath;
}

//if the map is valid, it will return the map, if it is invalid, it will return an empty map
Map MapLoader::getMap() {
	if (valid) {
		return *map;
	}
	else {
		return Map();
	}
}

//loads in a different file into map loader
void MapLoader::load(string path) {
	if (!map->getCountries().empty()) {
		delete map;
		map = new Map();
	}
	fpath = path;
	valid = readFile(fpath);
}

//reads a file line by line then creates a graph of the map outlined in the file.
//it reads the nodes, then the edges.
bool MapLoader::readFile(string path) {
	if (!validFile(path)) {
		cout << "This file is invalid." << endl;
		return false;
	}
	ifstream file_reader(path);
	string current_continent = "";
	string current_country = "";
	bool readingContinent = false;
	bool readingEdge = false;

	for (string line; getline(file_reader, line);) {
		if (line == "}" || line == "]") {
			readingContinent = false;
			readingEdge = false;
		}
		if (readingContinent) {
			current_country = line;

			Country* country = new Country(current_country, current_continent);

			map->addCountry(country);
			map->getContinent(current_continent)->addCountrytoContinent(country);

		}
		if (readingEdge) {
			string neighbor = line;
			map->getCountry(current_country)->addNeighbor(new Country(neighbor));
			//cout << "Added " << neighbor << " to " << current_country << endl;
		}
		if (line.find('{') != string::npos) {
			readingContinent = true;
			current_continent = line.substr(0, line.find('{'));
			Continent* continent = new Continent(current_continent);
			map->addContinent(continent);
		}
		if (line.find('[') != string::npos) {
			readingEdge = true;
			current_country = line.substr(0, line.find('['));
		}
	}

	if (map->toValidate()) {
		cout << "This map is valid." << endl;
		return true;
	}
	else {
		cout << "This map is invalid." << endl;
		return false;
	}
}

//only accepts .txt files
bool MapLoader::validFile(string path) {
	return path.substr(path.length() - 4, path.length() - 1) == ".txt";
}