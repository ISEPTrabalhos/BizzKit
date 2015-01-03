#include "MainCharacter.h"


MainCharacter::MainCharacter(){
    position = new Point();
    mdlviewer_init("homer.mdl", homer);
    position->x = -250;
    position->y = -250;
    position->z = 1;
    dir = 0;
    vel = 0.5;
}

MainCharacter::~MainCharacter(){}
