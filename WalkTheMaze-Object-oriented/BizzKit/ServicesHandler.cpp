#include "ServicesHandler.h"

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

	//return _wtoi(idResult);

	//int x = ServicesHandler::score("admin", "quarto1", 10);
	//cout << "--> " << x << endl;
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
	wstring strLvl = convertStringToWstring(lvl);
	wchar_t* levelName = const_cast<wchar_t*>(strLvl.c_str());

	// receive map
	wchar_t* level;
	hr = BasicHttpBinding_IService_LoadLevel(proxy, levelName, &level, heap, NULL, 0, NULL, error);
	//wprintf(L"%s\n", level);

	// save on file
	//wstring wstr = level;
	string newLevel = convertWcharToString(level);
	// there is a NEW BUG on receving the maps, dont know why , ISSUE 47
	// dont save file because of the bug
	/*ofstream newFile; 
	string filename = lvl + ".grafo";
	newFile.open(filename);
	newFile << newLevel;
	newFile.close();*/
}

int ServicesHandler::score(string user, string level, int score)
{
	wstring string1 = convertStringToWstring(user);
	wchar_t* username = const_cast<wchar_t*>(string1.c_str());

	wstring string2 = convertStringToWstring(level);
	wchar_t* levelName = const_cast<wchar_t*>(string2.c_str());

	//upload score
	int *result = 0;
	hr = BasicHttpBinding_IService_Score(proxy, username,levelName, score, result, heap, NULL, 0, NULL, error);
	return *result;
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