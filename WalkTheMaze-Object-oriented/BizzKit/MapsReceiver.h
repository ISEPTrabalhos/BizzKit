#ifndef _MAPSRECEIVER
#define _MAPSRECEIVER

#include <stdlib.h>
#include <string>
#include <iostream>
#include "stdafx.h"
#include "WebServices.h"
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h"
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"
#include <vector>

using namespace std;

class MapsReceiver {
public:

	// functions
	static vector<string> getAllMaps();
	static string getMapById(int id);
};

#endif