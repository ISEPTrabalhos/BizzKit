#ifndef _SERVICESHANDLER
#define _SERVICESHANDLER

#include "GlobalVars.h"
#include "stdafx.h"
#include "WebServices.h"
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h"
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"
//#include "schema.xsd.h"
#include <atlconv.h>
#include <locale>
#include <codecvt>

using namespace std;

class ServicesHandler {
public:
	
	// variables
	HRESULT hr = ERROR_SUCCESS;
	WS_ERROR* error = NULL;
	WS_HEAP* heap = NULL;
	WS_SERVICE_PROXY* proxy = NULL;
	WS_ENDPOINT_ADDRESS address = {};
	WS_HTTP_BINDING_TEMPLATE templ;
	// endere�o do servi�o
	WS_STRING url;

	// functions
	ServicesHandler();
	~ServicesHandler();

	int signIn(string user, string pass);
	vector<string> getMapsList();
	void saveSingleMap(string lvl);
	void uploadScore(int score);
	void uploadRoute(string route);
	vector<string> getSoundsList();
	void saveSound(string soundName);
	vector<string> getTexturesList();
	void saveTexture(string textureName);
	void saveFile(string url, string path);
	vector<string>getEnemiesModels();
	void saveModels(string modelName);

	//usefull functions
	wstring convertStringToWstring(string source);
	string convertWcharToString(wchar_t* source);
};

#endif