#include "Maze.h"

Model *model = new Model();
Status *status = new Status();

void Maze::putLights(GLfloat* diffuse){
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

void Maze::setCamera(){
	Vertice eye;
	eye[0] = status->camera->center[0] + status->camera->dist*cos(status->camera->dir_long)*cos(status->camera->dir_lat);
	eye[1] = status->camera->center[1] + status->camera->dist*sin(status->camera->dir_long)*cos(status->camera->dir_lat);
	eye[2] = status->camera->center[2] + status->camera->dist*sin(status->camera->dir_lat);

	if (status->light){
		gluLookAt(eye[0], eye[1], eye[2], status->camera->center[0], status->camera->center[1], status->camera->center[2], 0, 0, 1);
		Maze::putLights((GLfloat*)white_light);
	}
	else{
		Maze::putLights((GLfloat*)white_light);
		gluLookAt(eye[0], eye[1], eye[2], status->camera->center[0], status->camera->center[1], status->camera->center[2], 0, 0, 1);
	}
}

void Maze::display(void){


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Maze::setCamera();

	Graphics::material(slate);
    Graphics::drawGround(model->texID[0]);


	Graphics::drawAxes(status, model);

	Graphics::drawMaze(status);

	if (status->eixoTranslaccao) {
		// desenha plano de translacção
		cout << "Translate... " << status->eixoTranslaccao << endl;
		Graphics::drawDragPlane(status ,status->eixoTranslaccao);

	}

	glFlush();
	glutSwapBuffers();

}






void Maze::setProjection(int x, int y, GLboolean picking){
	glLoadIdentity();
	if (picking) { // se está no modo picking, lê viewport e define zona de picking
		GLint vport[4];
		glGetIntegerv(GL_VIEWPORT, vport);
		gluPickMatrix(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 4, 4, vport); // Inverte o y do rato para corresponder à jana
	}

	gluPerspective(status->camera->fov, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1, 500);

}

void Maze::myReshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	Maze::setProjection(0, 0, GL_FALSE);
	glMatrixMode(GL_MODELVIEW);
}


void Maze::motionRotate(int x, int y){
#define DRAG_SCALE	0.01
	double lim = M_PI / 2 - 0.1;
	status->camera->dir_long += (status->xMouse - x)*DRAG_SCALE;
	status->camera->dir_lat -= (status->yMouse - y)*DRAG_SCALE*0.5;
	if (status->camera->dir_lat>lim)
		status->camera->dir_lat = lim;
	else
	if (status->camera->dir_lat<-lim)
		status->camera->dir_lat = -lim;
	status->xMouse = x;
	status->yMouse = y;
	glutPostRedisplay();
}

void Maze::motionZoom(int x, int y){
#define ZOOM_SCALE	0.5
	status->camera->dist -= (status->yMouse - y)*ZOOM_SCALE;
	if (status->camera->dist<5)
		status->camera->dist = 5;
	else
	if (status->camera->dist>200)
		status->camera->dist = 200;
	status->yMouse = y;
	glutPostRedisplay();
}

