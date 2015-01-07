#include "Maze.h"
#include "MainCharacter.h"
#include "Login.h"
#include "Status.h"
#include "MapsReceiver.h"
#include "EnemyCharacter.h"

#define MAP_COOR_SCALE 5

Model *model = new Model();
Status *status = new Status();
MainCharacter *character = new MainCharacter();
EnemyCharacter *enemy = new EnemyCharacter();
int counter = 0;
double lightComponent, factor = 3.0;
void Maze::Timer(int value) {
	counter++;
	lightComponent = cos((counter / 1000.0) * (2.0 * M_PI)) / factor + (factor - 1.0) / factor;
	GLfloat light[] = { lightComponent, lightComponent, lightComponent, 1.0 };
	//status->main_light = (GLfloat*)light;
	if (counter > 1000) {
		counter = 0;
	}

    ALint state;
    glutTimerFunc(status->timer, Timer, 0);
    alGetSourcei(status->source, AL_SOURCE_STATE, &state);
    if (status->tecla_o)
    {
        if (state != AL_PLAYING)
            alSourcePlay(status->source);
        else
            alSourceStop(status->source);   
    }

	GLfloat nx = 0, ny = 0;
	GLboolean walking = GL_FALSE;

	if (status->up){
		nx = character->position->x + cosf(character->dir) * CHARACTER_LENGTH * character->vel;
		ny = character->position->y + sinf(character->dir) * CHARACTER_WIDTH * character->vel;

		if (!Maze::Collision((GLfloat)nx, (GLfloat)ny, character->position->z)){
			character->position->x = nx;
			character->position->y = ny;
			walking = GL_TRUE;
		}
	}

	else if (status->down){
		nx = character->position->x - cosf(character->dir) * CHARACTER_LENGTH * character->vel;
		ny = character->position->y - sinf(character->dir) * CHARACTER_WIDTH * character->vel;
		
		if (!Maze::Collision((GLfloat)nx, (GLfloat)ny, character->position->z)){
			character->position->x = nx;
			character->position->y = ny;
			walking = GL_TRUE;
		}
	}
	if (status->left){
		character->dir += rad(2);
		status->camera->dir_long = character->dir;
	}
	else if (status->right){
		character->dir -= rad(2);
		status->camera->dir_long = character->dir;
	}

	if (walking && character->homer.GetSequence() != 3){
		character->homer.SetSequence(3);

	}
	else if (!walking && character->homer.GetSequence() == 3)
	{
		character->homer.SetSequence(0);
	}

	if (status->mapfile == "quarto1.grafo")
	{
		if (character->position->x > 0.331 && character->position->x<11.43 && character->position->y>292.529 && character->position->y < 292.605)
		{
			status->mapfile = "quarto2.grafo";
		}
		/*else if (character->position->x &&character->position->y){
			status->mapfile = "quarto3.grafo";
		}*/
	}
	else if (status->mapfile == "quarto2.grafo")
	{
		if (character->position->x>-137.506 && character->position->x<-134.058 && character->position->y>-266.794 && character->position->y<-256.512){
			status->mapfile = "quarto1.grafo";
		}
	}
	//else {
	//	if (character->position->x &&character->position->y){
	//		status->mapfile = "quarto1.grafo";
	//	}
	//}

    glutPostRedisplay();
}

bool Maze::Collision(GLfloat nx, GLfloat ny, GLfloat nz) {
	//cout << "POS(X,Y): " << nx << ", " << ny << endl;

	for (int i = 0; i<numArcos; i++){
		No ni = nos[arcos[i].noi];
		No nf = nos[arcos[i].nof];

		// colide with node
		if (pow(nx - (ni.x * 5), 2) + pow(ny - (ni.y * 5), 2) <= pow((ni.largura / 2) * 5, 2) && ni.z + nz > 1.0) return true;
		if (pow(nx - (nf.x * 5), 2) + pow(ny - (nf.y * 5), 2) <= pow((nf.largura / 2) * 5, 2) && nf.z + nz > 1.0) return true;

		// collide with vertical wall
		if (ni.x == nf.x)
			if ((ny >= (ni.y * 5) && ny <= (nf.y * 5)) || (ny <= (ni.y * 5) && ny >= (nf.y * 5)))
				if (nx <= 5.0 * (ni.x + (ni.largura * 0.5)) && nx >= 5.0 * (ni.x - (ni.largura * 0.5))) return true;

		// collide with horizontal wall
		if (ni.y == nf.y)
			if ((nx >= (ni.x * 5) && nx <= (nf.x * 5)) || (nx <= (ni.x * 5) && nx >= (nf.x * 5)))
				if (ny <= 5.0 * (ni.y + (ni.largura * 0.5)) && ny >= 5.0 * (ni.y - (ni.largura * 0.5))) return true;

		// collide with diagonal wall
	}
	return false;
}


void Maze::Launch(int argc, char **argv){

	/*Login *login = new Login();
	if (login->ShowSignInMenu()) {
		MapsReceiver *receiver = new MapsReceiver();
		string mapName = receiver->chooseMap();
		if (!mapName.empty()) {
			//set choosen map
			status->mapfile = mapName + ".grafo";*/
			glutInit(&argc, argv);

			/* need both double buffering and z buffer */

			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutInitWindowSize(640, 480);
			glutCreateWindow("OpenGL");
			glutReshapeFunc(Graphics::myReshape);
			glutDisplayFunc(Graphics::display);
			glutKeyboardFunc(Keyboard::keyboard);
			glutSpecialUpFunc(Keyboard::specialKeyUp);
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

			alutInit(&argc, argv);
			status->InitAudio();

			leGrafo(status->mapfile);

			Keyboard::help();

			glutMainLoop();
		//}

		
	//}
	
}
