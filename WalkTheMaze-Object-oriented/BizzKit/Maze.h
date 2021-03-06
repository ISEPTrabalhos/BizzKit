#ifndef _MAZE
#define _MAZE

#include "GlobalVars.h"
#include "Model.h"
#include "Status.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Model.h"
#include <time.h>
#include "SnowFlake.h"
#include "Rain.h"

class Maze {
public:
    
	// functions
    static void Launch(int argc, char **argv);
    static void Timer(int value);
	static bool Collision(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat vel, GLfloat dir);
	static void ChasePlayer();
	static bool Walk(int direction);
	static bool CollisionObstacle(GLfloat x, GLfloat y, GLfloat z);
	static bool CollisionEnemy(GLfloat x, GLfloat y, GLfloat z);
	static bool AmmoHitEnemy(GLfloat x, GLfloat y, GLfloat z, GLfloat vel, GLfloat dir);
	static bool DetectTrap(GLfloat x, GLfloat y, GLfloat z);
	static void showLoginWindow();
	static void spawn();
};

#endif