#ifndef _MUSIC
#define _MUSIC

#include <string>
#include <iostream>
#include <fstream>

#include <conio.h>
#include <stdlib.h>
#include <AL/alut.h>
#include <stdio.h>

using namespace std;

class Music {
public:
	ALuint buffer, source;
	ALboolean status;

	Music(string file);
	~Music();

	//methods
	ALboolean choseMusic(string file);
	void play();
	void stop();
	void toggle();
};

#endif