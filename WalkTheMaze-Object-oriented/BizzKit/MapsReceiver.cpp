#include "MapsReceiver.h"
#include "ServicesHandler.h"

vector<string> MapsReceiver::getAllMaps() {
	ServicesHandler *service = new ServicesHandler();
	return service->getMapsList();
}

string MapsReceiver::getMapByName(string name) {
	ServicesHandler *service = new ServicesHandler();
	return  service->getSingleMap(name);
}

