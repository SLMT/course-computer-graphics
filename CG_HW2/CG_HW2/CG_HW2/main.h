#ifndef MAIN_H
#define MAIN_H

// Our libraries
#include "matrix.h"
#include "model.h"
#include "camara.h"
#include "projection.h"

// 3-party libraries
#include <GL/glew.h>
#include <freeglut/glut.h>
#include "textfile.h"

// Event handlers
extern void onMouseEvent(int who, int state, int x, int y);
extern void onMouseMotionEvent(int x, int y);
extern void onKeyboardEvent(unsigned char key, int x, int y);

// Render functions
extern void onIdle();
extern void onRender();
extern void setShaders();

// Shader attributes
extern GLint iLocPosition, iLocColor, iLocMVP;

// Transform matrix and model
extern Matrix transfromMatrix;
extern Model *currentModel;

// Camara for view
extern Camara camara;

#endif