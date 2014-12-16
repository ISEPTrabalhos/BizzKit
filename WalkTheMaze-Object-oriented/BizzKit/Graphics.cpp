#include "Graphics.h"

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

void Graphics::drawWall(Status *status, GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf){
	GLdouble v1[3], v2[3], cross[3];
	GLdouble length;
	v1[0] = xf - xi;
	v1[1] = yf - yi;
	v1[2] = 0;
	v2[0] = 0;
	v2[1] = 0;
	v2[2] = 1;
	Graphics::CrossProduct(v1, v2, cross);
	//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
	length = Graphics::VectorNormalize(cross);
	//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);

	Graphics::material(emerald);
	glBegin(GL_QUADS);
	glNormal3dv(cross);
	glVertex3f(xi, yi, zi);
	glVertex3f(xf, yf, zf + 0);
	glVertex3f(xf, yf, zf + 1);
	glVertex3f(xi, yi, zi + 1);
	glEnd();

	if (status->apresentaNormais) {
		drawNormal(xi, yi, zi, cross, emerald);
		drawNormal(xf, yf, zf, cross, emerald);
		drawNormal(xf, yf, zf + 1, cross, emerald);
		drawNormal(xi, yi, zi + 1, cross, emerald);
	}
}

void Graphics::drawPlatform(Status *status, GLfloat xi, GLfloat yi, GLfloat zi, GLfloat xf, GLfloat yf, GLfloat zf, int orient){
	GLdouble v1[3], v2[3], cross[3];
	GLdouble length;
	v1[0] = xf - xi;
	v1[1] = 0;
	v2[0] = 0;
	v2[1] = yf - yi;

	switch (orient) {
	case NORTE_SUL:
		v1[2] = 0;
		v2[2] = zf - zi;
		Graphics::CrossProduct(v1, v2, cross);
		//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
		length = Graphics::VectorNormalize(cross);
		//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);

		Graphics::material(red_plastic);
		glBegin(GL_QUADS);
		glNormal3dv(cross);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zi);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zf);
		glEnd();
		if (status->apresentaNormais) {
			Graphics::drawNormal(xi, yi, zi, cross, red_plastic);
			Graphics::drawNormal(xf, yi, zi, cross, red_plastic);
			Graphics::drawNormal(xf, yf, zf, cross, red_plastic);
			Graphics::drawNormal(xi, yi, zf, cross, red_plastic);
		}
		break;
	case ESTE_OESTE:
		v1[2] = zf - zi;
		v2[2] = 0;
		Graphics::CrossProduct(v1, v2, cross);
		//printf("cross x=%lf y=%lf z=%lf",cross[0],cross[1],cross[2]);
		length = VectorNormalize(cross);
		//printf("Normal x=%lf y=%lf z=%lf length=%lf\n",cross[0],cross[1],cross[2]);
		Graphics::material(red_plastic);
		glBegin(GL_QUADS);
		glNormal3dv(cross);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zf);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zi);
		glEnd();
		if (status->apresentaNormais) {
			Graphics::drawNormal(xi, yi, zi, cross, red_plastic);
			Graphics::drawNormal(xf, yi, zf, cross, red_plastic);
			Graphics::drawNormal(xf, yf, zf, cross, red_plastic);
			Graphics::drawNormal(xi, yi, zi, cross, red_plastic);
		}
		break;
	default:
		cross[0] = 0;
		cross[1] = 0;
		cross[2] = 1;
		Graphics::material(azul);
		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glVertex3f(xi, yi, zi);
		glVertex3f(xf, yi, zf);
		glVertex3f(xf, yf, zf);
		glVertex3f(xi, yf, zi);
		glEnd();
		if (status->apresentaNormais) {
			Graphics::drawNormal(xi, yi, zi, cross, azul);
			Graphics::drawNormal(xf, yi, zf, cross, azul);
			Graphics::drawNormal(xf, yf, zf, cross, azul);
			Graphics::drawNormal(xi, yi, zi, cross, azul);
		}
		break;
	}
}

