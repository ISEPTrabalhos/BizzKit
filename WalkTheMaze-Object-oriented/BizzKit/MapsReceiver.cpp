#include "MapsReceiver.h"
#include "ServicesHandler.h"

vector<string> MapsReceiver::getAllMaps() {
	ServicesHandler *service = new ServicesHandler();
	vector<string> maps;
	maps = service->getMapsList();
	return maps;
}


string MapsReceiver::getMapById(int id) {
	return "MAP";
}
