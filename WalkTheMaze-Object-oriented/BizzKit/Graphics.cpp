#include "Graphics.h"
#include "MapsReceiver.h"

#define SCALE_HOMER 0.005
#define GRAUS(x)        (180*(x)/M_PI)
#define K_CIRCLE 1.0
#define K_CONNECTION 1.0
#define INFINITESIMO 0.000001

extern Status *status;
extern Model *model;
extern MainCharacter *character;

void Graphics::drawGround(GLuint texID){
#define STEP 10
    glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	for (int i = -300; i<300; i += STEP)
	for (int j = -300; j<300; j += STEP){
        glTexCoord2f(1, 1);
        glVertex2f(i,j);
        glTexCoord2f(0, 1);
        glVertex2f(i+STEP,j);
        glTexCoord2f(0, 0);
        glVertex2f(i+STEP,j+STEP);
        glTexCoord2f(1, 0);
        glVertex2f(i,j+STEP);
	}
	glEnd();
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void Graphics::CrossProduct(GLdouble v1[], GLdouble v2[], GLdouble cross[]){
	cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
	cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
	cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

GLdouble Graphics::VectorNormalize(GLdouble v[]){
	int		i;
	GLdouble	length;

	if (fabs(v[1] - 0.000215956) < 0.0001)
		i = 1;

	length = 0;
	for (i = 0; i< 3; i++)
		length += v[i] * v[i];
	length = sqrt(length);
	if (length == 0)
		return 0;

	for (i = 0; i< 3; i++)
		v[i] /= length;

	return length;
}

void Graphics::drawNormal(GLdouble x, GLdouble y, GLdouble z, GLdouble normal[], tipo_material mat){

	switch (mat){
	case red_plastic:
		glColor3f(1, 0, 0);
		break;
	case azul:
		glColor3f(0, 0, 1);
		break;
	case emerald:
		glColor3f(0, 1, 0);
		break;
	default:
		glColor3f(1, 1, 0);
	}
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(0.4, 0.4, 0.4);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3dv(normal);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Graphics::drawNode(int no){
	No * noI = &nos[no];
	GLUquadric * quadric = gluNewQuadric();
	GLfloat radius = K_CIRCLE * noI->largura * 0.5;
	GLfloat comp = noI->z + 2.0 * INFINITESIMO;
	Arco arco = arcos[0];

	glPushMatrix();
	glTranslatef(noI->x, noI->y, noI->z + INFINITESIMO);
	gluDisk(quadric, 0, radius, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(noI->x, noI->y, -INFINITESIMO);
	gluCylinder(quadric, radius, radius, comp, 20, 1);
	glPopMatrix();

	for (int i = 0; i < numArcos; arco =  arcos[i++]){
		if (no == arco.noi){
			No * noF = &nos[arco.nof];
			comp = radius * K_CONNECTION;
			GLfloat alpha = graus(atan2(noF->y - noI->y, noF->x - noI->x));

			//	Horizontal rectangle
			glPushMatrix();
			glTranslatef(noI->x, noI->y, noI->z);
			glRotatef(alpha, 0.0, 0.0, 1.0);
			glTranslatef(comp * 0.5, 0.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, 0.0);
			glEnd();
			glPopMatrix();

			//	Vertical rectangles
			glPushMatrix();
			glTranslatef(noI->x, noI->y, -INFINITESIMO);
			glRotatef(alpha, 0.0, 0.0, 1.0);
			glTranslatef(comp * 0.5, 0.0, 0.0);
			glBegin(GL_QUADS);

			//	1
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, 0.0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, noI->z);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, noI->z);

			//	2
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, noI->z);
			glVertex3f(comp * 0.5, arco.largura * 0.5, noI->z);

			glEnd();
			glPopMatrix();

			
		}
		else if (no == arco.nof){
			noI = &nos[arco.nof];
			No * noF = &nos[arco.noi];
			comp = radius * K_CONNECTION;
			GLfloat alpha = graus(atan2(noF->y - noI->y, noF->x - noI->x));

			//	Horizontal rectangle
			glPushMatrix();
			glTranslatef(noI->x, noI->y, noI->z);
			glRotatef(alpha, 0.0, 0.0, 1.0);
			glTranslatef(comp * 0.5, 0.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, 0.0);
			glEnd();
			glPopMatrix();

			//	Vertical rectangles
			glPushMatrix();
			glTranslatef(noI->x, noI->y, -INFINITESIMO);
			glRotatef(alpha, 0.0, 0.0, 1.0);
			glTranslatef(comp * 0.5, 0.0, 0.0);
			glBegin(GL_QUADS);

			//	1
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, 0.0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, noI->z);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, noI->z);

			//	2
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, noI->z);
			glVertex3f(comp * 0.5, arco.largura * 0.5, noI->z);

			glEnd();
			glPopMatrix();


		}
	}
}


