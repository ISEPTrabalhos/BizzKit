#ifndef _GRAPHICS
#define _GRAPHICS

#include "GlobalVars.h"
#include "Status.h"
#include "Model.h"

class Graphics{
public:
	static void drawGround(GLuint texID); // desenhaSolo
	static void drawNormal(GLdouble x, GLdouble y, GLdouble z, GLdouble normal[], tipo_material mat);
	static void drawWall(Status *status, GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf);
	static void drawPlatform(Status *status, GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf, int orient); //desenhaChao
	static void drawNode(Status *status, int no);
	static void drawArc(Status *status, Arco arco); // desenhaArco
	static void drawMaze(Status *status);
	static void drawAxis(Model *model); // desenhaEixo
	static void drawDragPlane(Status *status, int eixo); // desenhaPlanoDrag
	static void drawAxes(Status *status, Model *model); // desenhaEixos
	static void material(enum tipo_material mat);
	static void CrossProduct(GLdouble v1[], GLdouble v2[], GLdouble cross[]);
	static GLdouble VectorNormalize(GLdouble v[]);
};

#endif