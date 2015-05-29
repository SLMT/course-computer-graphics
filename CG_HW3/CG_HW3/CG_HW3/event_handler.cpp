#include <stdio.h>
#include <float.h>

// Our libraries
#include "main.h"

// Define wheel motion
#ifndef GLUT_WHEEL_UP
	#define GLUT_WHEEL_UP   0x0003
	#define GLUT_WHEEL_DOWN 0x0004
#endif

#define DELTA 0.1f

// Flags
int pressX = -1, pressY = -1;

void onMouseEvent(int who, int state, int x, int y) {
	
}

void onMouseDragEvent(int x, int y) {  // callback on mouse drag
	
}

void onKeyboardEvent(unsigned char key, int x, int y) {
	switch(key) {
		// ESC
		case 27:
			exit(0); 
			break;

		// Switch model
		case 'M':
		case 'm':
			world->nextModel();
			break;

		// Moving
		case 'A':
		case 'a':
			world->getLigthSource()->rotateByY(-5);
			break;
		case 'D':
		case 'd':
			world->getLigthSource()->rotateByY(5);
			break;
		case 'W':
		case 'w':
			world->getLigthSource()->rotateByX(-5);
			break;
		case 'S':
		case 's':
			world->getLigthSource()->rotateByX(5);
			break;
	}
}