void Graphics::drawArc(Arco arco){

	No *noi = &nos[arco.noi], *nof = &nos[arco.nof];
	GLfloat ri = K_CIRCLE * noi->largura * 0.5;
	GLfloat si = K_CONNECTION * ri;
	GLfloat rf = K_CIRCLE * nof->largura * 0.5;
	GLfloat sf = K_CONNECTION * rf;
	GLfloat projLength = sqrtf(powf(nof->x - noi->x, 2) + powf(nof->y - noi->y, 2)) - si - sf;
	GLfloat gap = nof->z - noi->z;
	GLfloat length = sqrt(powf(projLength, 2) + pow(gap, 2));
	GLfloat orientation = graus(atan2(nof->y - noi->y, nof->x - noi->x));
	GLfloat inclination = graus(atan2(gap, projLength));

	glPushMatrix();
	glTranslatef(noi->x, noi->y, noi->z);
	glRotatef(orientation, 0.0, 0.0, 1.0);
	glTranslatef(si, 0.0, 0.0);
	glRotatef(-inclination, 0.0, 1.0, 0.0);
	glTranslatef(length * 0.5, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-length * 0.5, arco.largura * 0.5, 0);
	glVertex3f(length * 0.5, arco.largura * 0.5, 0);
	glVertex3f(length * 0.5, -arco.largura * 0.5, 0);
	glVertex3f(-length * 0.5, -arco.largura * 0.5, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(noi->x, noi->y, -INFINITESIMO);
	glRotatef(orientation, 0.0, 0.0, 1.0);
	glTranslatef(si, 0.0, 0.0);

	//	1
	glBegin(GL_QUADS);
	glVertex3f(0.0, -arco.largura * 0.5, 0.0);
	glVertex3f(projLength, -arco.largura * 0.5, 0.0);
	glVertex3f(projLength, -arco.largura * 0.5, nof->z);
	glVertex3f(0.0, -arco.largura * 0.5, noi->z);
	glEnd();

	//	2
	glBegin(GL_QUADS);
	glVertex3f(projLength, arco.largura * 0.5, 0.0);
	glVertex3f(0.0, arco.largura * 0.5, 0.0);
	glVertex3f(0.0, arco.largura * 0.5, noi->z);
	glVertex3f(projLength, arco.largura * 0.5, nof->z);
	glEnd();
	glPopMatrix();
}

void Graphics::drawMaze(){
	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	glScalef(5, 5, 5);
	Graphics::material(red_plastic);
	for (int i = 0; i<numNos; i++){
		glPushMatrix();
		Graphics::material(preto);
		glTranslatef(nos[i].x, nos[i].y, nos[i].z + 0.25);
		//glutSolidCube(0.5);
		glPopMatrix();
		Graphics::drawNode(i);
	}
	Graphics::material(emerald);
	for (int i = 0; i<numArcos; i++)
		Graphics::drawArc(arcos[i]);
	glPopMatrix();
}

void Graphics::drawAxis(){
	gluCylinder(model->quad, 0.5, 0.5, 20, 16, 15);
	glPushMatrix();
	glTranslatef(0, 0, 20);
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	gluDisk(model->quad, 0.5, 2, 16, 6);
	glPopMatrix();
	gluCylinder(model->quad, 2, 0, 5, 16, 15);
	glPopMatrix();
}

#define EIXO_X		1
#define EIXO_Y		2
#define EIXO_Z		3

void Graphics::drawDragPlane(int eixo){
	glPushMatrix();
	glTranslated(status->eixo[0], status->eixo[1], status->eixo[2]);
    switch (eixo) {
        case EIXO_Y :
            if(fabs(status->camera->dir_lat)<M_PI/4)
                glRotatef(-90,0,0,1);
            else
                glRotatef(90,1,0,0);
            material(red_plastic);
            break;
        case EIXO_X :
            if(fabs(status->camera->dir_lat)>M_PI/6)
                glRotatef(90,1,0,0);
            material(azul);
            break;
        case EIXO_Z :
            if(fabs(cos(status->camera->dir_long))>0.5)
                glRotatef(90,0,0,1);
            
            material(emerald);
            break;
    }
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-100, 0, -100);
	glVertex3f(100, 0, -100);
	glVertex3f(100, 0, 100);
	glVertex3f(-100, 0, 100);
	glEnd();
	glPopMatrix();
}

