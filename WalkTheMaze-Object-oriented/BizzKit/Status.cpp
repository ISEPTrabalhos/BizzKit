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
  
	//showMapMenu = GL_FALSE;

	first = top = GL_FALSE;
    eixoTranslaccao = 0;
	up = down = left = right = GL_FALSE;
	mapfile = "quarto1.grafo";
}

Status::~Status(){}

void Status::InitAudio()
{
	buffer = alutCreateBufferFromFile("The_Simpsons.wav");
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	tecla_o = AL_TRUE;
}