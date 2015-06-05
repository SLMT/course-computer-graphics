#ifndef MAIN_H
#define MAIN_H

// Our libraries
#include "shader.h"
#include "matrix.h"
#include "model.h"
#include "camara.h"
#include "projection.h"
#include "world.h"
#include "light_source.h"

// 3-party libraries
#include <GL/glew.h>
#include <freeglut/glut.h>
#include "textfile.h"

// Event handlers
extern void onMouseEvent(int who, int state, int x, int y);
extern void onMouseDragEvent(int x, int y);
extern void onKeyboardEvent(unsigned char key, int x, int y);

// Render functions
extern void onIdle();
extern void onRender();
extern void initShaders();

// Shader attributes
extern ShaderPointers pointers;

// Render objects
extern Matrix transfromMatrix;
extern World *world;
extern const Camara DEFAULT_CAMARA;
extern Camara camara;
extern Projection project;
extern bool isVertexLighting;

// Camara for view
extern Camara camara;

#endif