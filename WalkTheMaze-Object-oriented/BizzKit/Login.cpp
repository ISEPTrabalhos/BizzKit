#include "Login.h"
#include "ServicesHandler.h"

int Login::LoginUser(string username, string password) {
	ServicesHandler *service = new ServicesHandler();
	int id = service->signIn(username, password);
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