#include "Trap.h"


Trap::Trap()
{
	size = 5.0;
	height = 0.1;

    position = new Point();
	position->x = 126;
	position->y = -152;
	position->z = 0;
}

Trap::~Trap(){}
