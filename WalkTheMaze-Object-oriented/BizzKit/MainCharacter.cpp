#include "MainCharacter.h"


MainCharacter::MainCharacter(){
    position = new Point();
    //mdlviewer_init("homer.mdl", homer);
    position->x = 0;
    position->y = 0;
    position->z = 0;
    dir = 0;
    vel = 1;
}

MainCharacter::~MainCharacter(){}
