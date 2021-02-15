#include "Map.h"

/*
    COUNTRY CLASS
*/

// Country constructor with name as argument
Country::Country(string country_Name)
{
	name = country_Name;
	armie = 0;
}

// Country constructor with name and continent as arguments
Country::Country(string country_Name, string continent_Name)
{
	name = country_Name;
	continentName = continent_Name;
	armie = 0;
}

// Country constructor with name, continent, neighbors and armie as arguments
Country::Country(string country_Name, string continent_Name, vector<Country*> neighbor_countries, int playerArmie)
{
	name = country_Name;
	continentName = continent_Name;
	neighbors = neighbor_countries;
	armie = playerArmie;
}

// Copy constructor
Country::Country(const Country& copy) {

	string* copyName = new string(copy.name);
	name = *copyName;
	string* copyContinent = new string(copy.continentName);
	continentName = *copyContinent;
	int* copyArmy = new int(copy.armie);
	armie = *copyArmy;
	for (auto temp : copy.neighbors) {
		this->neighbors.push_back(new Country(*temp));
	}

}


Country::~Country(){

	for (auto& p : neighbors)
	{
		delete p;
		p = NULL;
	}
	neighbors.clear();
	
}


Country& Country::operator=(const Country& copy)
{
	cout << "Creating a country copy:" << endl;
	return *(new Country(copy));
}

ostream& operator<<(ostream& out, const Country& copy)
{
	out << copy.name;
	return out;
}

istream& operator>>(istream& in, Country& copy)
{
	cout << "Enter country name: ";
	in >> copy.name;
	return in;
}

// Returns country name
string Country::getName()
{
	return name;
};

// Returns continent name of country
string Country::getContinentName()
{
	return continentName;
}

// Sets the amount of army
void Country::setArmy(int amount) {
	armie = amount;
}

//  Returns amount of army
int Country::getArmy() {
	return armie;
}

// Returns bool if country has neighbors
bool Country::hasNeighbors()
{
	return !neighbors.empty();
};

// Adds neighbors to country
void Country::addNeighbor(Country* country)
{
	neighbors.push_back(new Country(*country));
}

// Adds a vector of neighbors to country
void Country::setNeighbors(vector<Country*> country_neighbor) 
{
	neighbors = country_neighbor;
}

// Returns the amount has neighbors
int Country::getNeighborAmount()
{
	return (int)neighbors.size();
};

// Returns a vector of neighbors
vector<Country*> Country::getNeighbors() {

	vector<Country*> tempCountries = vector<Country*>();

	for (auto& temp : neighbors) {
		tempCountries.push_back(temp);
	}
	return tempCountries;
}

// Returns a vector of neighbors Name
vector<string> Country::getNeighborsName()
{
	vector<string> neighborsName = vector<string>();
	
	for (auto temp : neighbors){
		neighborsName.push_back(temp->getName());
	}
	return neighborsName;
}




/*
	CONTINENT CLASS
*/

// Continent constructor with name as argument
Continent::Continent(string continent_Name)
{
	name = continent_Name;
}

// Continent constructor with name and it countries as arguments
Continent::Continent(string continent_Name, vector<Country*> continent_countries)
{
	name = continent_Name;
	continentCountries = continent_countries;
}

// Continent copy constructor 
Continent::Continent(const  Continent& copy) {

	name = copy.name;
	for (auto temp : copy.continentCountries) {
		this->continentCountries.push_back(new Country(*temp));
	}
}

// Continent deconstructor
Continent::~Continent()
{
	for (auto p : continentCountries)
	{
		delete p;
		p = NULL;
	}
	continentCountries.clear();
}

Continent& Continent::operator=(const Continent& copy)
{
	cout << "Creating a Territory Copy:" << endl;
	return *(new Continent(copy));
}

ostream& operator<<(ostream& out, const Continent& copy)
{
	out << "Continent name: " << copy.name <<  endl;
	
	return out;
}

istream& operator>>(istream& in, Continent& copy)
{
	cout << "Enter continent name: ";
	in >> copy.name;

	return in;
}

// Returns continent name
string Continent::getName()
{
	return name;
};

// Returns a vector of countries of continent 
vector<Country*> Continent::getContinentCountries()
{
	return continentCountries;
}

// Adds a country to continent 
void Continent::addCountrytoContinent(Country* country)
{
	continentCountries.push_back(new Country(*country));
}

// Returns the number of countries
int Continent::numberOfCountry()
{
	return continentCountries.size();
}

// Check if a country in this continent
bool Continent::checkForCountry(string countryName)
{
	for (int i = 0; i < continentCountries.size(); i++) {
		
		if (countryName == continentCountries[i]->getName()) {
			return true;
		}
	}
	return false;
}




/*
	MAP CLASS
*/


// Map Destructor
Map::~Map()
{
	for (map<string, Country*>::iterator i = countries.begin(); i != countries.end(); ++i) {

		delete i->second;
		i->second = NULL;
	}

	for (map<string, Continent*>::iterator j = continents.begin(); j != continents.end(); ++j) {

		delete j->second;
		j->second = NULL;
	}
}

