#ifndef __BizzKit__Obstacle__
#define __BizzKit__Obstacle__

#include "GlobalVars.h"
#include "Point.h"

class Obstacle {
public:
	StudioModel model;
    Point *position;
	float size;
	float height;
    
	Obstacle();
	~Obstacle();
};

#endif


