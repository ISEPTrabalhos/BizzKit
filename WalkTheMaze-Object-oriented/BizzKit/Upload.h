#ifndef Upload_
#define Upload_

#include <stdlib.h>
#include <string>
#include <iostream>
#include "WebServices.h"
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h"
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"
#include <fstream>
using namespace std;

class Upload{

public:
	static int uploadProgress(string username, int score, GLfloat pos_x, GLfloat pos_y);
	static int saveProgress(string user, int score, GLfloat pos_x, GLfloat pos_y);
};

#endif