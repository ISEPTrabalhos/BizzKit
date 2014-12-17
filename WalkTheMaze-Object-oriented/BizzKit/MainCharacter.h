#ifndef __BizzKit__MainCharacter__
#define __BizzKit__MainCharacter__

#include "GlobalVars.h"
#include "Point.h"

class MainCharacter {
public:
    StudioModel homer;
    Point *position;
    GLfloat  dir;
    GLfloat  vel;
    
    MainCharacter();
    ~MainCharacter();

};

#endif
