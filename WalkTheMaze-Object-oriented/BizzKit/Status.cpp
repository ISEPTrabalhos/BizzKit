#include "Status.h"

Status::Status(){
	// set Camera
	camera = new Camera();

	// Set center
	eixo[0] = 0;
	eixo[1] = 0;
	eixo[2] = 0;

	// set light
	light = GL_FALSE;
	apresentaNormais = GL_FALSE;
	lightViewer = 1;
  
	showMapMenu = GL_FALSE;

	first = top = GL_FALSE;
    eixoTranslaccao = 0;
	up = down = left = right = GL_FALSE;
	mapfile = "quarto1.grafo"; // for testing purpose it's better to have one of the rom as 'default' map

	/* SET UP THE MUSIC */
	background_music = new Music("The_Simpsons.wav");
	background_music->play();

	score = 0;
	main_light = (GLfloat*)white_light;
	daynight = true;

	walking = GL_FALSE;
	falling = GL_FALSE;

	username = "";
	password = "";
	passwd = "";
	loginErrorMessage = "";
	nextInput = false;
	loggedIn = false;
	mainMenu = false;
	showSoundsMenu = false;
	showTexturesMenu = false;

	soundsList = {};
	texturesList = {};
}

Status::~Status(){}
