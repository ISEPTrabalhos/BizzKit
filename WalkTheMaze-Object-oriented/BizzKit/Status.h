#ifndef _STATUS
#define _STATUS

#include "GlobalVars.h"
#include "Camera.h"
#include "Music.h"

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
    Music *background_music;
    ALboolean	tecla_o;
	GLboolean		top, first;
	GLboolean up, down, right, left;
	string mapfile;
	int score;
	GLfloat* main_light;
	GLboolean daynight;
	GLboolean walking;

	string username, password, passwd, loginErrorMessage;
	bool nextInput, loggedIn;

	// functions
	Status();
	~Status();
};

#endif