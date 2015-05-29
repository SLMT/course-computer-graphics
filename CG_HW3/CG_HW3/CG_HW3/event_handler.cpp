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
unsigned selectedLight = 0;

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
			world->getLigthSource(selectedLight)->rotateByY(-5);
			break;
		case 'D':
		case 'd':
			world->getLigthSource(selectedLight)->rotateByY(5);
			break;
		case 'W':
		case 'w':
			world->getLigthSource(selectedLight)->rotateByX(-5);
			break;
		case 'S':
		case 's':
			world->getLigthSource(selectedLight)->rotateByX(5);
			break;

		// Open or close
		case 'L':
		case 'l':
			world->getLigthSource(selectedLight)->toggleEnableStatus();
			printf("Toggle the selected light source\n");
			break;

		// Select lights
		case 'I':
		case 'i':
			selectedLight = 0;
			printf("Now select the directional light source\n");
			break;
		case 'O':
		case 'o':
			selectedLight = 1;
			printf("Now select the positional light source\n");
			break;
		case 'P':
		case 'p':
			selectedLight = 2;
			printf("Now select the spot light source\n");
			break;
	}
}
