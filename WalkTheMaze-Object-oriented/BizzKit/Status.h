#ifndef _STATUS
#define _STATUS

#include "GlobalVars.h"
#include "Camera.h"

class Status {
public:
	Camera *camera;
	int xMouse, yMouse;
	GLboolean light;
	GLboolean apresentaNormais;
	GLint lightViewer;
	GLint eixoTranslaccao;
	GLdouble eixo[3];

	// functions
	Status();
	~Status();
};

#endif