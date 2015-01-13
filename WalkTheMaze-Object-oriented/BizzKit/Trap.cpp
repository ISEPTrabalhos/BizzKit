#include "Trap.h"


Trap::Trap()
{
	size = 5.0;
	height = 1.1;

    position = new Point();
	position->x = 126;
	position->y = -152;
	position->z = 0.0;
}

Trap::~Trap(){}
