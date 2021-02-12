
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

#include "Map.h"

using namespace std;



int main(int argc, const char* argv[]) {
  
  

    // We create 5 countries in 2 continents and add them to the Map
  

    Continent*centralAmerica = new Continent("Central America");
    Continent*southAmerica = new Continent("South America");
    Continent* europe = new Continent("Europe");

    Country* nicaragua = new Country("Nicaragua", "Central America");
    centralAmerica->addCountrytoContinent(nicaragua);

    Country* costaRica = new Country("Costa Rica", "Central America");
    centralAmerica->addCountrytoContinent(costaRica);

    Country* panama = new Country("Panama", "Central America");
    centralAmerica->addCountrytoContinent(panama);

    Country* colombia = new Country("Colombia", "South America");
    southAmerica->addCountrytoContinent(colombia);

    Country* venezuela = new Country("Venezuela", "South America");
    southAmerica->addCountrytoContinent(venezuela);

    Country* brazil = new Country("Brazil", "South America");
    southAmerica->addCountrytoContinent(brazil);

    Country* france = new Country("France", "Europe");
    europe->addCountrytoContinent(france);


    Map gameMap;

    gameMap.addContinent(centralAmerica);
    gameMap.addContinent(southAmerica);


    vector<Country*> nicNeighbors;
    nicNeighbors.push_back(costaRica);
    nicaragua->setNeighbors(nicNeighbors);
    gameMap.addCountry(nicaragua);


    vector<Country*> costaNeighbors;
    costaNeighbors.push_back(nicaragua);
    costaNeighbors.push_back(panama);
    costaRica->setNeighbors(costaNeighbors);
    gameMap.addCountry(costaRica);

    vector<Country*> panamaNeighbors;
    panamaNeighbors.push_back(costaRica);
    panamaNeighbors.push_back(colombia);
    panama->setNeighbors(panamaNeighbors);
    gameMap.addCountry(panama);

    vector<Country*> colNeighbors;
    colNeighbors.push_back(panama);
    colNeighbors.push_back(venezuela);
    colombia->setNeighbors(colNeighbors);
    gameMap.addCountry(colombia);


    vector<Country*> venNeighbors;
    venNeighbors.push_back(colombia);
    venezuela->setNeighbors(venNeighbors);
    gameMap.addCountry(venezuela);



    cout << "---------- TESTING MAP -----------" << endl << endl;

    cout << "---------- Created Map -----------" << endl;

    cout << "Created " << gameMap.countryCount() << " countries" << endl;
    cout << "Created " << gameMap.continentCount() << " continent" << endl << endl;

    vector<Country*> countrylist = gameMap.getCountries();
    vector<Continent*> continentlist = gameMap.getContinents();


    for (auto& temp : continentlist) {

        cout << "Continent Name: " << temp->getName();

        for (auto& temp2 : temp->getContinentCountries()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

        cout << endl;

    for (auto& temp : countrylist) {

        cout << "Country Name: " << temp->getName();

        for (auto& temp2 : temp->getNeighbors()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout  << endl;

    if (gameMap.toValidate() == true) {
        cout << "The Map is valid" << endl;
    }
    else {
        cout << "The Map is not valid" << endl;
    }

    cout << endl << endl;

  
    cout << "---------- Created Map -----------" << endl;
    cout << "Adding 1 unconnected country..." << endl << endl;

    vector<Country*> braNeighbors;
    braNeighbors.push_back(colombia);
    brazil->setNeighbors(braNeighbors);

    gameMap.addCountry(brazil);

    cout << "Created " << gameMap.countryCount() << " countries" << endl;
    cout << "Created " << gameMap.continentCount() << " continent" << endl << endl;


    for (auto& temp : continentlist) {

        cout << "Continent Name: " << temp->getName();

        for (auto& temp2 : temp->getContinentCountries()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    for (auto& temp : countrylist) {

        cout << "Country Name: " << temp->getName();

        for (auto& temp2 : temp->getNeighbors()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    if (gameMap.toValidate() == true) {
        cout << "The Map is valid" << endl;
    }
    else {
        cout << "The Map is not valid" << endl;
    }

    cout << endl << endl;


    cout << "---------- Created Map -----------" << endl;
    cout << "Adding neighbor to make map connected..." << endl << endl;

   colombia->addNeighbor(brazil);

    cout << "Created " << gameMap.countryCount() << " countries" << endl;
    cout << "Created " << gameMap.continentCount() << " continent" << endl << endl;

    countrylist = gameMap.getCountries();

    for (auto& temp : continentlist) {

        cout << "Continent Name: " << temp->getName();

        for (auto& temp2 : temp->getContinentCountries()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    for (auto& temp : countrylist) {

        cout << "Country Name: " << temp->getName();

        for (auto& temp2 : temp->getNeighbors()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    if (gameMap.toValidate() == true) {
        cout << "The Map is valid" << endl;
    }
    else {
        cout << "The Map is not valid" << endl;
    }

    cout << endl << endl;


    cout << "---------- Created Map -----------" << endl;
    cout << "Adding 1 unconnected country..." << endl << endl;

    gameMap.addContinent(europe);
    gameMap.addCountry(france);


    cout << "Created " << gameMap.countryCount() << " countries" << endl;
    cout << "Created " << gameMap.continentCount() << " continent" << endl << endl;

    countrylist = gameMap.getCountries();


    for (auto& temp : continentlist) {

        cout << "Continent Name: " << temp->getName();

        for (auto& temp2 : temp->getContinentCountries()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    for (auto& temp : countrylist) {

        cout << "Country Name: " << temp->getName();

        for (auto& temp2 : temp->getNeighbors()) {

            cout << "---> " << temp2->getName();
        }

        cout << endl;
    }

    cout << endl;

    if (gameMap.toValidate() == true) {
        cout << "The Map is valid" << endl;
    }
    else {
        cout << "The Map is not valid" << endl;
    }

    cout << endl << endl;


    cout << "---------- FINISH TESTING MAP -----------" << endl << endl;

    return 0;
}