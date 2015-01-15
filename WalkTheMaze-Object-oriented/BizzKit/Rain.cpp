#include "Rain.h"

Rain::Rain() { flag = true; }


Rain::~Rain(){}

void Rain::draw() {
	if (flag) reGen();

	float delta_theta = 0.01;

	// draw
	glPushMatrix();
	//draw separator line
	glLineWidth(lineWidth);
	glColor3f(0.5, 0.6, 0.7);
	glBegin(GL_LINES);
	glVertex3f(position->x, position->y, 0.0);
	glVertex3f(position->x, position->y + size, 0.0);
	glEnd();
	glPopMatrix();

	if (position->y >(limit->y * -1)) position->y -= vel;
	else position->y = limit->y;
}

void Rain::reGen() {
	position = new Point();
	limit = new Point();
	limit->x = glutGet(GLUT_WINDOW_WIDTH);
	limit->y = glutGet(GLUT_WINDOW_HEIGHT);
	limit->z = 0;

	vel = 40;

	int nx = limit->x * 2;
	int ny = limit->y * 2;
	position->x = (rand() % nx) - limit->x;
	position->y = (rand() % ny) - limit->y;
	 size = rand() % 90 + 20;
	 lineWidth = 1.0;
	
	flag = false;
}