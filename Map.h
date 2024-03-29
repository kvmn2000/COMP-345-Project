#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <map>
#include<iostream>

using namespace std;

class Player;

class Country {


public:

	Country() = default;
	Country(string country_Name);
	Country(string country_Name, string continent_Name);
	Country(string country_Name, string continent_Name, vector<Country*> neighbor_countries, int playerArmie);
	Country(const Country& copy);
	~Country();

	Country& operator=(const Country& copy);
	bool operator==(const Country& copy);
	friend ostream& operator << (ostream& out, const Country& copy);
	friend istream& operator >> (istream& in, Country& copy);

	string getName();
	string getContinentName();
	void setOwner(Player* countryOwner);
	Player* getOwner();
	void setArmy(int amount);
	int getArmy();

	bool hasNeighbors();
	void addNeighbor(Country* country);
	void setNeighbors(vector<Country*> country_neighbor);
	int getNeighborAmount();
	vector<Country*> getNeighbors();
	vector<string> getNeighborsName();
	int isAdjacent(Country* from);

private:
	string name;
	string continentName;
	Player* owner;
	int armie;
	vector<Country*> neighbors;
};


class Continent {


public:

	Continent() = default;
	Continent(string continent_name);
	Continent(string continent_name, vector<Country*> continent_countries);
	Continent(const  Continent& copy);
	~Continent();

	Continent& operator=(const  Continent& copy);
	friend ostream& operator << (ostream& out, const Continent& copy);
	friend istream& operator >> (istream& in, Continent& copy);

	string getName();
	vector<Country*> getContinentCountries();
	void addCountrytoContinent(Country* country);
	int numberOfCountry();
	bool checkForCountry(string countryName);


private:
	string name;
	vector<Country*> continentCountries;
};


class Map {


public:

	Map() = default;
	Map(const Map& copy);
	~Map();

	Map& operator=(const Map& copy);
	friend ostream& operator << (ostream& out, const Map& copy);

	int countryCount();
	int continentCount();
	void addCountry(Country* country_Name);
	void addContinent(Continent* continent_Name);
	Country* getCountry(string countryName);
	Continent* getContinent(string continentName);
	vector<Country*> getCountries();
	vector<Continent*> getContinents();
	vector<Country*> getCountriesByContinent(string continentName);
	bool validate();
	Country* startingRegion;
	Country* findCountry(string country_name);

private:
	map<string, Country*> countries;
	map<string, Continent*> continents;
	bool toGetTo(string source, string destination);
};