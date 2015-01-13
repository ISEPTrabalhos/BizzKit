#include "Trap.h"


Trap::Trap()
{
	size = 5.0;

    position = new Point();
	position->x = 126;
	position->y = -152;
	position->z = size / 2.0;
}

Trap::~Trap(){}
