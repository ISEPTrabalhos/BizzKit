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
  
    
    eixoTranslaccao = 0;
}

Status::~Status(){}

void Status::InitAudio()
{
	buffer = alutCreateBufferFromFile("The_Simpsons.wav");
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	tecla_o = AL_TRUE;
}