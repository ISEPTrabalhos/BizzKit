#include "Maze.h"
#include "MainCharacter.h"
#include "Login.h"
#include "Status.h"
#include "MapsReceiver.h"
#include "EnemyCharacter.h"
#include "Obstacle.h"

#define MAP_COOR_SCALE 5
#define GAP_CLIMB 0.1

Model *model;
Status *status;
MainCharacter *character;
EnemyCharacter *enemy;
Obstacle *obstacle;

int counter = 0;
double lightComponent, factor = 3.0, duration = 10000.0; //change duration to increase/decrease effect tim

void Maze::Timer(int value) {
	if (status->daynight) {
		counter++;
		lightComponent = cos((counter / duration) * (2.0 * M_PI)) / factor + (factor - 1.0) / factor;
		GLfloat light[] = { lightComponent, lightComponent, lightComponent, 1.0 };
		//status->main_light = (GLfloat*)light;
		if (counter > duration) {
			counter = 0;
		}
	}

    glutTimerFunc(status->timer, Timer, 0);


	if (status->tecla_o) status->background_music->toggle();

	GLfloat nx = 0, ny = 0, z = character->position->z;


	if (status->up){
		if (Walk(1)) {
			nx = character->position->x + character->vel * cosf(character->dir);
			ny = character->position->y + character->vel * sinf(character->dir);
			character->position->x = nx;
			character->position->y = ny;
			character->position->z = CHARACTER_HEIGHT * 0.5;
			status->walking = GL_TRUE;
			
			//	Check if the character has fallen and drains some life
			if (character->position->z - z < -0.5)
				character->health -= 10;
		}
	}
	else if (status->down){
		if (Walk(-1)) {
			nx = character->position->x - character->vel * cosf(character->dir);
			ny = character->position->y - character->vel * sinf(character->dir);
			character->position->x = nx;
			character->position->y = ny;
			character->position->z = CHARACTER_HEIGHT * 0.5;
			status->walking = GL_TRUE;

			//	Check if the character has fallen and drains some life
			if (character->position->z - z < -0.5)
				character->health -= 10;
		
		}
	}
	else
		status->walking = GL_FALSE;

	if (status->left){
		character->dir += rad(2);
		status->camera->dir_long = character->dir;
	}
	else if (status->right){
		character->dir -= rad(2);
		status->camera->dir_long = character->dir;
	}

	if (status->walking && character->homer.GetSequence() != 3){
		character->homer.SetSequence(3);

	}
	else if (!status->walking && character->homer.GetSequence() == 3)
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

	if (CollisionEnemy(character->position->x, character->position->y, character->position->z))
	{
		character->health = 0;
	}

    glutPostRedisplay();
}

