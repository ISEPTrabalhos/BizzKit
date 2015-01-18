#include "ServicesHandler.h"
#include "Status.h"
#include<windows.h>
#include <tchar.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")

extern Status *status;

ServicesHandler::ServicesHandler(){
	hr = ERROR_SUCCESS;
	error = NULL;
	heap = NULL;
	proxy = NULL;
	address = {};
	templ = {};
	// endereço do serviço
	url = WS_STRING_VALUE(L"http://wvm041.dei.isep.ipp.pt/Lapr5/Services/Service.svc");
	address.url = url;
	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);

	// criação do proxy para o serviço
	hr = BasicHttpBinding_IService_CreateServiceProxy(
		&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);
}

ServicesHandler::~ServicesHandler(){}

int ServicesHandler::signIn(string user, string pass) {
	wstring u = convertStringToWstring(user);
	wstring p = convertStringToWstring(pass);
	wchar_t*  username = const_cast<wchar_t*>(u.c_str()); 
	wchar_t*  password = const_cast<wchar_t*>(p.c_str());
	//WCHAR* idResult;
	int id;
	hr = BasicHttpBinding_IService_Login(
		proxy, username, password, &id, heap, NULL, 0, NULL, error);
	//wprintf(L"%s\n", idResult);

	return id;
}

vector<string> ServicesHandler::getMapsList() {
	// receive map list 
	WCHAR* results;
	hr = BasicHttpBinding_IService_ListLevels(proxy, &results, heap, NULL, 0, NULL, error); 

	//wprintf(L"%s\n", results);

	string resultsMaps = convertWcharToString(results);
	// split string into vector
	vector<string> maps;
	stringstream ss(resultsMaps);
	string item;
	while (getline(ss, item, ',')) {
		maps.push_back(item);
	}

	return maps;
}

void ServicesHandler::saveSingleMap(string lvl) {
	//convert string into wchar
	string l = lvl.substr(0, lvl.find("."));
	wstring strLvl = convertStringToWstring(l);
	wchar_t* levelName = const_cast<wchar_t*>(strLvl.c_str());

	// receive map
	wchar_t* level;
	hr = BasicHttpBinding_IService_LoadLevel(proxy, levelName, &level, heap, NULL, 0, NULL, error);
	//wprintf(L"%s\n", level);

	// save on file
	//wstring wstr = level;
	string newLevel = convertWcharToString(level);

	ofstream newFile;
	//string filename = lvl + ".grafo";
	newFile.open(lvl);
	newFile << newLevel;
	newFile.close();
}

void ServicesHandler::uploadScore(int score)
{
	wstring string1 = convertStringToWstring(status->username);
	wchar_t* username = const_cast<wchar_t*>(string1.c_str());

	string lvlName = status->mapfile.substr(0, status->mapfile.find("."));
	wstring string2 = convertStringToWstring(lvlName);
	wchar_t* levelName = const_cast<wchar_t*>(string2.c_str());

	hr = BasicHttpBinding_IService_Score(proxy, username, levelName, score, heap, NULL, 0, NULL, error);
}

wstring ServicesHandler::convertStringToWstring(string source) {
	//convert string into wstring
	typedef codecvt_utf8<wchar_t> convert_typeX;
	wstring_convert<convert_typeX, wchar_t> converterX;
	return converterX.from_bytes(source);
}

string ServicesHandler::convertWcharToString(wchar_t* src) {
	//convert wchar to string
	typedef codecvt_utf8<wchar_t> convert_typeX;
	wstring_convert<convert_typeX, wchar_t> converterX;
	wstring wstr = src;
	return converterX.to_bytes(wstr);
}

