#include "Graphics.h"
#include "MapsReceiver.h"
#include "ServicesHandler.h"

#define SCALE_HOMER 0.02
#define GRAUS(x)        (180*(x)/M_PI)
#define K_CIRCLE 1.0
#define K_CONNECTION 1.0
#define INFINITESIMO 0.000001

extern Status *status;
extern Model *model;
extern MainCharacter *character;
extern EnemyCharacter *enemy;
extern Door *door1, *door2, *exitDoor;
extern Obstacle *obstacle;
extern Trap *trap;
extern SnowFlake* sf[10];

void Graphics::drawEffect(void) {
	double w = glutGet(GLUT_WINDOW_WIDTH);
	double h = glutGet(GLUT_WINDOW_HEIGHT);

	// switch to 2D for text overlay
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w, w, -h, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	for (size_t i = 0; i < 40; i++) sf[i]->draw();

	glEnable(GL_LIGHTING);
	glutSwapBuffers();
}

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
			glTexCoord2f(0, 0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.0);
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.25);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.0, 0.25);
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
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.25);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, noI->z);
			glTexCoord2f(0.0, 0.25);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, noI->z);

			//	2
			glTexCoord2f(0.0, 0.0);
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.25);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, noI->z);
			glTexCoord2f(0.0, 0.25);
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
			glTexCoord2f(0, 0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.0);
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.25);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.0, 0.25);
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
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.0);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.25);
			glVertex3f(comp * 0.5, -arco.largura * 0.5, noI->z);
			glTexCoord2f(0.0, 0.25);
			glVertex3f(-comp * 0.5, -arco.largura * 0.5, noI->z);

			//	2
			glTexCoord2f(0.0, 0.0);
			glVertex3f(comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.0);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, 0.0);
			glTexCoord2f(0.25, 0.25);
			glVertex3f(-comp * 0.5, arco.largura * 0.5, noI->z);
			glTexCoord2f(0.0, 0.25);
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
	glTexCoord2f(0, 0);
	glVertex3f(-length * 0.5, arco.largura * 0.5, 0);
	glTexCoord2f(0.25, 0);
	glVertex3f(length * 0.5, arco.largura * 0.5, 0);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(length * 0.5, -arco.largura * 0.5, 0);
	glTexCoord2f(0, 0.25);
	glVertex3f(-length * 0.5, -arco.largura * 0.5, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(noi->x, noi->y, -INFINITESIMO);
	glRotatef(orientation, 0.0, 0.0, 1.0);
	glTranslatef(si, 0.0, 0.0);

	//	1
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, -arco.largura * 0.5, 0.0);
	glTexCoord2f(0.25, 0.0);
	glVertex3f(projLength, -arco.largura * 0.5, 0.0);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(projLength, -arco.largura * 0.5, nof->z);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(0.0, -arco.largura * 0.5, noi->z);
	glEnd();

	//	2
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(projLength, arco.largura * 0.5, 0.0);
	glTexCoord2f(0.25, 0.0);
	glVertex3f(0.0, arco.largura * 0.5, 0.0);
	glTexCoord2f(0.25, 0.25);
	glVertex3f(0.0, arco.largura * 0.5, noi->z);
	glTexCoord2f(0.0, 0.25);
	glVertex3f(projLength, arco.largura * 0.5, nof->z);
	glEnd();
	glPopMatrix();

}