// Map Copy Constructor
Map::Map(const Map& copy) {

	/*
	for (map<string, Country*>::iterator i = countries.begin(); i != countries.end(); i++) {
		countries.push_back(new Country(*countries[i]));
	}

	for (map<string, Continent*>::iterator i = continents.begin(); i != continents.end(); i++) {
		continents.push_back(new Continent(*i));
	}
	*/
}

Map& Map::operator=(const Map& copy)
{
	return *(new Map(copy));
}

ostream& operator<<(ostream& out, const Map& copy)
{

	return out;
}

istream& operator>>(istream& in, Map& copy)
{

	return in;
}

// Returns the amount of countries
int Map::countryCount()
{
	return (int)countries.size();
}

// Returns the amount of continents
int Map::continentCount() {

	return (int)continents.size();
}

// Add Country object to Map
void Map::addCountry(Country* countryName)
{
	countries[countryName->getName()] = countryName;
};

// Add Continent object to Map
void Map::addContinent(Continent* continentName)
{
	continents[continentName->getName()] = continentName;
};

// Returns a vector of all the countries
vector<Country*> Map::getCountries() {
	
	vector<Country*> temp;

	for (map<string, Country*>::iterator i = countries.begin(); i != countries.end(); i++) {
		temp.push_back(i->second);
	}

	return temp;
}

// Returns a vector of all the continents
vector<Continent*> Map::getContinents() {
	
	vector<Continent*> temp;

	for (std::map<string, Continent*>::iterator i = continents.begin(); i != continents.end(); i++) {
		temp.push_back(i->second);
	}

	return temp;
}

// Returns a Country object of a specific name
Country* Map::getCountry(string countryName)
{
		return countries[countryName];
}

// Returns a Continent object of a specific name
Continent* Map::getContinent(string continentName) 
{
	return continents[continentName];
}

// Returns a vector of the Countries of a specific continent
vector<Country*>  Map::getCountriesByContinent(string continentName)
{
	vector<Country*> tempCountries;

	for (std::map<string, Country*>::iterator i = countries.begin(); i != countries.end(); i++) {
	
		if (i->second->getContinentName() == continentName) {
			tempCountries.push_back(i->second);
		}
	}
	return tempCountries;
}

// Validates the Map
bool Map::toValidate()
{

	// Use BFS on the first node to verify that all countries are connected
	vector<Country*> allCountries = getCountries();

	// Verifying that every if country can reach all eachother
	if (allCountries.size() == 0) {
		return false;
	}
		
	for (int i = 0; i < allCountries.size(); i++)
	{
		string temp1 = allCountries[i]->getName();
		
		for (int j = 0; j < allCountries.size(); j++) {
			
			string temp2 = allCountries[j]->getName();
			
			if (!reachable(temp1, temp2)) {
				
				cout << "This is not a connected graph." << endl;
				
				return false;
			}
		}
	}

	std::cout << "This is a connected graph." << std::endl;

	// Check if continents are connected subgraphs
	// by verifying all continents contain at least one country
	// checking if continent contains a country and all country are connected
	
	for (map<string, Continent*>::iterator i = continents.begin(); i != continents.end(); i++) {
		
		if (i->second->numberOfCountry() == 0) {
			cout << "Continents are not connected subgraphs." << endl;
			return false;
		}

	}

	std::cout << "Continents are connected subgraphs." << std::endl;

	// verify all countries should belong to at least one continent
	for (int i = 0; i < getCountries().size(); i++)
	{
		if (getCountries()[i]->getContinentName() == "") {
			return false;
		}
	}

	// check each country belongs to only one continent
	for (int i = 0; i < allCountries.size(); i++)
	{
		string temp = allCountries[i]->getName();
		string tempContinent = allCountries[i]->getContinentName();

		
		for (map<string, Continent*>::iterator j = continents.begin(); j != continents.end(); j++) {

			if (j->second->checkForCountry(temp) && (tempContinent != j->first)) {
				cout << "There exists a country that does not belong to any continent." << endl;
				return false;
			}
		}
	}

	cout << "Each country belongs to one and only one continent." << endl;

	return true;
}

// Check if a initial country can reach a destinatation country
bool Map::reachable(string initial, string destination)
{

	if (initial == destination){
		return true;
	}

	// Keep track of visited
	map<string, bool> visited;

	//initialize them all to false
	map<string, Country*>::iterator start = countries.begin();
	
	for (start; start != countries.end(); ++start)
	{
		pair<string, bool> flag(start->first, false);
		visited.insert(flag);
	}

	//Create a queue and mark the initial country as visited
	list<string> queue;
	visited[initial] = true;
	queue.push_back(initial);

	while (!queue.empty())
	{
		string name = queue.front();
		queue.pop_front();

		for (auto& i : getCountry(name)->getNeighbors()) {
			
			if (i->getName() == destination) {
				return true;
			}

			if (!visited[i->getName()]){
				visited[i->getName()] = true;
				queue.push_back(i->getName());
			}	
		}
	}

	return false;

}



