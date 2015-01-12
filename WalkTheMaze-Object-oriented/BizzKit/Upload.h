#ifndef Upload_
#define Upload_

#include <stdlib.h>
#include <string>
#include <iostream>
#include "WebServices.h"
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h"
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"

using namespace std;

class Upload{

public:
	static int uploadProgress(string username, int positions []);
	static int saveProgress();
};

#endif