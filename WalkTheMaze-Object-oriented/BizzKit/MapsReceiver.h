#ifndef _MAPSRECEIVER
#define _MAPSRECEIVER

#include "GlobalVars.h"
using namespace std;

class MapsReceiver {
public:

	// functions
	static vector<string> getAllMaps();
	static string getMapById(int id);
};

#endif