#include "Camera.h"

Camera::Camera(){
	// set direction
	dir_lat = M_PI / 4;
	dir_long = -M_PI / 4;

	// set (fov) distance to see
	fov = 60;

	// set distande
	dist = 100;

	// set center
	center[0] = 0;
	center[1] = 0;
	center[2] = 0;
}

Camera::~Camera(){}