void Graphics::drawMaze(){

	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	glScalef(5, 5, 5);
	//Graphics::material(red_plastic);
	for (int i = 0; i<numNos; i++){
		glPushMatrix();
		//Graphics::material(preto);
		glTranslatef(nos[i].x, nos[i].y, nos[i].z + 0.25);
		//glutSolidCube(0.5);
		glPopMatrix();
		Graphics::drawNode(i);
	}
	//Graphics::material(emerald);
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
		status->camera->center[0] = character->position->x + cos(character->dir);
		status->camera->center[1] = character->position->y + sin(character->dir);
		status->camera->center[2] = character->position->z;

		//	set the eye of the camera to a position above the character
		eye[0] = character->position->x;
		eye[1] = character->position->y;
		eye[2] = character->position->z + 7;
	} 
	else if(status->first){

		status->camera->center[0] = character->position->x + cos(character->dir);
		status->camera->center[1] = character->position->y + sin(character->dir);
		status->camera->center[2] = character->position->z;

		eye[0] = character->position->x;
		eye[1] = character->position->y;
		eye[2] = character->position->z;
	}

	else{
		status->camera->center[0] = character->position->x;
		status->camera->center[1] = character->position->y;
		status->camera->center[2] = CHARACTER_HEIGHT * 0.5 + character->position->z;

		eye[0] = character->position->x - cos(character->dir) * 5;
		eye[1] = character->position->y - sin(character->dir) * 5;
		eye[2] = CHARACTER_HEIGHT * 0.5 + character->position->z;

		/*eye[0] = status->camera->center[0] + status->camera->dist*cos(status->camera->dir_long)*cos(status->camera->dir_lat);
		eye[1] = status->camera->center[1] + status->camera->dist*sin(status->camera->dir_long)*cos(status->camera->dir_lat);
		eye[2] = status->camera->center[2] + status->camera->dist*sin(status->camera->dir_lat);*/
	}

    if (status->light){
        gluLookAt(eye[0], eye[1], eye[2], status->camera->center[0], status->camera->center[1], status->camera->center[2], 0, 0, 1);
        Graphics::putLights(status->main_light);//(GLfloat*)white_light
    }
    else{
        Graphics::putLights(status->main_light);//(GLfloat*)white_light
        gluLookAt(eye[0], eye[1], eye[2], status->camera->center[0], status->camera->center[1], status->camera->center[2], 0, 0, 1);
    }
}

void Graphics::drawEnemy(){
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glTranslatef(enemy->position->x, enemy->position->y, enemy->position->z);
	glRotatef(GRAUS(enemy->dir), 0, 0, 1);
	glScalef(SCALE_HOMER, SCALE_HOMER, SCALE_HOMER);
	mdlviewer_display(enemy->model);
	glPopMatrix();
}

void Graphics::drawDoors() {
	if (status->mapfile.compare("quarto1.grafo") == 0) {
		door1->position->x = 15;
		door1->position->y = 290;
	}
	 else if (status->mapfile.compare("quarto2.grafo") == 0) {
		door1->position->x = -125;
		door1->position->y = -285;
	}
	else if (status->mapfile.compare("quarto3.grafo") == 0) {
		door1->position->x = -280;
		door1->position->y = 250;
	}
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glTranslatef(door1->position->x, door1->position->y, door1->position->z);
		glRotatef(90, 0, 0, 1);
		glScalef(SCALE_HOMER, SCALE_HOMER, SCALE_HOMER);
		mdlviewer_display(door1->model);
	glPopMatrix();
	if (status->mapfile.compare("quarto1.grafo") == 0) {
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, NULL);
			glTranslatef(door2->position->x, door2->position->y, door2->position->z);
			glRotatef(180, 0, 0, 1);
			glScalef(SCALE_HOMER, SCALE_HOMER, SCALE_HOMER);
			mdlviewer_display(door2->model);
		glPopMatrix();
	}
	if (status->mapfile.compare("quarto3.grafo") == 0) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, NULL);
		glTranslatef(exitDoor->position->x, exitDoor->position->y, exitDoor->position->z);
		glRotatef(0, 0, 0, 1);
		glScalef(SCALE_HOMER, SCALE_HOMER, SCALE_HOMER);
		mdlviewer_display(exitDoor->model);
		glPopMatrix();
	}
	
}

void Graphics::drawCharacter(){
	glPushMatrix();
	glTranslatef(character->position->x, character->position->y, character->position->z);
	glRotatef(GRAUS(character->dir), 0, 0, 1);
	glScalef(SCALE_HOMER, SCALE_HOMER, SCALE_HOMER);
	mdlviewer_display(character->homer);
	glPopMatrix();
}

