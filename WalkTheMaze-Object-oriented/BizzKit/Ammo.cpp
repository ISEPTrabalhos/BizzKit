#include "Ammo.h"


Ammo::Ammo(){
	position = new Point();
	mdlviewer_init("ammo.mdl", model);
	isTravelling = GL_FALSE;
	position->x = INT_MAX;
	position->y = INT_MAX;
	position->z = INT_MAX;
}

Ammo::~Ammo(){}

void Ammo::fire(GLfloat x, GLfloat y, GLfloat z, GLfloat direction)
{
	position->x = x;
	position->y = y;
	position->z = z;
	dir = direction;
	isTravelling = GL_TRUE;
}

void Ammo::travel()
{
	if (isTravelling)
	{
		position->x += vel * cosf(dir);
		position->y += vel * sinf(dir);
	}
}