void Graphics::drawNode(Status *status, int no){
	GLboolean norte, sul, este, oeste;
	GLfloat larguraNorte, larguraSul, larguraEste, larguraOeste;
	Arco arco = arcos[0];
	No *noi = &nos[no], *nof;
	norte = sul = este = oeste = GL_TRUE;
	Graphics::drawPlatform(status, nos[no].x - 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z, nos[no].x + 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z, PLANO);
	for (int i = 0; i<numArcos; arco = arcos[++i]){
		if (arco.noi == no)
			nof = &nos[arco.nof];
		else
		if (arco.nof == no)
			nof = &nos[arco.noi];
		else
			continue;
		if (noi->x == nof->x)
		if (noi->y<nof->y){
			norte = GL_FALSE;
			larguraNorte = arco.largura;
		}
		else{
			sul = GL_FALSE;
			larguraSul = arco.largura;
		}
		else
		if (noi->y == nof->y)
		if (noi->x<nof->x){
			oeste = GL_FALSE;
			larguraOeste = arco.largura;
		}
		else{
			este = GL_FALSE;
			larguraEste = arco.largura;
		}
		else
			cout << "Arco dioagonal: " << arco.noi << " " << arco.nof << endl;
		if (norte && sul && este && oeste)
			return;
	}
	if (norte)
		Graphics::drawWall(status, nos[no].x - 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z, nos[no].x + 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z);
	else
	if (larguraNorte < noi->largura){
		Graphics::drawWall(status, nos[no].x - 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z, nos[no].x - 0.5*larguraNorte, nos[no].y + 0.5*noi->largura, nos[no].z);
		Graphics::drawWall(status, nos[no].x + 0.5*larguraNorte, nos[no].y + 0.5*noi->largura, nos[no].z, nos[no].x + 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z);
	}
	if (sul)
		Graphics::drawWall(status, nos[no].x + 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z, nos[no].x - 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z);
	else
	if (larguraSul < noi->largura){
		Graphics::drawWall(status, nos[no].x + 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z, nos[no].x + 0.5*larguraSul, nos[no].y - 0.5*noi->largura, nos[no].z);
		Graphics::drawWall(status, nos[no].x - 0.5*larguraSul, nos[no].y - 0.5*noi->largura, nos[no].z, nos[no].x - 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z);
	}
	if (este)
		Graphics::drawWall(status, nos[no].x - 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z, nos[no].x - 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z);
	else
	if (larguraEste < noi->largura){
		Graphics::drawWall(status, nos[no].x - 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z, nos[no].x - 0.5*noi->largura, nos[no].y - 0.5*larguraEste, nos[no].z);
		Graphics::drawWall(status, nos[no].x - 0.5*noi->largura, nos[no].y + 0.5*larguraEste, nos[no].z, nos[no].x - 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z);
	}
	if (oeste)
		Graphics::drawWall(status, nos[no].x + 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z, nos[no].x + 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z);
	else
	if (larguraOeste < noi->largura){
		Graphics::drawWall(status, nos[no].x + 0.5*noi->largura, nos[no].y + 0.5*noi->largura, nos[no].z, nos[no].x + 0.5*noi->largura, nos[no].y + 0.5*larguraOeste, nos[no].z);
		Graphics::drawWall(status, nos[no].x + 0.5*noi->largura, nos[no].y - 0.5*larguraOeste, nos[no].z, nos[no].x + 0.5*noi->largura, nos[no].y - 0.5*noi->largura, nos[no].z);
	}
}


