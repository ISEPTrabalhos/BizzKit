#ifndef __BizzKit__EnemyCharacter__
#define __BizzKit__EnemyCharacter__

#include "GlobalVars.h"
#include "Point.h"

class EnemyCharacter {
public:
	const GLfloat maxHealth = 10000;
	const GLfloat damage = 4;
    StudioModel model;
    Point *position;
    GLfloat  dir;
    GLfloat  vel;
	GLfloat health;
    
	EnemyCharacter();
	~EnemyCharacter();
	void setDefaults();

};

#endif


