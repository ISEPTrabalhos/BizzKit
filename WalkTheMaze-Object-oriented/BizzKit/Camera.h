#ifndef _CAMERA
#define _CAMERA

#include "GlobalVars.h"

class Camera {
public:
	GLfloat fov;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	Vertice center;

	// functions
	Camera();
	~Camera();
};

#endif