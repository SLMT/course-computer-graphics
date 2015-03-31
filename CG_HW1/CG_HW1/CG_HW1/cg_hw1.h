#ifndef CG_HW1_H
#define CG_HW1_H

// Related Header Files
#include "glm.h"

// model.cpp
GLMmodel* loadOBJModel(char *filename);

// event_handler.cpp
void onMouseEvent(int who, int state, int x, int y);
void onMouseMove(int x, int y);
void onKeyboardEvent(unsigned char key, int x, int y);

// gl_render.cpp
void idle(void);
void renderScene(void);

// gl_shader.cpp
void setShaders();


// Global Variables
extern GLMmodel *global_current_model; // in gl_render.cpp
extern GLint global_pos_loc, global_color_loc; // in gl_render.cpp
extern char *global_obj_files[];
extern unsigned global_obj_files_num;
extern bool global_flag_is_solid;

#endif  // CG_HW1_H
