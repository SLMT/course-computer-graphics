/************************************
	Purpose:
		Event handlers
	Author: SLMT
************************************/
// Original Libraries
#include <stdio.h>

// OpenGL-related Libraries
#include <freeglut/glut.h>

// My Header Files
#include "cg_hw1.h"

// Constants
#define GLUT_WHEEL_UP   0x0003
#define GLUT_WHEEL_DOWN 0x0004

#define KEY_ESC 27


void onMouseEvent(int who, int state, int x, int y)
{
	printf("(%d, %d) ", x, y);

	switch(who){
		case GLUT_LEFT_BUTTON:   printf("left button   "); break;
		case GLUT_MIDDLE_BUTTON: printf("middle button "); break;
		case GLUT_RIGHT_BUTTON:  printf("right button  "); break; 
		case GLUT_WHEEL_UP:      printf("wheel up      "); break;
		case GLUT_WHEEL_DOWN:    printf("wheel down    "); break;
		default:                 printf("%-14d", who);     break;
	}

	switch(state){
		case GLUT_DOWN:          printf("start ");         break;
		case GLUT_UP:            printf("end   ");         break;
	}

	printf("\n");
}

void onMouseMove(int x, int y) {  // callback on mouse drag
	printf("(%d, %d) mouse move\n", x, y);
}

void onKeyboardEvent(unsigned char key, int x, int y) {
	printf("(%d, %d) ", x, y);
	switch(key) {
		case KEY_ESC: 
			exit(0); 
			break;
	}
	printf("\n");
}