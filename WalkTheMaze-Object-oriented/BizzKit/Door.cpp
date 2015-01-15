#include "Door.h"

Door::Door(int x, int y, string mdl){
	position = new Point();
	mdlviewer_init((char*)mdl.c_str(), model);
	model.SetSequence(0);
	position->x = x;
	position->y = y;
	position->z = 0;
}

Door::~Door(){}
           
void Door::setDefaults(int x, int y) {
	model.SetSequence(0);
	position->x = x;
	position->y = y;
	position->z = 0;
}
