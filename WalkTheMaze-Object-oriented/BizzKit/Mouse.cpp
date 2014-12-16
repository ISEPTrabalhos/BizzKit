#include "Mouse.h"

extern Status *status;
extern Model *model;

void Mouse::motionRotate(int x, int y){
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

void Mouse::motionZoom(int x, int y){
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

void Mouse::motionDrag(int x, int y){
    GLuint buffer[100];
    GLint vp[4];
    GLdouble proj[16], mv[16];
    int n;
    GLdouble newx, newy, newz;
    
    glSelectBuffer(100, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // guarda a projecÁ„o
    glLoadIdentity();
    Graphics::setProjection(x, y, GL_TRUE);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Graphics::setCamera();
    Graphics::drawDragPlane(status->eixoTranslaccao);
    
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
    
    
    glMatrixMode(GL_PROJECTION); //repıe matriz projecÁ„o
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int Mouse::picking(int x, int y){
    int i, n, objid = 0;
    double zmin = 10.0;
    GLuint buffer[100], *ptr;
    
    glSelectBuffer(100, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // guarda a projecÁ„o
    glLoadIdentity();
    Graphics::setProjection(x, y, GL_TRUE);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Graphics::setCamera();
    Graphics::drawAxes();
    
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
            ptr += 3 + ptr[0]; // ptr[0] contem o n˙mero de nomes (normalmente 1); 3 corresponde a numnomes, zmin e zmax
        }
    }
    
    
    glMatrixMode(GL_PROJECTION); //repıe matriz projecÁ„o
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    return objid;
}

void Mouse::mouse(int btn, int state, int x, int y){
    switch (btn) {
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN){
                status->xMouse = x;
                status->yMouse = y;
                if (glutGetModifiers() & GLUT_ACTIVE_CTRL)
                    glutMotionFunc(Mouse::motionZoom);
                else
                    glutMotionFunc(Mouse::motionRotate);
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
                    glutMotionFunc(Mouse::motionDrag);
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
