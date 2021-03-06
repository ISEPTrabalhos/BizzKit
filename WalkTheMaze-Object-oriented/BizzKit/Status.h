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
	GLboolean attacking;
	GLboolean daynight;
	GLboolean walking;
	GLboolean falling;
	GLboolean snow, rain, spotlight;

	string username, password, passwd, loginErrorMessage;
	bool nextInput, loggedIn, mainMenu, showSoundsMenu, showTexturesMenu, finished, gameOver, showEnemiesModelsMenu;

	vector<string> soundsList, texturesList, enemiesModelsList;

	string gameRoute;

	// functions
	Status();
	~Status();
	void setDefaults();
};

#endif