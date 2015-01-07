#ifndef _MAZE
#define _MAZE

#include "GlobalVars.h"
#include "Model.h"
#include "Status.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Model.h"

class Maze {
public:
    
	// functions
    static void Launch(int argc, char **argv);
    static void Timer(int value);
	static bool Collision(GLfloat nx, GLfloat ny, GLfloat nz);
	static void Walk(int direction);
	static bool CollisionEnemy(GLfloat x, GLfloat y, GLfloat z);
};

#endif