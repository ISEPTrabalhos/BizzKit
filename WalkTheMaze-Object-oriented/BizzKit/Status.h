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
	GLboolean showMapMenu;
	GLint lightViewer;
	GLint eixoTranslaccao;
	GLdouble eixo[3];
    GLint		timer;
    ALuint		buffer, source;
    ALboolean	tecla_o;
	GLboolean		top, first;
	GLboolean up, down, right, left;

	// functions
	Status();
	~Status();
	void InitAudio();
};

#endif