#ifndef __BizzKit__EnemyCharacter__
#define __BizzKit__EnemyCharacter__

#include "GlobalVars.h"
#include "Point.h"

class EnemyCharacter {
public:
	const GLint maxHealth = 10000;
	const GLint damage = 4;
    StudioModel model;
    Point *position;
    GLfloat  dir;
    GLfloat  vel;
	GLint health;
    
	EnemyCharacter();
	~EnemyCharacter();
	void setDefaults();

};

#endif