void Graphics::drawArc(Status *status, Arco arco){
	No *noi, *nof;

	if (nos[arco.noi].x == nos[arco.nof].x){
		// arco vertical
		if (nos[arco.noi].y<nos[arco.nof].y){
			noi = &nos[arco.noi];
			nof = &nos[arco.nof];
		}
		else{
			nof = &nos[arco.noi];
			noi = &nos[arco.nof];
		}

		Graphics::drawPlatform(status, noi->x - 0.5*arco.largura, noi->y + 0.5*noi->largura, noi->z, nof->x + 0.5*arco.largura, nof->y - 0.5*nof->largura, nof->z, NORTE_SUL);
		Graphics::drawWall(status, noi->x - 0.5*arco.largura, noi->y + 0.5*noi->largura, noi->z, nof->x - 0.5*arco.largura, nof->y - 0.5*nof->largura, nof->z);
		Graphics::drawWall(status, nof->x + 0.5*arco.largura, nof->y - 0.5*nof->largura, nof->z, noi->x + 0.5*arco.largura, noi->y + 0.5*noi->largura, noi->z);
	}
	else{
		if (nos[arco.noi].y == nos[arco.nof].y){
			//arco horizontal
			if (nos[arco.noi].x<nos[arco.nof].x){
				noi = &nos[arco.noi];
				nof = &nos[arco.nof];
			}
			else{
				nof = &nos[arco.noi];
				noi = &nos[arco.nof];
			}
			Graphics::drawPlatform(status, noi->x + 0.5*noi->largura, noi->y - 0.5*arco.largura, noi->z, nof->x - 0.5*nof->largura, nof->y + 0.5*arco.largura, nof->z, ESTE_OESTE);
			Graphics::drawWall(status, noi->x + 0.5*noi->largura, noi->y + 0.5*arco.largura, noi->z, nof->x - 0.5*nof->largura, nof->y + 0.5*arco.largura, nof->z);
			Graphics::drawWall(status, nof->x - 0.5*nof->largura, nof->y - 0.5*arco.largura, nof->z, noi->x + 0.5*noi->largura, noi->y - 0.5*arco.largura, noi->z);
		}
		else{
			cout << "arco diagonal... não será desenhado";
		}
	}
}

void Graphics::drawMaze(Status *status){
	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	glScalef(5, 5, 5);
	Graphics::material(red_plastic);
	for (int i = 0; i<numNos; i++){
		glPushMatrix();
		Graphics::material(preto);
		glTranslatef(nos[i].x, nos[i].y, nos[i].z + 0.25);
		glutSolidCube(0.5);
		glPopMatrix();
		Graphics::drawNode(status, i);
	}
	Graphics::material(emerald);
	for (int i = 0; i<numArcos; i++)
		Graphics::drawArc(status, arcos[i]);
	glPopMatrix();
}

void Graphics::drawAxis(Model *model){
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

void Graphics::drawDragPlane(Status *status, int eixo){
	glPushMatrix();
	glTranslated(status->eixo[0], status->eixo[1], status->eixo[2]);
	switch (eixo) {
	case EIXO_Y:
		if (fabs(status->camera->dir_lat)<M_PI / 4)
			glRotatef(-90, 0, 0, 1);
		else
			glRotatef(90, 1, 0, 0);
		material(red_plastic);
		break;
	case EIXO_X:
		if (fabs(status->camera->dir_lat)>M_PI / 6)
			glRotatef(90, 1, 0, 0);
		material(azul);
		break;
	case EIXO_Z:
		if (fabs(cos(status->camera->dir_long))>0.5)
			glRotatef(90, 0, 0, 1);

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

void Graphics::drawAxes(Status *status, Model *model){

	glPushMatrix();
	glTranslated(status->eixo[0], status->eixo[1], status->eixo[2]);
	Graphics::material(emerald);
	glPushName(EIXO_Z);
	Graphics::drawAxis(model);
	glPopName();
	glPushName(EIXO_Y);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	Graphics::material(red_plastic);
	Graphics::drawAxis(model);
	glPopMatrix();
	glPopName();
	glPushName(EIXO_X);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	Graphics::material(azul);
	Graphics::drawAxis(model);
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
