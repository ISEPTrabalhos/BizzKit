#include "ServicesHandler.h"

ServicesHandler::ServicesHandler(){
	hr = ERROR_SUCCESS;
	error = NULL;
	heap = NULL;
	proxy = NULL;
	address = {};
	templ = {};
	// endereço do serviço
	url = WS_STRING_VALUE(L"http://localhost:43492/Services/Service.svc?wsdl");
	//http://wvm041.dei.isep.ipp.pt/Lapr5/Services/Service.svc
	address.url = url;
	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);

	// criação do proxy para o serviço
	hr = BasicHttpBinding_IService_CreateServiceProxy(
		&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);
}

ServicesHandler::~ServicesHandler(){}

int ServicesHandler::signIn(string user, string pass) {
	/*wchar_t myuser[100] = L"admin";
	wchar_t mypass[100] = L"Admin_123";*/
	typedef codecvt_utf8<wchar_t> convert_typeX;
	wstring_convert<convert_typeX, wchar_t> converterX;
	wstring str1 = converterX.from_bytes(user);
	wchar_t* username = const_cast<wchar_t*>(str1.c_str());
	wstring str2 = converterX.from_bytes(pass);
	wchar_t*  password = const_cast<wchar_t*>(str2.c_str());
	//WCHAR* idResult;
	int id;
	hr = BasicHttpBinding_IService_Login(
		proxy, username, password, &id, heap, NULL, 0, NULL, error);
	//wprintf(L"%s\n", idResult);

	//return _wtoi(idResult);
	return id;
}

vector<string> ServicesHandler::getMapsList() {
	// receive map list 
	WCHAR* results;
	// disabled because method doesnt exist on deployed version yet, only locally
	hr = BasicHttpBinding_IService_ListLevels(proxy, &results, heap, NULL, 0, NULL, error); 

	//wprintf(L"%s\n", results);

	// convert wchar_t to string
	typedef codecvt_utf8<wchar_t> convert_typeX;
	wstring_convert<convert_typeX, wchar_t> converterX;
	wstring wstr = results;
	string resultsMaps = converterX.to_bytes(wstr);
	// split string into vector
	vector<string> maps;
	stringstream ss(resultsMaps);
	string item;
	while (getline(ss, item, ',')) {
		maps.push_back(item);
	}

	return maps;
}

string ServicesHandler::getSingleMap(string lvl) {
	//convert string into wchar
	typedef codecvt_utf8<wchar_t> convert_typeX;
	wstring_convert<convert_typeX, wchar_t> converterX;
	string name = lvl;
	wstring strLvl = converterX.from_bytes(lvl);
	wchar_t* levelName = const_cast<wchar_t*>(strLvl.c_str());

	// receive map
	wchar_t* level;
	// disabled because method doesnt exist on deployed version yet, only locally
	hr = BasicHttpBinding_IService_LoadLevel(proxy, levelName, &level, heap, NULL, 0, NULL, error);
	//wprintf(L"%s\n", level);

	// save on file
	wstring wstr = level;
	string newLevel = converterX.to_bytes(wstr);
	//ofstream newFile;
	//string filename = lvl + ".grafo";
	//newFile.open(filename);
	////newFile << newLevel;
	//newFile.close();

	return newLevel;
}

int ServicesHandler::score(string user, string level, int score)
{
	typedef codecvt_utf8<wchar_t>convert_typeX;
	wstring_convert<convert_typeX, wchar_t>convertUsername;
	wstring string1 = convertUsername.from_bytes(user);
	wchar_t* username = const_cast<wchar_t*>(string1.c_str());
	int *result;
	//hr = BasicHttpBinding_IService_Score(proxy, username, score, result, heap, NULL, 0, NULL, error);
	//return *result;
	return 0;
}