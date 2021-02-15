#include "MapLoader.h"

MapLoader::MapLoader(string name) {
	fpath = name;
	readFile(name);
	cout << map.countryCount()<< endl;
	cout << "Neighbours of Venezuela in the map" << endl;
	cout << map.getCountry("Venezuela")->hasNeighbors() << endl;
	vector<Country*> countries = map.getContinent("South America")->getContinentCountries();
	cout << "Neighbours of Venezuela taken from map from Continent South America" << endl;
	cout << countries.at(1)->hasNeighbors() << endl;
}

string MapLoader::getPath(MapLoader maploader) {
	return fpath;
}

Map MapLoader::load() {
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
			
			map.addCountry(country);
			map.getContinent(current_continent)->addCountrytoContinent(country);
			
		}
		if (readingEdge) {
			string neighbor = line;
			map.getCountry(current_country)->addNeighbor(new Country(neighbor));
		}
		if (line.find('{') != string::npos) {
			readingContinent = true;
			current_continent = line.substr(0, line.find('{'));
			//cout << current_continent << endl;
			Continent* continent = new Continent(current_continent);
			map.addContinent(continent);
		}
		if (line.find('[') != string::npos) {
			readingEdge = true;
			current_country = line.substr(0, line.find('['));
		}
	}
}