void Graphics::drawAxes(){

	glPushMatrix();
	glTranslated(status->eixo[0], status->eixo[1], status->eixo[2]);
	Graphics::material(emerald);
	glPushName(EIXO_Z);
	Graphics::drawAxis();
	glPopName();
	glPushName(EIXO_Y);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	Graphics::material(red_plastic);
	Graphics::drawAxis();
	glPopMatrix();
	glPopName();
	glPushName(EIXO_X);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	Graphics::material(azul);
	Graphics::drawAxis();
	glPopMatrix();
	glPopName();
	glPopMatrix();
}

void Graphics::material(enum tipo_material mat) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient[mat]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse[mat]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular[mat]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess[mat]);
}

void Graphics::putLights(GLfloat* diffuse){
    const GLfloat white_amb[] = { 0.2, 0.2, 0.2, 1.0 };
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white_amb);
    glLightfv(GL_LIGHT0, GL_POSITION, model->g_pos_luz1);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT1, GL_AMBIENT, white_amb);
    glLightfv(GL_LIGHT1, GL_POSITION, model->g_pos_luz2);
    
    /* desenhar luz */
    //material(red_plastic);
    //glPushMatrix();
    //	glTranslatef(Maze::model->g_pos_luz1[0], Maze::model->g_pos_luz1[1], Maze::model->g_pos_luz1[2]);
    //	glDisable(GL_LIGHTING);
    //	glColor3f(1.0, 1.0, 1.0);
    //	glutSolidCube(0.1);
    //	glEnable(GL_LIGHTING);
    //glPopMatrix();
    //glPushMatrix();
    //	glTranslatef(Maze::model->g_pos_luz2[0], Maze::model->g_pos_luz2[1], Maze::model->g_pos_luz2[2]);
    //	glDisable(GL_LIGHTING);
    //	glColor3f(1.0, 1.0, 1.0);
    //	glutSolidCube(0.1);
    //	glEnable(GL_LIGHTING);
    //glPopMatrix();
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void Graphics::setCamera(){

    Vertice eye;

	if (status->top){

		//	set the camera center to the character
		status->camera->center[0] = character->position->x + cos(status->camera->dir_long)*cos(status->camera->dir_lat);
		status->camera->center[1] = character->position->y + sin(status->camera->dir_long)*cos(status->camera->dir_lat);
		status->camera->center[2] = character->position->z;

		//	set the eye of the camera to a position above the character
		eye[0] = character->position->x;
		eye[1] = character->position->y;
		eye[2] = character->position->z + CHARACTER_HEIGHT * 4;
	} 
	else if(status->first){

		status->camera->center[0] = character->position->x + cos(status->camera->dir_long)*cos(status->camera->dir_lat);
		status->camera->center[1] = character->position->y +  sin(status->camera->dir_long)*cos(status->camera->dir_lat);
		status->camera->center[2] = 1;

		eye[0] = character->position->x;
		eye[1] = character->position->y;
		eye[2] = 1;
	}

	else{
		status->camera->center[0] = character->position->x;
		status->camera->center[1] = character->position->y;
		status->camera->center[2] = 1;

		eye[0] = character->position->x + cos(character->dir);
		eye[1] = character->position->y + sin(character->dir);
		eye[2] = 1;

		/*eye[0] = status->camera->center[0] + status->camera->dist*cos(status->camera->dir_long)*cos(status->camera->dir_lat);
		eye[1] = status->camera->center[1] + status->camera->dist*sin(status->camera->dir_long)*cos(status->camera->dir_lat);
		eye[2] = status->camera->center[2] + status->camera->dist*sin(status->camera->dir_lat);*/
	}

    if (status->light){
        gluLookAt(eye[0], eye[1], eye[2], status->camera->center[0], status->camera->center[1], status->camera->center[2], 0, 0, 1);
        Graphics::putLights((GLfloat*)white_light);
    }
    else{
        Graphics::putLights((GLfloat*)white_light);
        gluLookAt(eye[0], eye[1], eye[2], status->camera->center[0], status->camera->center[1], status->camera->center[2], 0, 0, 1);
    }
}

