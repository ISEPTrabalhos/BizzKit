#ifndef _KEYBOARD
#define _KEYBOARD

#include "GlobalVars.h"
#include "Status.h"
#include "Model.h"

class Keyboard {
public:
    static void keyboard(unsigned char key, int x, int y);
    static void Special(int key, int x, int y);
    static void help(void);
	static void specialKeyUp(int key, int x, int y);
	static void loginKeyboard(unsigned char key, int x, int y);
};

#endif