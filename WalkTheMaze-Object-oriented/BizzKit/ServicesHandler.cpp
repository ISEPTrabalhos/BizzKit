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
	/*wchar_t myuser[100] = L"admin";
	wchar_t mypass[100] = L"Admin_123";*/
	typedef codecvt_utf8<wchar_t> convert_typeX;
	wstring_convert<convert_typeX, wchar_t> converterX;
	wstring str1 = converterX.from_bytes(user);
	wchar_t* username = const_cast<wchar_t*>(str1.c_str());
	wstring str2 = converterX.from_bytes(pass);
	wchar_t*  password = const_cast<wchar_t*>(str2.c_str());
	WCHAR* idResult;
	hr = BasicHttpBinding_IService_Login(
		proxy, username, password, &idResult, heap, NULL, 0, NULL, error);
	//wprintf(L"%s\n", idResult);

	return _wtoi(idResult);
}

vector<string> ServicesHandler::getMapsList() {
	vector<string> maps;
	/* it will be something like this, METHODS NOT READY YET
	Maps m;
	hr = BasicHttpBinding_IService_AllMaps(
		proxy, &m, heap, NULL, 0, NULL, error);
	maps.push_back(m->name); // do this for all maps received
	*/
	maps.push_back("Map Name 1");
	maps.push_back("Map Name 2");
	maps.push_back("Map Name 3");
	
	return maps;
}

int ServicesHandler::score(string user, string level, int score)
{
	typedef codecvt_utf8<wchar_t>convert_typeX;
	wstring_convert<convert_typeX, wchar_t>convertUsername;
	wstring string1 = convertUsername.from_bytes(user);
	wchar_t* username = const_cast<wchar_t*>(string1.c_str());
	int *result;
	hr = BasicHttpBinding_IService_Score(proxy, username, score, result, heap, NULL, 0, NULL, error);
	return *result;
}