#include "Login.h"

int Login::LoginUser(string user, string pass) {
	HRESULT hr = ERROR_SUCCESS;
	WS_ERROR* error = NULL;
	WS_HEAP* heap = NULL;
	WS_SERVICE_PROXY* proxy = NULL;
	WS_ENDPOINT_ADDRESS address = {};
	// endereço do serviço
	WS_STRING url = WS_STRING_VALUE(
		L"http://wvm041.dei.isep.ipp.pt/Lapr5/Services/Service.svc");
	address.url = url;
	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};

	// criação do proxy para o serviço
	hr = BasicHttpBinding_IService_CreateServiceProxy(
		&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);

	WCHAR* idResult;
	WCHAR username = L'username';
	WCHAR password = L'password';
	hr = BasicHttpBinding_IService_Login(
		proxy, &username, &password, &idResult, heap, NULL, 0, NULL, error);
	//wprintf(L"%s\n", idResult);

	int id = _wtoi(idResult);

	return id;

}


bool Login::ShowSignInMenu() {
	string username = "", password = "";
	bool valid = false;
	cout << "******* SIGN IN *******\n";
	while (valid == false) {
		cout << "Username: ";
		getline(cin, username);
		cout << "Password: ";
		getline(cin, password);
		cout << "Username: " << username << " Password: " << password;
		cout << "\n" << endl;

		int id = LoginUser(username, password);

		if (id > 0) { // valid user
			valid = true;
			cout << "\n ** You're now logged in !! **\n" << endl;
			return true;
		}
		else {
			cout << "Invalid user, please try again !! \n" << endl;
		}
	}
	return false;
}