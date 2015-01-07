#ifndef __BizzKit__Obstacle__
#define __BizzKit__Obstacle__

#include "GlobalVars.h"
#include "Point.h"

class Obstacle {
public:
    Point *position;
	float size;
    
	Obstacle();
	~Obstacle();

	void draw();
};

#endif


