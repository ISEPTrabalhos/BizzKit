#ifndef __BizzKit__EnemyCharacter__
#define __BizzKit__EnemyCharacter__

#include "GlobalVars.h"
#include "Point.h"

class EnemyCharacter {
public:
    StudioModel model;
    Point *position;
    GLfloat  dir;
    GLfloat  vel;
	GLint health;
    
	EnemyCharacter();
	~EnemyCharacter();

};

#endif


