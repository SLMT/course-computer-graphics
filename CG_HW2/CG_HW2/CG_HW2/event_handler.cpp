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

// Transform Mode
enum TransformMode { translate, rotate, scale };
TransformMode transMode = translate;

// Global flags
int pressX = -1, pressY = -1;

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
	// Which button
	switch(who){
	case GLUT_WHEEL_UP:
		transformModel(false, false, true, DELTA);
		break;
	case GLUT_WHEEL_DOWN:
		transformModel(false, false, true, -DELTA);
		break;
	}

	// Button states
	switch(state){
	case GLUT_DOWN:
		// Save press position
		pressX = x;
		pressY = y;
		break;
	case GLUT_UP:
		break;
	}
}

void onMouseDragEvent(int x, int y) {  // callback on mouse drag
	static int lastX, lastY;

	// Calculate values
	GLfloat dx = x - lastX;
	GLfloat dy = y - lastY;

	// Check if it was the first time moving after pressing button
	if (pressX != -1 && pressY != -1) {
		dx = x - pressX;
		dy = y - pressY;
		pressX = -1;
		pressY = -1;
	}

	// Transaform
	if (dx > 0 + FLT_EPSILON || dx < 0 - FLT_EPSILON)
		transformModel(true, false, false, dx / 500);
	if (dy > 0 + FLT_EPSILON || dy < 0 - FLT_EPSILON)
		transformModel(false, true, false, -dy / 500);

	// Save the location
	lastX = x;
	lastY = y;
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
