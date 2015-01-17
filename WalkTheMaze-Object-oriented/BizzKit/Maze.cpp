#include "Maze.h"
#include "MainCharacter.h"
#include "Login.h"
#include "Status.h"
#include "MapsReceiver.h"
#include "EnemyCharacter.h"
#include "Obstacle.h"
#include "Trap.h"
#include "Door.h"

#define MAP_COOR_SCALE 5
#define GAP_CLIMB 0.1

Model *model;
Status *status;
MainCharacter *character;
EnemyCharacter *enemy;
Obstacle *obstacle;
Trap *trap;
Door *door1, *door2, *exitDoor;
SnowFlake* sf[40] = {
	new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(),
	new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(),
	new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(),
	new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake(), new SnowFlake()
};
Rain* rain[40] = {
	new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(),
	new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(),
	new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(),
	new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain(), new Rain()
};


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

	if (!character->IsDead()){
		ChasePlayer();

		if (!status->falling){
			GLfloat nx = 0, ny = 0, z = character->position->z;


			if (status->up){
				if (Walk(1)) {
					nx = character->position->x + character->vel * cosf(character->dir);
					ny = character->position->y + character->vel * sinf(character->dir);
					character->position->x = nx;
					character->position->y = ny;
					character->position->z = CHARACTER_HEIGHT * 0.5;
					status->walking = GL_TRUE;
					status->score += 1;
					//	Check if the character has fallen and drains some life
					if (character->position->z - z < -4.0) {
						character->health -= 10;
						Music *f = new Music("fall.wav");
						f->play();
						status->score -= 10;
						if (status->score <= 0)
							status->score = 0;

					}

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
					if (character->position->z - z < -4.0) {
						character->health -= 10;
						Music *f = new Music("fall.wav");
						f->play();
						
					}
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
		}
		else{
			character->homer.SetSequence(20);
			status->falling = GL_FALSE;
			//Timer(10);
		}

		if (status->mapfile == "quarto1.grafo") {

			if (character->position->x > 10 && character->position->x < 15 && character->position->y>285 && character->position->y < 295) {
				status->mapfile = "quarto2.grafo";
				character->position->x = -125;
				character->position->y = -250;
				leGrafo(status->mapfile);
			}

			if (character->position->x > 285 && character->position->x<295 && character->position->y>-275 && character->position->y < -265) {
				status->mapfile = "quarto3.grafo";
				character->position->x = -270;
				character->position->y = 250;
				leGrafo(status->mapfile);
			}

			if (character->position->x > 185 && character->position->x<195 && character->position->y>285 && character->position->y < 295) {
				//	Win the Game
			}

		}
		else if (status->mapfile == "quarto2.grafo") {

			if (character->position->x>-130 && character->position->x<-120 && character->position->y>-295 && character->position->y < -285) {
				status->mapfile = "quarto1.grafo";
				character->position->x = 20;
				character->position->y = 290;
				leGrafo(status->mapfile);
			}
		}
		else {
			if (character->position->x>-285 && character->position->x < -275 && character->position->y>245 && character->position->y < 255) {
				status->mapfile = "quarto1.grafo";
				character->position->x = 270;
				character->position->y = -270;
				leGrafo(status->mapfile);
			}

			if (character->position->x>275 && character->position->x < 285 && character->position->y>-285 && character->position->y < -275) {
				// Win the Game
			}
				
		}

		if (CollisionEnemy(character->position->x, character->position->y, character->position->z))
		{
			character->Die();
		}

		if (DetectTrap(character->position->x, character->position->y, character->position->z - CHARACTER_HEIGHT / 2.0))
		{
			character->Die();
		}
	}
	else
	{
		//if (character->homer.GetSequence() != 19)
		//	character->homer.SetSequence(19);
		character->homer.SetSequence(73);
	}

	glutPostRedisplay();
}

void Maze::ChasePlayer()
{
	static GLfloat enemyInitialX = enemy->position->x;
	static GLfloat enemyInitialY = enemy->position->y;
	static GLfloat enemyInitialZ = enemy->position->z;

	GLfloat range = 50.0;

	GLfloat playerX = character->position->x;
	GLfloat playerY = character->position->y;
	GLfloat playerZ = character->position->z;

	GLfloat xMin, xMax;
	GLfloat yMin, yMax;
	GLfloat zMin, zMax;

	xMin = enemy->position->x - range;
	xMax = enemy->position->x + range;

	yMin = enemy->position->y - range;
	yMax = enemy->position->y + range;

	zMin = enemy->position->z - range;
	zMax = enemy->position->z + range;

	if (playerX >= xMin && playerX <= xMax &&
		playerY >= yMin && playerY <= yMax &&
		playerZ >= zMin && playerZ <= zMax)
	{
		if (enemy->model.GetSequence() != 3)
		{
			enemy->model.SetSequence(3); //4
		}

		double ladoAdjacente = playerX - enemy->position->x;
		double ladoOposto = playerY - enemy->position->y;
		double ladoHipotenusa = sqrt(pow(ladoAdjacente, 2) + pow(ladoOposto, 2));

		enemy->dir = atan2(ladoOposto, ladoAdjacente);

		if (playerX > enemy->position->x || playerX < enemy->position->x)
		{
			enemy->position->x += enemy->vel * cos(enemy->dir);
		}

		if (playerY > enemy->position->y || playerY < enemy->position->y)
		{
			enemy->position->y += enemy->vel * sin(enemy->dir);
		}
	}
	else // retorna ao lugar ou fica parado
	{
		if (enemy->model.GetSequence() != 1)
			enemy->model.SetSequence(1);
	}
}

bool Maze::Walk(int direction) {
	if (character->IsDead())
	{
		return false;
	}

	GLfloat nx = 0.0, ny = 0.0, nz = 0.0, lx, ly, alpha, si, projLength, sf, gap, nxx, nyy, nfxx, nfyy;


	nx = character->position->x + (direction * character->vel) * cosf(character->dir);
	ny = character->position->y + (direction * character->vel) * sinf(character->dir);

	if (CollisionObstacle(nx, ny, character->position->z))
	{
		return false;
	}

	for (int n = 0; n < numNos; n++){
		No ni = nos[n];

		if (pow(nx - (ni.x * MAP_COOR_SCALE), 2) + pow(ny - (ni.y * MAP_COOR_SCALE), 2) <= pow((ni.largura * 0.5) * MAP_COOR_SCALE, 2)) {
			nz = ni.z * MAP_COOR_SCALE + CHARACTER_HEIGHT * 0.5;
			if (nz > character->position->z && nz - character->position->z > 1) {
				Music *wall = new Music("wall.wav");
				wall->play();
				status->falling = GL_TRUE;
				status->score -= 10;
				if (status->score <= 0)
					status->score = 0;
				character->health -= 5;
				return false;
			}
			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			status->walking = GL_TRUE;
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

		nfxx = (nx - nf.x * MAP_COOR_SCALE) * cos(alpha + M_PI) + (ny - nf.y * MAP_COOR_SCALE) * sin(alpha + M_PI);
		nfyy = (ny - nf.y * MAP_COOR_SCALE) * cos(alpha + M_PI) - (nx - nf.x * MAP_COOR_SCALE) * sin(alpha + M_PI);

		if (0.0 <= nxx
			&& nxx <= si
			&& -arcos[i].largura * 0.5 * MAP_COOR_SCALE <= nyy
			&& nyy <= arcos[i].largura * 0.5 * MAP_COOR_SCALE) {

			nz = ni.z * MAP_COOR_SCALE + CHARACTER_HEIGHT * 0.5;
			if (nz > character->position->z && nz - character->position->z > 1) {
				Music *wall = new Music("wall.wav");
				wall->play();
				status->falling = GL_TRUE;
				status->score -= 10;
				if (status->score <= 0)
					status->score = 0;
				character->health -= 5;
				return false;
			}

			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			status->walking = GL_TRUE;
			return false;
		}

		if (0.0 <= nfxx
			&& nfxx <= sf
			&& -arcos[i].largura * 0.5 * MAP_COOR_SCALE <= nfyy
			&& nfyy <= arcos[i].largura * 0.5 * MAP_COOR_SCALE) {

			nz = nf.z * MAP_COOR_SCALE + CHARACTER_HEIGHT * 0.5;
			if (nz > character->position->z && nz - character->position->z > 1) {
				Music *wall = new Music("wall.wav");
				wall->play();
				status->falling = GL_TRUE;
				status->score -= 10;
				if (status->score <= 0)
					status->score = 0;
				character->health -= 5;
				return false;
			}


			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			status->walking = GL_TRUE;
			return false;
		}

		if (si < nxx
			&& nxx < si + projLength
			&& -arcos[i].largura * 0.5 * MAP_COOR_SCALE <= nyy
			&& nyy <= arcos[i].largura * 0.5 * MAP_COOR_SCALE) {

			nz = ni.z * MAP_COOR_SCALE + (lx - si) / projLength * gap + CHARACTER_HEIGHT * 0.5;
			if (nz > character->position->z && nz - character->position->z > 1) {
				Music *wall = new Music("wall.wav");
				wall->play();
				status->falling = GL_TRUE;
				status->score -= 10;
				if (status->score <= 0)
					status->score = 0;
				character->health -= 5;
				return false;
			}

			character->position->x = nx;
			character->position->y = ny;
			character->position->z = nz;
			status->walking = GL_TRUE;
			return false;
		}
	}
}

bool Maze::CollisionObstacle(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat xMin, xMax;
	GLfloat yMin, yMax;
	GLfloat zMin, zMax;

	xMin = obstacle->position->x - obstacle->size / 2;
	xMax = obstacle->position->x + obstacle->size / 2;

	yMin = obstacle->position->y - obstacle->size / 2;
	yMax = obstacle->position->y + obstacle->size / 2;

	zMin = obstacle->position->z;
	zMax = obstacle->position->z + obstacle->height;

	return x >= xMin && x <= xMax &&
		y >= yMin && y <= yMax &&
		z >= zMin && z <= zMax;
}

bool Maze::DetectTrap(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat xMin, xMax;
	GLfloat yMin, yMax;
	GLfloat zMin, zMax;

	xMin = trap->position->x - trap->size / 2;
	xMax = trap->position->x + trap->size / 2;

	yMin = trap->position->y - trap->size / 2;
	yMax = trap->position->y + trap->size / 2;

	zMin = trap->position->z;
	zMax = trap->position->z + trap->height;

	return x >= xMin && x <= xMax &&
		y >= yMin && y <= yMax &&
		z >= zMin && z <= zMax;
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

void Maze::spawn(){
	if (status->mapfile == "quarto2.grafo"){
		character->position->x = -125;
		character->position->y = -250;
	}
}

void Maze::Launch(int argc, char **argv){
	srand(time(NULL));
	rand();

	status = new Status();
	glutInit(&argc, argv);
	alutInit(&argc, argv);
	model = new Model();
	character = new MainCharacter();
	enemy = new EnemyCharacter();
	door1 = new Door(15, 290, "door.mdl");
	door2 = new Door(290, -270, "door.mdl");
	exitDoor = new Door(280, -280, "exit.mdl");
	exitDoor->model.SetSequence(1);
	exitDoor->position->z = 3;
	obstacle = new Obstacle();
	trap = new Trap();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	int loginWindow = glutCreateWindow("OpenGL");
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

	spawn();

	leGrafo(status->mapfile);

	glutMainLoop();

	//	// there is a NEW BUG on receving the maps, dont know why so map is not saved ISSUE 47
	//	//MapsReceiver *receiver = new MapsReceiver();
	//	//string mapName = receiver->chooseMap();
	//	//if (!mapName.empty()) {
	//	//	//set choosen map
	//	//	status->mapfile = mapName + ".grafo";

}
