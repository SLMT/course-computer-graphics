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

unsigned current_index = 0;

void swapModel(GLMmodel* new_model) {
	GLMmodel* old_model = global_current_model;
	global_current_model = new_model;
	glmDelete(old_model);
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

void onMouseMove(int x, int y) {  // callback on mouse drag
	printf("(%d, %d) mouse move\n", x, y);
}

void onKeyboardEvent(unsigned char key, int x, int y) {
	switch(key) {
	case 'A':
	case 'a':
		// Move backward
		current_index = (current_index == 0)? global_obj_files_num - 1 : current_index - 1;
		swapModel(loadOBJModel(global_obj_files[current_index]));
		printf("Move backward to no.%u model %s\n", current_index, global_obj_files[current_index]);
		break;
	case 'D':
	case 'd':
		// Move forward
		current_index = (current_index == global_obj_files_num - 1)? 0 : current_index + 1;
		swapModel(loadOBJModel(global_obj_files[current_index]));
		printf("Move forward to no.%u model %s\n", current_index, global_obj_files[current_index]);
		break;
	case 'S':
	case 's':
		// Toggle solid/wireframes mode
		global_flag_is_solid = !global_flag_is_solid;
		printf("Solid mode: %s\n", global_flag_is_solid? "on" : "off");
		break;
	case 'H':
	case 'h':
		// Help
		printf("=============== Help ===============\n");
		printf("A/a: Change to the previous model\n");
		printf("D/d: Change to the next model\n");
		printf("S/s: Toggle solid/wireframes mode\n");
		printf("H/h: Open this help\n");
		printf("Esc: Exit this program\n");
		printf("====================================\n");
		break;
	case KEY_ESC:
		exit(0); 
		break;
	}
}