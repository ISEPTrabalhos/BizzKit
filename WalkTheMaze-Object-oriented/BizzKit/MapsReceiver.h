#ifndef _MAPSRECEIVER
#define _MAPSRECEIVER

#include "GlobalVars.h"
using namespace std;

class MapsReceiver {
public:

	// functions
	static vector<string> getAllMaps();
	static void getMapByName(string name);
	static string showChooseMapMenu();
	static string chooseMap();
};

#endif