void Maze::motionDrag(int x, int y){
	GLuint buffer[100];
	GLint vp[4];
	GLdouble proj[16], mv[16];
	int n;
	GLdouble newx, newy, newz;

	glSelectBuffer(100, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // guarda a projecção
	glLoadIdentity();
	Maze::setProjection(x, y, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Maze::setCamera();
	Graphics::drawDragPlane(status, status->eixoTranslaccao);

	n = glRenderMode(GL_RENDER);
	if (n > 0) {
		glGetIntegerv(GL_VIEWPORT, vp);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		glGetDoublev(GL_MODELVIEW_MATRIX, mv);
		gluUnProject(x, glutGet(GLUT_WINDOW_HEIGHT) - y, (double)buffer[2] / UINT_MAX, mv, proj, vp, &newx, &newy, &newz);
		printf("Novo x:%lf, y:%lf, z:%lf\n\n", newx, newy, newz);
		switch (status->eixoTranslaccao) {
		case EIXO_X:
			status->eixo[0] = newx;
			//Maze::status->eixo[1]=newy;
			break;
		case EIXO_Y:
			status->eixo[1] = newy;
			//Maze::status->eixo[2]=newz;
			break;
		case EIXO_Z:
			//Maze::status->eixo[0]=newx;
			status->eixo[2] = newz;
			break;
		}
		glutPostRedisplay();
	}


	glMatrixMode(GL_PROJECTION); //repõe matriz projecção
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int Maze::picking(int x, int y){
	int i, n, objid = 0;
	double zmin = 10.0;
	GLuint buffer[100], *ptr;

	glSelectBuffer(100, buffer);
	glRenderMode(GL_SELECT);
	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // guarda a projecção
	glLoadIdentity();
	setProjection(x, y, GL_TRUE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Maze::setCamera();
	Graphics::drawAxes(status, model);

	n = glRenderMode(GL_RENDER);
	if (n > 0)
	{
		ptr = buffer;
		for (i = 0; i < n; i++)
		{
			if (zmin >(double) ptr[1] / UINT_MAX) {
				zmin = (double)ptr[1] / UINT_MAX;
				objid = ptr[3];
			}
			ptr += 3 + ptr[0]; // ptr[0] contem o número de nomes (normalmente 1); 3 corresponde a numnomes, zmin e zmax
		}
	}


	glMatrixMode(GL_PROJECTION); //repõe matriz projecção
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	return objid;
}
void Maze::mouse(int btn, int state, int x, int y){
	switch (btn) {
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN){
			status->xMouse = x;
			status->yMouse = y;
			if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
				glutMotionFunc(Maze::motionZoom);
			else
				glutMotionFunc(Maze::motionRotate);
			cout << "Left down\n";
		}
		else{
			glutMotionFunc(NULL);
			cout << "Left up\n";
		}
		break;
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			status->eixoTranslaccao = picking(x, y);
			if (status->eixoTranslaccao)
				glutMotionFunc(Maze::motionDrag);
			cout << "Right down - objecto:" << status->eixoTranslaccao << endl;
		}
		else{
			if (status->eixoTranslaccao != 0) {
				status->camera->center[0] = status->eixo[0];
				status->camera->center[1] = status->eixo[1];
				status->camera->center[2] = status->eixo[2];
				glutMotionFunc(NULL);
				status->eixoTranslaccao = 0;
				glutPostRedisplay();
			}
			cout << "Right up\n";
		}
		break;
	}
}

void Maze::keyboard(unsigned char key, int x, int y){

	switch (key){
	case 27:
		exit(0);
		break;
	case 'h':
	case 'H':
		Maze::help();
		break;
	case 'l':
	case 'L':
		if (status->lightViewer)
			status->lightViewer = 0;
		else
			status->lightViewer = 1;
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, status->lightViewer);
		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		status->light = !status->light;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		glEnable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		if (glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);
		glutPostRedisplay();
		break;
	case 'n':
	case 'N':
		status->apresentaNormais = !status->apresentaNormais;
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		status = new Status();
		model = new Model();
		glutPostRedisplay();
		break;
    case 'o':
    case 'O':
        status->tecla_o = !status->tecla_o;
        break;
	}
}

void Maze::Special(int key, int x, int y){

	switch (key){
	case GLUT_KEY_F1:
		gravaGrafo();
		break;
	case GLUT_KEY_F2:
		leGrafo();
		glutPostRedisplay();
		break;

	case GLUT_KEY_F6:
		numNos = numArcos = 0;
		addNo(criaNo(0, 10, 0));  // 0
		addNo(criaNo(0, 5, 0));  // 1
		addNo(criaNo(-5, 5, 0));  // 2
		addNo(criaNo(5, 5, 0));  // 3
		addNo(criaNo(-5, 0, 0));  // 4
		addNo(criaNo(5, 0, 0));  // 5
		addNo(criaNo(-5, -5, 0));  // 6
		addArco(criaArco(0, 1, 1, 1));  // 0 - 1
		addArco(criaArco(1, 2, 1, 1));  // 1 - 2
		addArco(criaArco(1, 3, 1, 1));  // 1 - 3
		addArco(criaArco(2, 4, 1, 1));  // 2 - 4
		addArco(criaArco(3, 5, 1, 1));  // 3 - 5
		addArco(criaArco(4, 5, 1, 1));  // 4 - 5
		addArco(criaArco(4, 6, 1, 1));  // 4 - 6
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		status->camera->dist -= 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		status->camera->dist += 1;
		glutPostRedisplay();
		break;
	}
}

void Maze::help(void){
	printf("\n\nDesenho de um labirinto a partir de um grafo\n");
	printf("h,H - Ajuda \n");
	printf("i,I - Reset dos Valores \n");
	printf("******* Diversos ******* \n");
	printf("l,L - Alterna o calculo luz entre Z e eye (GL_LIGHT_MODEL_LOCAL_VIEWER)\n");
	printf("k,K - Alerna luz de camera com luz global \n");
	printf("s,S - PolygonMode Fill \n");
	printf("w,W - PolygonMode Wireframe \n");
	printf("p,P - PolygonMode Point \n");
	printf("c,C - Liga/Desliga Cull Face \n");
	printf("n,N - Liga/Desliga apresentação das normais \n");
	printf("******* grafos ******* \n");
	printf("F1  - Grava grafo do ficheiro \n");
	printf("F2  - Lê grafo para ficheiro \n");
	printf("F6  - Cria novo grafo\n");
	printf("******* Camera ******* \n");
	printf("Botão esquerdo - Arrastar os eixos (centro da camera)\n");
	printf("Botão direito  - Rodar camera\n");
	printf("Botão direito com CTRL - Zoom-in/out\n");
	printf("PAGE_UP, PAGE_DOWN - Altera distância da camara \n");
	printf("ESC - Sair\n");
}

#define FLOOR_TEXTURE "floor.jpg"

extern "C" int read_JPEG_file(char *, char **, int *, int *, int *);

void Maze::createTextures(GLuint texID[])
{
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

void Maze::Launch(int argc, char **argv){
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("OpenGL");
	glutReshapeFunc(Maze::myReshape);
	glutDisplayFunc(Maze::display);
	glutKeyboardFunc(Maze::keyboard);
	glutSpecialFunc(Maze::Special);
	glutMouseFunc(Maze::mouse);
    glutTimerFunc(status->timer, Timer, 0);

	GLfloat LuzAmbiente[] = { 0.5, 0.5, 0.5, 0.0 };
    Maze::createTextures(model->texID);
    
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_SMOOTH); /*enable smooth shading */
	glEnable(GL_LIGHTING); /* enable lighting */
	glEnable(GL_DEPTH_TEST); /* enable z buffer */
	glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

	glDepthFunc(GL_LESS);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, status->lightViewer);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	model->quad = gluNewQuadric();
	gluQuadricDrawStyle(model->quad, GLU_FILL);
	gluQuadricNormals(model->quad, GLU_OUTSIDE);

	leGrafo();

	Maze::help();

	glutMainLoop();
}

void Maze::Timer(int value)
{
    ALint state;
    glutTimerFunc(status->timer, Timer, 0);
    alGetSourcei(status->source, AL_SOURCE_STATE, &state);
    if (status->tecla_o)
    {
        if (state != AL_PLAYING)
            alSourcePlay(status->source);
        else{
            if (state==AL_PLAYING)
                alSourceStop(status->source);
        }
        
    }
    glutPostRedisplay();
}