void Graphics::display(void){
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    Graphics::setCamera();
    
    Graphics::material(slate);
    Graphics::drawGround(model->texID[0]);
    
    glPushMatrix();
    glTranslatef(character->position->x ,character->position->y,character->position->z);
    glRotatef(GRAUS(character->dir),0,0,1);
    glScalef(SCALE_HOMER,SCALE_HOMER,SCALE_HOMER);
    mdlviewer_display(character->homer);
    glPopMatrix();
    
    Graphics::drawAxes();
    
    Graphics::drawMaze();
    
    if (status->eixoTranslaccao) {
        // desenha plano de translacÁ„o
        cout << "Translate... " << status->eixoTranslaccao << endl;
        Graphics::drawDragPlane(status->eixoTranslaccao);
    }
    
    Graphics::drawMiniMap(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    
	/*if (status->showMapMenu) {
		Graphics::displayMapList(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}*/

    glFlush();
    glutSwapBuffers();
    
}

void Graphics::setProjection(int x, int y, GLboolean picking){
    glLoadIdentity();
    if (picking) { // esta no modo picking
        GLint vport[4];
        glGetIntegerv(GL_VIEWPORT, vport);
        gluPickMatrix(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 4, 4, vport); // Inverte o rato para corresponder
    }
    
    gluPerspective(status->camera->fov, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1, 500);
    
}

void Graphics::myReshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    Graphics::setProjection(0, 0, GL_FALSE);
    glMatrixMode(GL_MODELVIEW);
}

void Graphics::createTextures(GLuint texID[]) {
    char *image;
    int w, h, bpp;
    
    glGenTextures(1,texID);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if(	read_JPEG_file(FLOOR_TEXTURE, &image, &w, &h, &bpp))
    {
        glBindTexture(GL_TEXTURE_2D, texID[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
    }else{
        printf("Textura %s not Found\n",FLOOR_TEXTURE);
        exit(0);
    }
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void Graphics::drawMiniMap(int width, int height) {

    // Altera viewport e projecção
    
    glViewport(width * 0.65, 0, 250, 250);
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    // mini map option to big view
    //glOrtho(-100, 100, -100, 100, -100, 100);
    
    // mini map option to room view
    glOrtho(-1000, 1000, -1000, 1000, -100, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    
    Graphics::drawMaze();
    
    Graphics::myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// kemaybe can be used later
//void Graphics::displayMapList(int width, int height) {
//	
//	glViewport(0, 0, width, height);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glOrtho(-100, 100, -100, 100, -100, 100);
//	glOrtho(-width, width, -height, height, -100, 100);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glColor3f(1, 0, 0);
//
//	int posX = -width + 50, gap = 0;
//
//	MapsReceiver *receiver = new MapsReceiver();
//	vector<string> maps = receiver->getAllMaps();
//	
//	for (int i = 0; i < maps.size(); i++) {
//		gap += 50;
//		string str = to_string(i+1) + " - " + maps.at(i);
//		Graphics::drawText(str, posX, height - gap);
//	}
//
//	Graphics::myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//}
//void Graphics::drawText(string src, int posX, int posY)
//{
//	char text[50];
//	sprintf(text, src.c_str());
//	glColor3f(0, 0, 0);
//	glRasterPos2i(posX, posY);
//	for (int i = 0; text[i] != '\0'; i++)
//		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
//}


