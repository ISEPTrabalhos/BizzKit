#ifndef __BizzKit__Trap__
#define __BizzKit__Trap__

#include "GlobalVars.h"
#include "Point.h"

class Trap {
public:
    Point *position;
	float size;
	float height;
    
	Trap();
	~Trap();
};

#endif


