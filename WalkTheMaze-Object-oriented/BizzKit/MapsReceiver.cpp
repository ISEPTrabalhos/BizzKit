#include "MapsReceiver.h"
#include "ServicesHandler.h"

vector<string> MapsReceiver::getAllMaps() {
	ServicesHandler *service = new ServicesHandler();
	return service->getMapsList();
}

void MapsReceiver::getMapByName(string name) {
	ServicesHandler *service = new ServicesHandler();
	service->saveSingleMap(name);
}

string MapsReceiver::showChooseMapMenu() {
	// get map list
	vector<string> maps = getAllMaps();
	string mapName = "";
	// show simple menu
	cout << "******* Choose the map *******\n\n";
	bool valid = false;
	while (valid == false) {
		for (int i = 0; i < maps.size(); i++) {
			cout << (i + 1) << " - " << maps.at(i) << endl;
		}
		// read option
		string input;
		int option;
		cout << "\nChoose a map to load: ";
		cin >> input;
		option = atoi(input.c_str());
		if (option > 0 && option <= maps.size()) {
			valid = true;
			mapName = maps.at(option-1);
		}
		else {
			cout << "\nInvalid option, please try again !! \n" << endl;
		}
	}
	return mapName;
}

string MapsReceiver::chooseMap() {
	string mapName = showChooseMapMenu();
	getMapByName(mapName);
	return mapName;
}