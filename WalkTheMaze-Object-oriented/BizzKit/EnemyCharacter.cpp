#include "EnemyCharacter.h"


EnemyCharacter::EnemyCharacter(){
    position = new Point();
	mdlviewer_init("mummy.mdl", model);
    position->x = -250;
    position->y = -250;
    position->z = 0;
    dir = 0;
    vel = 0.5;
	health = INT_MAX;
}

EnemyCharacter::~EnemyCharacter(){}