void Graphics::drawCube(float size)
{
	GLfloat xMin, xMax;
	GLfloat yMin, yMax;
	GLfloat zMin, zMax;

	xMin = yMin = zMin = -size / 2.0;
	xMax = yMax = zMax = size / 2.0;

	GLfloat vert[][3] = {
		{ xMin, yMin, zMin },
		{ xMax, yMin, zMin },
		{ xMax, yMax, zMin },
		{ xMin, yMax, zMin },
		{ xMin, yMin, zMax },
		{ xMax, yMin, zMax },
		{ xMax, yMax, zMax },
		{ xMin, yMax, zMax }
	};

	drawFace(vert[0], vert[1], vert[2], vert[3]);
	drawFace(vert[4], vert[5], vert[6], vert[7]);
	drawFace(vert[0], vert[1], vert[5], vert[4]);
	drawFace(vert[3], vert[2], vert[6], vert[7]);
	drawFace(vert[3], vert[0], vert[4], vert[7]);
	drawFace(vert[2], vert[1], vert[5], vert[6]);
}

void Graphics::drawFace(GLfloat *v1, GLfloat *v2, GLfloat *v3, GLfloat *v4)
{
	glBegin(GL_POLYGON);
	{
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
		glVertex3fv(v4);
	}
	glEnd();
}

void Graphics::drawObstacle()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glTranslatef(obstacle->position->x, obstacle->position->y, obstacle->position->z);
	glScalef(0.05, 0.05, 0.05);
	mdlviewer_display(obstacle->model);
	glPopMatrix();
}

void Graphics::drawTrap()
{
	glPushMatrix();
	glTranslatef(trap->position->x, trap->position->y, trap->position->z);
	glScalef(1.0, 1.0, trap->height);
	drawCube(obstacle->size);
	glPopMatrix();
}

