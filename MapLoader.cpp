#include "MapLoader.h"

MapLoader::MapLoader(string name) {
	map = new Map();
	fpath = name;
	readFile(name);
}

string MapLoader::getPath(MapLoader maploader) {
	return fpath;
}

Map* MapLoader::load() {
	return map;
}

void MapLoader::readFile(string path) {
	ifstream file_reader(path);
	string current_continent = "";
	string current_country = "";
	bool readingContinent = false;
	bool readingEdge = false;
	for (string line; getline(file_reader, line);) {
		//cout << line << endl;
		if (line == "}" || line == "]") {
			readingContinent = false;
			readingEdge = false;
		}
		if (readingContinent) {
			current_country = line;
			//cout << current_country << endl;
			
			Country* country = new Country(current_country, current_continent);
			
			map->addCountry(country);
			map->getContinent(current_continent)->addCountrytoContinent(country);
			
		}
		if (readingEdge) {
			string neighbor = line;
			map->getCountry(current_country)->addNeighbor(new Country(neighbor));
			cout << "Added " << neighbor << " to " << current_country << endl;
		}
		if (line.find('{') != string::npos) {
			readingContinent = true;
			current_continent = line.substr(0, line.find('{'));
			//cout << current_continent << endl;
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
	}
	else {
		cout << "This map is invalid. Closing program." << endl;
		exit(-1);
	}
}