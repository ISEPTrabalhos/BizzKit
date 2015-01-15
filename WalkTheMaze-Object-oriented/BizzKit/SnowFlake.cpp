#include "SnowFlake.h"


SnowFlake::SnowFlake() { flag = true; }


SnowFlake::~SnowFlake(){}

void SnowFlake::draw() {
	if (flag) reGen();

	float delta_theta = 0.01;

	// draw
	glPushMatrix();
	glTranslatef(position->x, position->y, 0);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON); // OR GL_LINE_LOOP

	for (float angle = 0; angle < 2 * M_PI; angle += delta_theta)
		glVertex3f(radious*cos(angle), radious*sin(angle), 0);

	glEnd();
	glPopMatrix();

	if (position->y >(limit->y * -1)) position->y -= vel;
	else position->y = limit->y;
}

void SnowFlake::reGen() {
	position = new Point();
	limit = new Point();
	limit->x = glutGet(GLUT_WINDOW_WIDTH);
	limit->y = glutGet(GLUT_WINDOW_HEIGHT);
	limit->z = 0;

	vel = 2;

	int nx = limit->x * 2;
	int ny = limit->y * 2;
	position->x = (rand() % nx) - limit->x;
	position->y = (rand() % ny) - limit->y;
	radious = rand() % 10 + 10;

	flag = false;
}