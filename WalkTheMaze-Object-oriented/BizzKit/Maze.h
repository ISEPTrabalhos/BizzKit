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
	static void putLights(GLfloat* diffuse);
	static void setCamera(void);
	static void display(void);
	static void setProjection(int x, int y, GLboolean picking);
	static void myReshape(int w, int h);
	static void motionRotate(int x, int y);
	static void motionZoom(int x, int y);
	static void motionDrag(int x, int y);
	static int picking(int x, int y);
	static void mouse(int btn, int state, int x, int y);
	static void Launch(int argc, char **argv);
	static void keyboard(unsigned char key, int x, int y);
	static void Special(int key, int x, int y);
	static void help(void);
    static void createTextures(GLuint texID[]);
};

#endif