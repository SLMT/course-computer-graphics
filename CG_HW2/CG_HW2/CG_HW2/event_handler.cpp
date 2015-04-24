#include <stdio.h>

// Our libraries
#include "main.h"

// Define wheel motion
#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP   0x0003
#define GLUT_WHEEL_DOWN 0x0004
#endif

#define DELTA 0.1f

// Transform Mode
enum TransformMode { translate, rotate, scale };
TransformMode transMode = translate;

void transformModel(bool moveX, bool moveY, bool moveZ, GLfloat value) {
	switch (transMode) {
	case translate:
		if (moveX)
			currentModel->translate(value, 0, 0);
		if (moveY)
			currentModel->translate(0, value, 0);
		if (moveZ)
			currentModel->translate(0, 0, value);
		break;
	case rotate:
		if (moveX)
			currentModel->rotate(value * 10, 1, 0, 0);
		if (moveY)
			currentModel->rotate(value * 10, 0, 1, 0);
		if (moveZ)
			currentModel->rotate(value * 10, 0, 0, 1);
		break;
	case scale:
		if (moveX)
			currentModel->scale(1.0f - value, 1, 1);
		if (moveY)
			currentModel->scale(1, 1.0f - value, 1);
		if (moveZ)
			currentModel->scale(1, 1, 1.0f - value);
		break;
	}
}



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

void onMouseMotionEvent(int x, int y) {  // callback on mouse drag
	printf("(%d, %d) mouse move\n", x, y);
}

void onKeyboardEvent(unsigned char key, int x, int y) {
	switch(key) {
		case 27: /* the Esc key */ 
			exit(0); 
			break;
		// X++
		case 'Q':
		case'q':
			transformModel(true, false, false, DELTA);
			break;
		// X--
		case 'A':
		case'a':
			transformModel(true, false, false, -DELTA);
			break;
		// Y++
		case 'W':
		case'w':
			transformModel(false, true, false, DELTA);
			break;
		// Y--
		case 'S':
		case's':
			transformModel(false, true, false, -DELTA);
			break;
		// Z++
		case 'E':
		case'e':
			transformModel(false, false, true, DELTA);
			break;
		// Z--
		case 'D':
		case'd':
			transformModel(false, false, true, -DELTA);
			break;
		// Switch transform mode
		case 'T':
		case 't':
			switch (transMode) {
			case translate:
				transMode = rotate;
				printf("Switch to rotate mode.\n");
				break;
			case rotate:
				transMode = scale;
				printf("Switch to scale mode.\n");
				break;
			case scale:
				transMode = translate;
				printf("Switch to translate mode.\n");
				break;
			}
			break;
	}
}
