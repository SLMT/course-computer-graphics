#include <stdio.h>
#include <float.h>

// Our libraries
#include "main.h"

// Flags
unsigned selectedLight = 0;

void onMouseEvent(int who, int state, int x, int y) {
	// Do nothing
}

void onMouseDragEvent(int x, int y) {
	// Do nothing
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

		// Spot light control
		case 'Z':
		case 'z':
			world->getLigthSource(2)->adjustSpotExp(0.01);
			break;
		case 'X':
		case 'x':
			world->getLigthSource(2)->adjustSpotExp(-0.01);
			break;
		case 'C':
		case 'c':
			world->getLigthSource(2)->adjustSpotCutoff(0.05);
			break;
		case 'V':
		case 'v':
			world->getLigthSource(2)->adjustSpotCutoff(-0.05);
			break;

		// Help
		case 'H':
		case 'h':
			printf("==================== Help ====================\n");
			printf("Select the light source first,\n");
			printf("I: Directional Light Source\n");
			printf("O: Point Light Source\n");
			printf("P: Spot Light Source\n\n");
			printf("then use the follwing controls: \n");
			printf("A/D: Move left/right\n");
			printf("W/S: Move up/down\n");
			printf("L: Turn on/off the selected light source\n");
			printf("Z/X: Adjust the exponent value of spot light\n");
			printf("C/V: Adjust the cutoff value of spot light\n\n");
			printf("M: Next model\n");
			printf("H: Help List\n");
			break;
	}
}
