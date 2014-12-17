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

	typedef codecvt_utf8<wchar_t> convert_typeX;
	wstring_convert<convert_typeX, wchar_t> converterX;
	wstring str1 = converterX.from_bytes(user);
	wchar_t* username = const_cast<wchar_t*>(str1.c_str());
	wstring str2 = converterX.from_bytes(pass);
	wchar_t*  password = const_cast<wchar_t*>(str2.c_str());
	
	WCHAR* idResult;
	/*wchar_t myuser[100] = L"admin";
	wchar_t mypass[100] = L"Admin_123";*/
	
	hr = BasicHttpBinding_IService_Login(
		proxy, username, password, &idResult, heap, NULL, 0, NULL, error);
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
			cout << "Invalid username or password, please try again !! \n" << endl;
		}
	}
	return false;
}