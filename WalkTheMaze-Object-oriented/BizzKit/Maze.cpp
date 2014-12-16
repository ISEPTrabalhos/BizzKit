#include "Maze.h"
#include "MainCharacter.h"

Model *model = new Model();
Status *status = new Status();
MainCharacter *character = new MainCharacter();

void Maze::Timer(int value) {
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


void Maze::Launch(int argc, char **argv){
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("OpenGL");
	glutReshapeFunc(Graphics::myReshape);
	glutDisplayFunc(Graphics::display);
	glutKeyboardFunc(Keyboard::keyboard);
	glutSpecialFunc(Keyboard::Special);
	glutMouseFunc(Mouse::mouse);
    glutTimerFunc(status->timer, Timer, 0);

	GLfloat LuzAmbiente[] = { 0.5, 0.5, 0.5, 0.0 };
    Graphics::createTextures(model->texID);
    
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

	Keyboard::help();

	glutMainLoop();
}
