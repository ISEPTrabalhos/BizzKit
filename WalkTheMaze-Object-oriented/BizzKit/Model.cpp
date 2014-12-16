#include "Model.h"

Model::Model(){
	// set scale
	escala = 0.2;

	// set color
	cor_cubo = brass;
	
	// set light
	g_pos_luz1[0] = -5.0;
	g_pos_luz1[1] = 5.0;
	g_pos_luz1[2] = 5.0;
	g_pos_luz1[3] = 0.0;
	g_pos_luz2[0] = 5.0;
	g_pos_luz2[1] = -15.0;
	g_pos_luz2[2] = 5.0;
	g_pos_luz2[3] = 0.0;
}

Model::~Model(){}