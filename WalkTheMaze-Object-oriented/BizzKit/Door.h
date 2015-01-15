#ifndef __EnemyCharacter
#define __EnemyCharacter

#include "GlobalVars.h"
#include "Point.h"

class Door {
public:
	StudioModel model;
	Point *position;

	Door();
	~Door();

};

#endif


