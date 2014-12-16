#ifndef _MOUSE
#define _MOUSE

#include "GlobalVars.h"
#include "Status.h"
#include "Model.h"
#include "Graphics.h"

class Mouse {
public:
    static void motionRotate(int x, int y);
    static void motionZoom(int x, int y);
    static void motionDrag(int x, int y);
    static int picking(int x, int y);
    static void mouse(int btn, int state, int x, int y);
};

#endif