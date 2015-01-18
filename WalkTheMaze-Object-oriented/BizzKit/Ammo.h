#ifndef __BizzKit__Ammo__
#define __BizzKit__Ammo__

#include "GlobalVars.h"
#include "Point.h"

class Ammo {
public:
	const GLfloat damage = 100;
	const GLfloat vel = 5;
    StudioModel model;
    Point *position;
    GLfloat dir;
	GLboolean isTravelling;
    
	Ammo();
	~Ammo();

	void fire(GLfloat x, GLfloat y, GLfloat z, GLfloat direction);
	void travel();
};

#endif


