#ifndef __SnowFlake__
#define __SnowFlake__

#include "GlobalVars.h"
#include "Point.h"
#include <ctime>

enum EFFECT {SNOW, RAIN};

class SnowFlake {
public:
	Point *position;
	Point *limit;
	int radious;
	bool flag;


	SnowFlake();
	~SnowFlake();
	void draw();
	void reGen();
};

#endif
