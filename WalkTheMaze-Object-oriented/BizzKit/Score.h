#ifndef _Score
#define _Score

#include <stdlib.h>
#include <string>
#include <iostream>
#include "WebServices.h"
#include "schemas.microsoft.com.2003.10.Serialization.xsd.h"
#include "tempuri.org.xsd.h"
#include "tempuri.org.wsdl.h"

using namespace std;

class Score{

public:
	static int uploadScore(string username, int score);
};
#endif