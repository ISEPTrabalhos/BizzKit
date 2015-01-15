#include "Door.h"

Door::Door(){
	position = new Point();
	mdlviewer_init("door.mdl", model);
	model.SetSequence(0);
}

Door::~Door(){}