bool Maze::Walk(int direction) {
	GLfloat nx = 0.0, ny = 0.0, nz = 0.0, lx, ly, alpha, si, projLength, sf, gap, nxx, nyy, nfxx, nfyy;


	nx = character->position->x + (direction * character->vel) * cosf(character->dir);
	ny = character->position->y + (direction * character->vel) * sinf(character->dir);

	for (int n = 0; n < numNos; n++){
		No ni = nos[n];

		if (pow(nx - (ni.x * MAP_COOR_SCALE), 2) + pow(ny - (ni.y * MAP_COOR_SCALE), 2) <= pow((ni.largura * 0.5) * MAP_COOR_SCALE, 2)) {
			nz = ni.z * MAP_COOR_SCALE + CHARACTER_HEIGHT * 0.5;
			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			status->walking = GL_TRUE;
			cout << "Node" << " NZ: " << nz << " Z: " << character->position->z << endl;
			return false;
		}
	}

	for (int i = 0; i < numArcos; i++) {

		No ni = nos[arcos[i].noi];
		No nf = nos[arcos[i].nof];
		si = ni.largura * 0.5 * MAP_COOR_SCALE;
		gap = nf.z * MAP_COOR_SCALE - ni.z * MAP_COOR_SCALE;
		sf = nf.largura * 0.5 * MAP_COOR_SCALE;
		projLength = sqrtf(powf(nf.x * MAP_COOR_SCALE - ni.x * MAP_COOR_SCALE, 2) + powf(nf.y * MAP_COOR_SCALE - ni.y * MAP_COOR_SCALE, 2)) - si - sf;
		alpha = atan2(nf.y * MAP_COOR_SCALE - ni.y * MAP_COOR_SCALE, nf.x * MAP_COOR_SCALE - ni.x * MAP_COOR_SCALE);
		lx = ((nx - ni.x * MAP_COOR_SCALE) * cosf(alpha) + (ny - ni.y * MAP_COOR_SCALE) * sinf(alpha));
		ly = ((ny - ni.y * MAP_COOR_SCALE) * cosf(alpha) - (nx - ni.x * MAP_COOR_SCALE) * sinf(alpha));
		nz = ni.z * MAP_COOR_SCALE + CHARACTER_HEIGHT * 0.5;

		nxx = (nx - ni.x * MAP_COOR_SCALE) * cos(alpha) + (ny - ni.y * MAP_COOR_SCALE) * sin(alpha);
		nyy = (ny - ni.y * MAP_COOR_SCALE) * cos(alpha) - (nx - ni.x * MAP_COOR_SCALE) * sin(alpha);

		nfxx = (nx - nf.x * MAP_COOR_SCALE) * cos(alpha) + (ny - nf.y * MAP_COOR_SCALE) * sin(alpha);
		nfyy = (ny - nf.y * MAP_COOR_SCALE) * cos(alpha) - (nx - nf.x * MAP_COOR_SCALE) * sin(alpha);

		if (0.0 <= nxx 
			&& nxx <= si 
			&& -arcos[i].largura * 0.5 * MAP_COOR_SCALE <= nyy 
			&& nyy <= arcos[i].largura * 0.5 * MAP_COOR_SCALE) {

			nz = ni.z * MAP_COOR_SCALE + CHARACTER_HEIGHT * 0.5;
			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			cout << "Connection " << "si: " << si << " nxx: " << nxx << " nyy: " << nyy << endl;
			return false;
		}
		//	Needs FIX
		if (0.0 <= nfxx
			&& nfxx <= sf
			&& -arcos[i].largura * 0.5 * MAP_COOR_SCALE <= nfyy
			&& nfyy <= arcos[i].largura * 0.5 * MAP_COOR_SCALE) {

			nz = nf.z * MAP_COOR_SCALE + CHARACTER_HEIGHT * 0.5;
			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			cout << "Connection " << "sf: " << sf << " nxx: " << nfxx << " nyy: " << nfyy << endl;
			return false;
		}

		if (si < nxx 
			&& nxx < si + projLength 
			&& -arcos[i].largura * 0.5 * MAP_COOR_SCALE <= nyy 
			&& nyy <= arcos[i].largura * 0.5 * MAP_COOR_SCALE) {

			nz = ni.z * MAP_COOR_SCALE + (lx - si) / projLength * gap + CHARACTER_HEIGHT * 0.5;
			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			cout << "Arch" << "SI : " << si << "PROJLENGTH: " << projLength << "nxx: " << ni.x << "ni.y: " << ni.y <<  endl;
			return false;
		}
	}
}

bool Maze::Collision(GLfloat nx, GLfloat ny, GLfloat nz) {
	//cout << "POS(X,Y): " << nx << ", " << ny << endl;

	for (int i = 0; i<numArcos; i++){
		No ni = nos[arcos[i].noi];
		No nf = nos[arcos[i].nof];

		// colide with node
		if (pow(nx - (ni.x * 5), 2) + pow(ny - (ni.y * 5), 2) <= pow((ni.largura / 2) * 5, 2)) return true;
		if (pow(nx - (nf.x * 5), 2) + pow(ny - (nf.y * 5), 2) <= pow((nf.largura / 2) * 5, 2)) return true;

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

bool Maze::CollisionEnemy(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat xMin, xMax;
	GLfloat yMin, yMax;
	GLfloat zMin, zMax;

	xMin = enemy->position->x - CHARACTER_WIDTH / 2;
	xMax = enemy->position->x + CHARACTER_WIDTH / 2;

	yMin = enemy->position->y - CHARACTER_LENGTH / 2;
	yMax = enemy->position->y + CHARACTER_LENGTH / 2;

	zMin = enemy->position->z - CHARACTER_HEIGHT / 2;
	zMax = enemy->position->z + CHARACTER_HEIGHT / 2;

	return x >= xMin && x <= xMax &&
		y >= yMin && y <= yMax &&
		z >= zMin && z <= zMax;
}

void Maze::showLoginWindow() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(350, 350);
	glutCreateWindow("Login");
	glutDisplayFunc(Graphics::loginDisplay);
	glutKeyboardFunc(Keyboard::loginKeyboard);
	glutMainLoop();
}

void Maze::Launch(int argc, char **argv){
	status = new Status();
	//showLoginWindow(); // do not show yet, not 100% ready
	// there is a NEW BUG on receving the maps, dont know why so map is not saved ISSUE 47
	//MapsReceiver *receiver = new MapsReceiver();
	//string mapName = receiver->chooseMap();
	//if (!mapName.empty()) {
	//	//set choosen map
	//	status->mapfile = mapName + ".grafo";
		glutInit(&argc, argv);
		alutInit(&argc, argv);

		model = new Model();
		//status = new Status();
		character = new MainCharacter();
		enemy = new EnemyCharacter();
		obstacle = new Obstacle();

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

		leGrafo(status->mapfile);

		Keyboard::help();

		glutMainLoop();
/*	}*/

	
}
