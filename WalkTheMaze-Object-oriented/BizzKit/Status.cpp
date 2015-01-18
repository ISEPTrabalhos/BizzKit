#include "Status.h"

Status::Status(){
	// set Camera
	camera = new Camera();

	// Set center
	eixo[0] = 0;
	eixo[1] = 0;
	eixo[2] = 0;

	// set light
	spotlight = GL_FALSE;
	light = GL_TRUE;
	apresentaNormais = GL_FALSE;
	lightViewer = 1;
  
	showMapMenu = GL_FALSE;

	first = top = GL_FALSE;
    eixoTranslaccao = 0;
	up = down = left = right = GL_FALSE;
	mapfile = "quarto3.grafo"; // for testing purpose it's better to have one of the rom as 'default' map

	/* SET UP THE MUSIC */
	background_music = new Music("background.wav");
	background_music->play();

	score = 0;
	main_light = (GLfloat*)white_light;
	daynight = true;

	walking = GL_FALSE;
	falling = GL_FALSE;
	snow = GL_FALSE;
	rain = GL_FALSE;

	username = "";
	password = "";
	passwd = "";
	loginErrorMessage = "";
	nextInput = false;
	loggedIn = false;
	mainMenu = false;
	showSoundsMenu = false;
	showTexturesMenu = false;
	finished = false;
	gameOver = false,

	soundsList = {};
	texturesList = {};

	gameRoute = "";
}

Status::~Status(){}


void Status::setDefaults() {
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
	mapfile = "quarto3.grafo"; // for testing purpose it's better to have one of the rom as 'default' map

	/* SET UP THE MUSIC */
	background_music = new Music("background.wav");
	//background_music->play();

	score = 0;
	main_light = (GLfloat*)white_light;
	daynight = true;

	walking = GL_FALSE;
	falling = GL_FALSE;
	snow = GL_FALSE;
	rain = GL_FALSE;

	mainMenu = false;
	showSoundsMenu = false;
	showTexturesMenu = false;
	finished = false;
	gameOver = false;

	soundsList = {};
	texturesList = {};

	gameRoute = "";
}
