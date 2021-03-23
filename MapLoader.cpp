#include "MapLoader.h"


//default constructor
MapLoader::MapLoader() 
{
	
}

//destructor
MapLoader::~MapLoader() {


}

//copy constructor
MapLoader::MapLoader(const MapLoader& copy) {
	fileName = copy.fileName;
}

//assignment operator
MapLoader& MapLoader::operator=(const MapLoader& copy) {
	this->fileName = copy.fileName;
	return *this;
}

//stream insertion operator
ostream& operator<<(ostream& os, const MapLoader& copy) {
	
	os << "path: " << copy.fileName << endl;
	return os;
	
}

//stream extraction operator
istream& operator>>(istream& is, MapLoader& copy) {
	cout << "Enter new file path: " << endl;
	is >> copy.fileName;
	return is;
}

string MapLoader::getFileName(){
	return fileName;
}

Map* MapLoader::loadMap(string path) {

	Map* map = new Map();	

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

	return map;

}

// Displays all the available maps
vector<string> MapLoader::displayAllMaps(const string mapDirectory) {

	vector<string> mapFiles;
	DIR* directory;
	struct dirent* file;

	cout << endl << "---DISPLAYING ALL AVAILABLE MAPS---" << endl;

	// Code for iterating through directories, works for Unix Operating Systems
	if ((directory = opendir(mapDirectory.c_str())) == NULL) {
		cout << "Could not open directory of maps, exiting." << endl << endl;
		exit(1);
	}
	else {
		int counter = 1;
		cout << "Select a map: " << endl << endl;
		while ((file = readdir(directory)) != NULL) {
			struct stat pathStat;
			stat((mapDirectory + file->d_name).c_str(), &pathStat);
			int is_dir = S_ISDIR(pathStat.st_mode);
			if (!is_dir) {
				cout << counter++ << ": " << file->d_name << endl;
				mapFiles.push_back(file->d_name);
			}
		}
	}
	closedir(directory);
	return mapFiles;
}

Map* MapLoader::selectMap(const string mapDirectory) {

	bool badMap = true;
	Map* theMap;
	
	do
	{	
		theMap = new Map();

		cout << endl << "---CHOOSING MAP---" << endl << endl;
		vector<string> mapFiles = displayAllMaps(mapDirectory);

		int mapNumber = getUserInputInteger("\nYour choice (-1 to quit): ", 1, mapFiles.size());

		string fileSelected =  mapDirectory + mapFiles[mapNumber - 1];
		cout<<"file name :"<< fileSelected<<endl;
		fileName = fileSelected;
		
		cout << endl << "The map you chose is: " << fileSelected << endl;

		
			if (fileSelected.substr(fileSelected.length() - 4, fileSelected.length() - 1) != ".txt")
			{
				cout << endl << "File is not of type .txt" << endl;
				fileSelected.clear();
			}
			else
			{					
				theMap = loadMap(fileSelected);
				
				if (theMap->validate()) {
					cout << "New Game has been started! \n";
					cout << "This gamemap is valid! \n";
					badMap = false;
				}
				else
				{
					cout << "Game map is invalid. It has been deleted. Try again with a valid map file\n";
				}
			}
	}
	while(badMap);
	cout<<"end of select map........."<<endl;
	return theMap;
}

// Helper function for getting user string input
string MapLoader::getUserInputString(string output, string choice1, string choice2) {

	string input;

	cout << output;
	cin >> input;

	// While the input is invalid
	while ((input != choice1 && input != choice2) || cin.fail() || input == "q" || input == "Q") {
		if (input == "q" || input == "Q") {
			cout << "Quitting..." << endl;
			exit(1);
		}

		// Clear the stream
		cin.clear();
		cout << "Invalid input" << endl;
		cout << "Must be " << choice1 << " or " << choice2 << " and must be a string" << endl;
		cout << "Try again ('q' to quit): ";
		cin >> input;
	}

	return input;
}

// Helper function for getting user integer input
int MapLoader::getUserInputInteger(string output, int min, int max) {
	string inputString;
	int input;
	bool failFlag;

	cout << output;
	cin >> inputString;

	try {
		input = stoi(inputString);
		failFlag = false;
	}
	catch (invalid_argument e) {
		failFlag = true;
	}

	// While the input is invalid
	while (input < min || input > max || cin.fail() || failFlag || inputString.find(".") != string::npos) {
		if (input == -1) {
			cout << "Quitting..." << endl;
			exit(1);
		}

		cin.clear();
		//cin.ignore(numeric_limits<streamsize> std::max, '\n');
		cout << "Invalid input" << endl;

		if (inputString.find(".") == string::npos) {
			cout << "Must be greater than " << min - 1 << " and less than " << max + 1 << " and must be an integer" << endl;
		}
		else {
			cout << "Must be an integer" << endl;
		}
		cout << "Try again (-1 to quit): ";
		cin >> inputString;

		try {
			input = stoi(inputString);
			failFlag = false;
		}
		catch (invalid_argument e) {
			failFlag = true;
		}
	}

	return input;
}