void ServicesHandler::uploadRoute(string route)
{
	wstring string1 = convertStringToWstring(status->username);
	wchar_t *username = const_cast<wchar_t*>(string1.c_str());

	string levelName = status->mapfile.substr(0, status->mapfile.find("."));
	wstring string2 = convertStringToWstring(levelName);
	wchar_t *level = const_cast<wchar_t*>(string2.c_str());

	wstring string3 = convertStringToWstring(route);
	wchar_t *gameRoute = const_cast<wchar_t*>(string3.c_str());

	hr = BasicHttpBinding_IService_uploadRoute(proxy, username, level, gameRoute, heap, NULL, 0, NULL, error);
}

vector<string> ServicesHandler::getSoundsList() {
	// receive sounds list 
	WCHAR* results = NULL;;
	hr = BasicHttpBinding_IService_getSoundsList(proxy, &results, heap, NULL, 0, NULL, error);

	string resultsSounds = convertWcharToString(results);
	// split string into vector
	vector<string> sounds;
	stringstream ss(resultsSounds);
	string item;
	while (getline(ss, item, ',')) {
		sounds.push_back(item);
	}

	return sounds;
}

void ServicesHandler::saveSound(string name) {

	cout << name << endl;
	//convert string into wchar
	wstring strName = convertStringToWstring(name);
	wchar_t* soundName = const_cast<wchar_t*>(strName.c_str());

	wchar_t* result = NULL;;
	hr = BasicHttpBinding_IService_downloadSound(proxy, soundName, &result, heap, NULL, 0, NULL, error);

	string url = convertWcharToString(result);
	cout << url << endl;
	string type = name.substr(name.find("_") + 1, name.size());
	string filename = type + ".wav";

	saveFile(url, filename);

}

vector<string> ServicesHandler::getTexturesList() {
	//receive textures list
	WCHAR* results = NULL;;
	hr = BasicHttpBinding_IService_getTexturesList(proxy, &results, heap, NULL, 0, NULL, error);

	string resultsTextures = convertWcharToString(results);
	// split string into vector
	vector<string> textures;
	stringstream ss(resultsTextures);
	string item;
	while (getline(ss, item, ',')) {
		textures.push_back(item);
	}

	return textures;
}

void ServicesHandler::saveTexture(string name) {

	cout << name << endl;
	//convert string into wchar
	wstring strName = convertStringToWstring(name);
	wchar_t* textureName = const_cast<wchar_t*>(strName.c_str());

	wchar_t* result = NULL;
	hr = BasicHttpBinding_IService_downloadTexture(proxy, textureName, &result, heap, NULL, 0, NULL, error);

	string url = convertWcharToString(result);
	cout << url << endl;
	string filename;
	if (name.find("Floor") != std::string::npos) {
		filename = "floor.jpg";
	}
	else {
		filename = "wall.jpg";
	}

	saveFile(url, filename);

}

void ServicesHandler::saveFile(string url, string path) {
	HRESULT hr;
	LPCTSTR Url = _T(url.c_str()), File = _T(path.c_str());
	hr = URLDownloadToFile(0, Url, File, 0, 0);
}

vector<string> ServicesHandler::getEnemiesModels()
{
	WCHAR *models=NULL;
	hr = BasicHttpBinding_IService_getEnemiesModelsList(proxy, &models, heap, NULL, 0, NULL, error);

	string results = convertWcharToString(models);

	vector<string>enemies;
	stringstream ss(results);
	string item;
	while (getline(ss, item,','))
	{
		enemies.push_back(item);
	}
	return enemies;
}

void ServicesHandler::saveModels(string modelName)
{
	wstring name = convertStringToWstring(modelName);
	wchar_t *model = const_cast<wchar_t*>(name.c_str());

	wchar_t *result = NULL;
	hr = BasicHttpBinding_IService_downloadEnemiesModels(proxy, model, &result, heap, NULL, 0, NULL, error);

	string url = convertWcharToString(result);
	string filename;
	if (modelName.find("Mummy") != std::string::npos)
	{
		filename = "mummy.mdl";
	}
	else{
		filename = "SpitterL4D2v1.mdl";
	}

	saveFile(url, filename);
}