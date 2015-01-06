#include "Music.h"

Music::Music(string file){
	alGetError();
	choseMusic(file);
}

ALboolean Music::choseMusic(string file){
	// Load pcm data into buffer
	buffer = alutCreateBufferFromFile(file.c_str());

	// Create sound source (use buffer to fill source)
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);

	// Play
	alSourcePlay(source);

	return (alGetError() != AL_NO_ERROR) ? AL_FALSE : AL_TRUE;
}

void Music::play(){
	alSourcePlay(source);
	status = AL_TRUE;
}

void Music::stop(){
	alSourceStop(source);
	status = AL_FALSE;
}

void Music::toggle() {
	(status) ? stop() : play();
}