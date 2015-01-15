#include "Obstacle.h"


Obstacle::Obstacle()
{
	size = 2.0;
	height = 8.0;
	mdlviewer_init("tree.mdl", model);

    position = new Point();
    position->x = -230;
    position->y = -240;
	position->z = 0;
}

Obstacle::~Obstacle(){}
