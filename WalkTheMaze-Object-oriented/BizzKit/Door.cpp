#include "Door.h"

Door::Door(int x, int y){
	position = new Point();
	mdlviewer_init("door.mdl", model);
	model.SetSequence(0);
	position->x = x;
	position->y = y;
	position->z = 0;
}

Door::~Door(){}
