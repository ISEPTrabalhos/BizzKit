#ifndef _GRAPHICS
#define _GRAPHICS

#include "GlobalVars.h"
#include "Status.h"
#include "Model.h"
#include "MainCharacter.h"
#include "EnemyCharacter.h"
#include "Obstacle.h"
#include "Trap.h"
#include "Door.h"

class Graphics{
public:
	static void drawGround(GLuint texID); // desenhaSolo
	static void drawNormal(GLdouble x, GLdouble y, GLdouble z, GLdouble normal[], tipo_material mat);
	static void drawNode(int no);
	static void drawArc(Arco arco); // desenhaArco
	static void drawMaze(void);
	static void drawAxis(void); // desenhaEixo
	static void drawDragPlane(int eixo); // desenhaPlanoDrag
	static void drawAxes(void); // desenhaEixos
	static void material(enum tipo_material mat);
	static void CrossProduct(GLdouble v1[], GLdouble v2[], GLdouble cross[]);
	static GLdouble VectorNormalize(GLdouble v[]);
    
    static void putLights(GLfloat* diffuse);
    static void setCamera(void);
    static void display(void);
    static void setProjection(int x, int y, GLboolean picking);
    static void myReshape(int w, int h);
    
    static void createTextures(GLuint texID[]);
    
	static void drawToolTip(float x, float y, float hp, GLfloat *c);
	static void drawToolTip3d(float x, float y, float z, float hp, GLfloat *c);
    static void drawMiniMap(int width, int height);
	static void displayMapList(int width, int height);
	static void drawText(string src, int posX, int posY);

	static void displayHealth(int width, int height);
	static void showScore(int width, int height);

	static void drawEnemy();
	static void drawDoors();
	static void drawCharacter();
	static void drawObstacle();
	static void drawTrap();

	static void drawCube(float size);
	static void drawFace(GLfloat *v1, GLfloat *v2, GLfloat *v3, GLfloat *v4);

	// functions for new login window
	static void loginDisplay(void);
	static void displayMyText(char *string, float x, float y, float z);

	static void displayMainMenu();
};

#endif