#ifndef __Rain__
#define __Rain__

#include "GlobalVars.h"
#include "Point.h"
#include <ctime>

class Rain {
public:
	Point *position;
	Point *limit;
	int radious;
	bool flag;
	GLdouble vel;

	Rain();
	~Rain();
	void draw();
	void reGen();
};

#endif