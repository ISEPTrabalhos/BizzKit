#ifndef _GRAPHICS
#define _GRAPHICS

#include "GlobalVars.h"
#include "Status.h"
#include "Model.h"
#include "MainCharacter.h"

class Graphics{
public:
	static void drawGround(GLuint texID); // desenhaSolo
	static void drawNormal(GLdouble x, GLdouble y, GLdouble z, GLdouble normal[], tipo_material mat);
	static void drawWall(GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf);
	static void drawPlatform(GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf, int orient); //desenhaChao
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
    
    static void drawMiniMap(int width, int height);
};

#endif