void Graphics::display(void){
	if (status->loggedIn && status->mainMenu == false) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		setCamera();

		material(slate);
		drawGround(model->texID[0]);

		drawCharacter();
		drawEnemy();
		drawObstacle();
		drawTrap();
		drawDoors();
		// barra de energia para o jogador; testado apenas na terceira pessoa; comentado, ja existe em numeracao no canto superior direito
		//GLfloat c1[3] = { 0.2, 0.8, 0.2 };
		//drawToolTip(0.5, 0.5, 0.67, c1);
		GLfloat c2[3] = { 0.9, 0.1, 0.1 };
		//drawToolTip(0.01, 0.01, (float) enemy->health / 100.0, c2);
		drawToolTip3d(enemy->position->x, enemy->position->y, enemy->position->z + CHARACTER_HEIGHT, enemy->health / enemy->maxHealth, c2);

		drawAxes();
		material(slate);
		glBindTexture(GL_TEXTURE_2D, model->texID[1]);
		drawMaze();
		glBindTexture(GL_TEXTURE_2D, NULL);

		if (status->eixoTranslaccao) {
			// desenha plano de translacÁ„o
			cout << "Translate... " << status->eixoTranslaccao << endl;
			drawDragPlane(status->eixoTranslaccao);
		}

		showScore(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

		drawMiniMap(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		
		if (status->snow) drawEffect();

		if (status->showMapMenu) {
			displayMapList(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}

		displayHealth(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

		glFlush();
		glutSwapBuffers();
	}
	else if (status->mainMenu) {
		displayMainMenu();
	}
	else {
		loginDisplay();
	}
}

void Graphics::drawToolTip3d(float x, float y, float z, float hp, GLfloat *c)
{
	hp = (hp > 1.0 || hp < 0.0) ? 0.0 : hp;


	glDisable(GL_LIGHTING);
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glRotatef(graus(character->dir)+90.0, 0.0, 0.0, 1.0);
		glScalef(0.1, 0.0001, 0.01);
		glColor3f(0.3, 0.3, 0.3);
		drawCube(10);
		glColor3fv(c);
		glTranslatef(0.0, 1.01, 0.0);
		glScalef(0.9, 1.0, 0.5);
		glScalef(hp, 1.0, 1.0);
		drawCube(10);

	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void  Graphics::loginDisplay(void){ 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double w = glutGet(GLUT_WINDOW_WIDTH);
	double h = glutGet(GLUT_WINDOW_HEIGHT);
	
	// switch to 2D for text overlay
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w, w, -h, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glColor3f(0, 1, 0);
	displayMyText("SIGN IN TO PLAY", -100, 400, 0);
	glColor3f(255, 255, 255);
	displayMyText("username -> ENTER -> password -> ENTER", -325, 240, 0);
	
	glColor3f(255, 0, 0);
	displayMyText("Username: ", -250, 140, 0);
	glColor3f(255, 255, 255);
	displayMyText((char*)status->username.c_str(), -50, 140, 0);
	if (status->nextInput) {
		glColor3f(255, 0, 0);
		displayMyText("Password: ", -250, 40, 0);
		glColor3f(255, 255, 255);
		displayMyText((char*)status->passwd.c_str(), -50, 40, 0);
	}
	if (!status->loginErrorMessage.empty()) {
		glColor3f(255, 0, 0);
		displayMyText((char*)status->loginErrorMessage.c_str(), -200, -300, 0);
	}
	glEnable(GL_LIGHTING);
	glutSwapBuffers();
	
}

void Graphics::displayMainMenu() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double width = glutGet(GLUT_WINDOW_WIDTH);
	double height = glutGet(GLUT_WINDOW_HEIGHT);
	// switch to 2D for text overlay
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width, width, -height, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	glColor3f(0.5, 0.5, 0.5);
	string score = "Score: " + to_string(status->score) + " Health: " + to_string(character->health);
	displayMyText((char*)score.c_str(), -width + 10, height - 30, 0);
	glColor3f(0, 1, 0);
	displayMyText("MAIN MENU", -100, 350, 0);
	glColor3f(1.0, 0, 0);
	displayMyText("C - CONTINUE  | N -  NEW GAME", -250, 275, 0);
	displayMyText("1 - WORLDS  |  2- SOUNDS  | 3 - TEXTURES", -350, 200, 0);

	//draw separator line
	glLineWidth(1.0);
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	glVertex3f(-580, 125, 0.0);
	glVertex3f(580, 125, 0);
	glEnd();

	if (status->showMapMenu) {
		displayMyText("1 - Mundo 1", -400, 0, 0);
		displayMyText("2 - Mundo 2", -400, -75, 0);
		string back = status->soundsList.size() + "0 - Go back";
		displayMyText((char*)back.c_str(), -400, -150, 0);
	}
	else if (status->showSoundsMenu) {
		if (status->soundsList.empty()) {
			ServicesHandler *handler = new ServicesHandler();
			//status->texturesList = handler->getSoundsList();
			status->soundsList.push_back("Sound 1");
			status->soundsList.push_back("Sound 2");
		}
		int posY = 0;
		for (int i = 0; i < status->soundsList.size(); i++) {
			string item = (i + 1) + " - " + status->soundsList.at(i);
			displayMyText((char*)item.c_str(), -200, posY, 0);
			posY += -75;
		}
		string back = status->soundsList.size() + "Go back";
		displayMyText((char*)back.c_str(), -200, posY, 0);
	}
	else if (status->showTexturesMenu) {
		if (status->texturesList.empty()) {
			ServicesHandler *handler = new ServicesHandler();
			//status->texturesList = handler->getTexturesList();
			status->texturesList.push_back("Texture 1");
			status->texturesList.push_back("Texture 2");
		}
		int posY = 0;
		for (int i = 0; i < status->texturesList.size(); i++) {
			string item = (i + 1) + " - " + status->texturesList.at(i);
			displayMyText((char*)item.c_str(), -200, posY, 0);
			posY += -75;
		}
		string back = status->soundsList.size() + "Go back";
		displayMyText((char*)back.c_str(), -200, posY, 0);
	}

	glEnable(GL_LIGHTING);
	glutSwapBuffers();
}

void Graphics::displayMyText(char *string, float x, float y, float z) {
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
	}

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
	if (status->loggedIn) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		Graphics::setProjection(0, 0, GL_FALSE);
		glMatrixMode(GL_MODELVIEW);
	}
    
}
void Graphics::createTextures(GLuint texID[]) {
    char *image;
    int w, h, bpp;
    
    glGenTextures(2,texID);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if(	read_JPEG_file(FLOOR_TEXTURE, &image, &w, &h, &bpp))
    {
        glBindTexture(GL_TEXTURE_2D, texID[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
    }else{
        printf("Texture %s not Found\n",FLOOR_TEXTURE);
        exit(0);
    }

	if (read_JPEG_file("Wall.jpg", &image, &w, &h, &bpp))
	{
		// Create MipMapped Texture
		glBindTexture(GL_TEXTURE_2D, texID[1]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
	}

	else
	{
		printf("Texture %s not Found\n", "Wall.jpg");
		exit(0);
	}
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void Graphics::drawToolTip(float x, float y, float hp, GLfloat *c)
{
	float width = 180.0;
	float height = 18.0;
	hp = (hp > 1.0 || hp < 0.0) ? 0.0 : hp;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	glClear(GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	{	// TODO: posicionar a barra de energia sobre o inimigo; para ja fica posicionada nas coordenadas X,Y
		//glTranslatef(-width / 2.0, -height / 2.0, 0.0);
		glTranslatef(x / 1.0 * ((float)glutGet(GLUT_WINDOW_WIDTH)), y / 1.0 * ((float)glutGet(GLUT_WINDOW_HEIGHT)), 0.0);
		glBegin(GL_QUADS);
		{
			glColor3f(0.0, 0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glVertex2f(width, 0.0);
			glVertex2f(width, height);
			glVertex2f(0.0, height);

			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(1.0, 1.0);
			glVertex2f(width - 1.0, 1.0);
			glVertex2f(width - 1.0, height - 1.0);
			glVertex2f(1.0, height - 1.0);

			glColor3f(0.0, 0.0, 0.0);
			glVertex2f(2.0, 2.0);
			glVertex2f(width - 2.0, 2.0);
			glVertex2f(width - 2.0, height - 2.0);
			glVertex2f(2.0, height - 2.0);

			glColor3fv(c);
			glVertex2f(3.0, 3.0);
			glVertex2f((width - 6.0) * hp + 3.0, 3.0);
			glVertex2f((width - 6.0) * hp + 3.0, height - 3.0);
			glVertex2f(3.0, height - 3.0);
		}
		glEnd();
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	Graphics::myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
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

void Graphics::displayMapList(int width, int height) {

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-100, 100, -100, 100, -100, 100);
	glOrtho(-width, width, -height, height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int posX = -width + 50, gap = 0;

	vector<string> worlds;
	worlds.push_back("Mundo 1");
	worlds.push_back("Mundo 2");

	Graphics::material(brass);
	for (int i = 0; i < worlds.size(); i++) {
		gap += 50;
		string str = to_string(i + 1) + " - " + worlds.at(i);
		Graphics::drawText(str, posX, height - gap);
	}

	Graphics::myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void Graphics::displayHealth(int width, int height){
	glViewport(width * 0.75, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width, width, -height, height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int posX = -width + 50, gap = 0;

	material(brass);
	gap += 50;
	string str = "Health: " + to_string(character->health);
	drawText(str, posX, height - gap);
	

	myReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
void Graphics::showScore(int width, int height) {
	glViewport(width * 0.45, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width, width, -height, height, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	material(brass);
	string score = "Score: " + to_string(status->score);
	Graphics::drawText(score, -width + 150, height - 50);
}

void Graphics::drawText(string src, int posX, int posY)
{
	char text[50];
	sprintf(text, src.c_str());
	glColor3f(0, 0, 0);
	glRasterPos2i(posX, posY);
	for (int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}

