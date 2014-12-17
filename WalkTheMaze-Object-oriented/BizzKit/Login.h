#ifndef _LOGIN
#define _LOGIN

#include <stdlib.h>
#include <string>
#include <iostream>
#include "stdafx.h"
#include "WebServices.h"
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h"
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"
//#include "schema.xsd.h"

using namespace std;

class Login {
public:

	// functions
	static int LoginUser(string username, string password);
	static bool ShowSignInMenu();
};

#endif