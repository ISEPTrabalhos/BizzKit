#ifndef __SnowFlake__
#define __SnowFlake__

#include "GlobalVars.h"
#include "Point.h"
#include <ctime>

class SnowFlake {
public:
	Point *position;
	Point *limit;
	int radious;
	bool flag;
	GLdouble vel;

	SnowFlake();
	~SnowFlake();
	void draw();
	void reGen();
};

#endif
