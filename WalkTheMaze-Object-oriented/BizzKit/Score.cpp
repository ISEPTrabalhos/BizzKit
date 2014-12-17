#include "Score.h"

int Score::uploadScore(string username, int score)
{
	HRESULT hr = ERROR_SUCCESS;
	WS_ERROR *error = NULL;
	WS_HEAP *heap = NULL;
	WS_SERVICE_PROXY *proxy = NULL;
	WS_ENDPOINT_ADDRESS address = {};

	//service address
	WS_STRING url = WS_STRING_VALUE(L"http://wvm041.dei.isep.ipp.pt/Lapr5/Services/Service.svc");
	address.url = url;

	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};

	//proxy creation
	hr = BasicHttpBinding_IService_CreateServiceProxy(&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);

	WCHAR *result;
	WCHAR user = L'username';
	WCHAR points = L'score';
	//hr = BasicHttpBinding_IService_Score(proxy, &username, &score, &result, heap, NULL, 0, NULL, error);
	return 1;

}