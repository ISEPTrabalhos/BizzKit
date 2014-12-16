#ifndef _MODEL
#define _MODEL

#include "GlobalVars.h"

class Model {
public:
#ifdef __cplusplus
	tipo_material cor_cubo;
#else
	enum tipo_material cor_cubo;
#endif

	GLfloat g_pos_luz1[4];
	GLfloat g_pos_luz2[4];

	GLfloat escala;
	GLUquadric *quad;
    GLuint texID[1];


	// functions
	Model();
	~Model();
};

#endif