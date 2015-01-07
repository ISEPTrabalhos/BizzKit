#include "Obstacle.h"


Obstacle::Obstacle()
{
	size = 5.0;

    position = new Point();
    position->x = -230;
    position->y = -240;
	position->z = size / 2.0;
}

Obstacle::~Obstacle(){}
