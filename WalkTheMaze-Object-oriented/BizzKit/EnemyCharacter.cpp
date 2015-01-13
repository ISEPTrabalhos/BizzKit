#include "EnemyCharacter.h"


EnemyCharacter::EnemyCharacter(){
    position = new Point();
	mdlviewer_init("mummy.mdl", model);
	model.SetSequence(1);
	position->x = -113;
	position->y = 163;
	position->z = CHARACTER_HEIGHT / 2;
    dir = 0;
    vel = 0.5;
	health = INT_MAX;
}

EnemyCharacter::~EnemyCharacter(){}
