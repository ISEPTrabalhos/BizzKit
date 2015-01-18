#include "EnemyCharacter.h"


EnemyCharacter::EnemyCharacter(){
    position = new Point();
	mdlviewer_init("mummy.mdl", model);
	model.SetSequence(1);
	position->x = -113;
	position->y = 163;
	position->z = ENEMY_HEIGHT / 2;
    dir = 0;
    vel = 0.35;
	health = maxHealth;
}

EnemyCharacter::~EnemyCharacter(){}

void EnemyCharacter::setDefaults() {
	model.SetSequence(1);
	position->x = -113;
	position->y = 163;
	position->z = ENEMY_HEIGHT / 2;
	dir = 0;
	health = maxHealth;
}