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
enum TransformMode { TRANS_TRNAS, TRANS_ROT, TRANS_SCALE };
TransformMode transMode = TRANS_TRNAS;

// Camara Control Mode
enum CamaraMode { CAM_EYE, CAM_CEN, CAM_UP };
CamaraMode camaraControlMode = CAM_EYE;

// Flags
int pressX = -1, pressY = -1;
int modelIndex = 0;
bool isCamControl = true;

void transformModel(bool moveX, bool moveY, bool moveZ, GLfloat value) {
	switch (transMode) {
	case TRANS_TRNAS:
		if (moveX)
			world->getModel(modelIndex)->translate(value, 0, 0);
		if (moveY)
			world->getModel(modelIndex)->translate(0, value, 0);
		if (moveZ)
			world->getModel(modelIndex)->translate(0, 0, value);
		break;
	case TRANS_ROT:
		if (moveX)
			world->getModel(modelIndex)->rotate(value * 10, 0, 1, 0);
		if (moveY)
			world->getModel(modelIndex)->rotate(value * 10, 1, 0, 0);
		if (moveZ)
			world->getModel(modelIndex)->rotate(value * 10, 0, 0, 1);
		break;
	case TRANS_SCALE:
		if (moveX)
			world->getModel(modelIndex)->scale(1.0f - value, 1, 1);
		if (moveY)
			world->getModel(modelIndex)->scale(1, 1.0f - value, 1);
		if (moveZ)
			world->getModel(modelIndex)->scale(1, 1, 1.0f - value);
		break;
	}
}

void controlCamara(GLfloat dx, GLfloat dy, GLfloat dz) {
	switch (camaraControlMode) {
	case CAM_EYE:
		camara.moveEye(dx, dy, dz);
		break;
	case CAM_CEN:
		camara.moveCenter(dx, dy, dz);
		break;
	case CAM_UP:
		camara.moveUp(dx, dy, dz);
		break;
	}
}


void onMouseEvent(int who, int state, int x, int y)
{
	// Which button
	switch(who){
	case GLUT_WHEEL_UP:
		if (isCamControl)
			controlCamara(0, 0, DELTA);
		else
			transformModel(false, false, true, DELTA);
		break;
	case GLUT_WHEEL_DOWN:
		if (isCamControl)
			controlCamara(0, 0, -DELTA);
		else
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
	GLfloat dx = (GLfloat) (x - lastX);
	GLfloat dy = (GLfloat) (y - lastY);

	// Check if it was the first time moving after pressing button
	if (pressX != -1 && pressY != -1) {
		dx = (GLfloat) (x - pressX);
		dy = (GLfloat) (y - pressY);
		pressX = -1;
		pressY = -1;
	}

	// Transaform
	if (dx > 0 + FLT_EPSILON || dx < 0 - FLT_EPSILON) {
		if (isCamControl)
			controlCamara(dx / 500, 0, 0);
		else
			transformModel(true, false, false, dx / 500);
	}
	if (dy > 0 + FLT_EPSILON || dy < 0 - FLT_EPSILON) {
		if (isCamControl)
			controlCamara(0, -dy / 500, 0);
		else
			transformModel(false, true, false, -dy / 500);
	}

	// Save the location
	lastX = x;
	lastY = y;
}

void onKeyboardEvent(unsigned char key, int x, int y) {
	switch(key) {
		// ESC
		case 27:
			exit(0); 
			break;

		// Model transform
		case 'T':
		case 't':
			if (isCamControl || (!isCamControl && transMode != TRANS_TRNAS)) {
				isCamControl = false;
				transMode = TRANS_TRNAS;
				printf("Switch to model translate mode.\n");
				printf("Current model is no.%d.\n", modelIndex);
			}
			break;
		case 'R':
		case 'r':
			if (isCamControl || (!isCamControl && transMode != TRANS_ROT)) {
				isCamControl = false;
				transMode = TRANS_ROT;
				printf("Switch to model rotate mode.\n");
				printf("Current model is no.%d.\n", modelIndex);
			}
			break;
		case 'S':
		case 's':
			if (isCamControl || (!isCamControl && transMode != TRANS_SCALE)) {
				isCamControl = false;
				transMode = TRANS_SCALE;
				printf("Switch to model scale mode.\n");
				printf("Current model is no.%d.\n", modelIndex);
			}
			break;

		// Switch model
		case 'M':
		case 'm':
			modelIndex = (modelIndex + 1) % world->getModelCount();
			printf("Switch to model no.%d.\n", modelIndex);
			break;

		// Camara transform
		case 'E':
		case 'e':
			if (!isCamControl || (isCamControl && transMode != CAM_EYE)) {
				isCamControl = true;
				camaraControlMode = CAM_EYE;
				printf("Switch to camara eye control mode.\n");
			}
			break;
		case 'C':
		case 'c':
			if (!isCamControl || (isCamControl && transMode != CAM_CEN)) {
				isCamControl = true;
				camaraControlMode = CAM_CEN;
				printf("Switch to camara center control mode.\n");
			}
			break;
		case 'U':
		case 'u':
			if (!isCamControl || (isCamControl && transMode != CAM_UP)) {
				isCamControl = true;
				camaraControlMode = CAM_UP;
				printf("Switch to camara up vector control mode.\n");
			}
			break;

		// Switch view mode
		case 'V':
		case 'v':
			project.toggleProjectionMode();
			printf("Toggle projection mode.\n", modelIndex);
			break;

		// Reset
		case 13: // Enter
			if (isCamControl) {
				camara = DEFAULT_CAMARA;
				printf("Reset camara.\n");
			} else {
				world->resetModelTransfrom(modelIndex);
				printf("Reset model no.%d.\n", modelIndex);
			}
			break;

		// Help
		case 'H':
		case 'h':
			printf("==================== Help ====================\n");
			printf("Use mouse draging and wheel to control transform\n");
			printf("Press the following buttons to swtich mode\n");
			printf("- Model Transform -\n");
			printf("T: Translate Mode\n");
			printf("R: Rotate Mode\n");
			printf("S: Scale Mode\n");
			printf("M: Switch model\n");
			printf("- Camara Control -\n");
			printf("E: Eye Control Mode\n");
			printf("C: Center Control Mode\n");
			printf("U: Up Vector Control Mode\n");
			printf("- Other Commands -\n");
			printf("V: Toggle View Transform mode\n");
			printf("Enter: Reset Camara or Model\n");
			printf("H: Help List\n");
			break;
	}
}
