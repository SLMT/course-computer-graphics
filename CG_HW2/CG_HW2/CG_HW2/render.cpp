#include <stdio.h>
#include <stdlib.h>

// Our libraries
#include "main.h"

// Shader attributes
GLint iLocPosition, iLocColor, iLocMVP;

// Transform matrix and model
Matrix transfromMatrix;
Model *currentModel = NULL;

// Camara for view
Camara camara = Camara(0, 0, 0, 0, 0, 1, 0, 1, 0);


void onIdle()
{
	glutPostRedisplay();
}

void onRender()
{
	///Example of displaying colorful triangle
	// clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(iLocPosition);
	glEnableVertexAttribArray(iLocColor);

	/*
	// Move example triangle to left by 0.5
	aMVP[0] = 1;	aMVP[4] = 0;	aMVP[8] = 0;	aMVP[12] = -0.5;
	aMVP[1] = 0;	aMVP[5] = 1;	aMVP[9] = 0;	aMVP[13] = 0;
	aMVP[2] = 0;	aMVP[6] = 0;	aMVP[10] = -1;	aMVP[14] = 0;
	aMVP[3] = 0;	aMVP[7] = 0;	aMVP[11] = 0;	aMVP[15] = 1;

	glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, aMVP);
	*/
	// Load indentity
	Matrix identityMatrix = Matrix();

	// Multiply view transform
	identityMatrix.postmultiply(camara.getViewTransform());

	// Render model
	currentModel->draw(identityMatrix, iLocPosition, iLocColor, iLocMVP);

	glutSwapBuffers();
}

void showShaderCompileStatus(GLuint shader, GLint *shaderCompiled){
	glGetShaderiv(shader, GL_COMPILE_STATUS, shaderCompiled);
	if(GL_FALSE == (*shaderCompiled))
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character.
		GLchar *errorLog = (GLchar*) malloc(sizeof(GLchar) * maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		fprintf(stderr, "%s", errorLog);

		glDeleteShader(shader);
		free(errorLog);
	}
}

void setShaders()
{
	GLuint v, f, p;
	char *vs = NULL;
	char *fs = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("shader.vert");
	fs = textFileRead("shader.frag");

	glShaderSource(v, 1, (const GLchar**)&vs, NULL);
	glShaderSource(f, 1, (const GLchar**)&fs, NULL);

	free(vs);
	free(fs);

	// compile vertex shader
	glCompileShader(v);
	GLint vShaderCompiled;
	showShaderCompileStatus(v, &vShaderCompiled);
	if(!vShaderCompiled) system("pause"), exit(123);

	// compile fragment shader
	glCompileShader(f);
	GLint fShaderCompiled;
	showShaderCompileStatus(f, &fShaderCompiled);
	if(!fShaderCompiled) system("pause"), exit(456);

	p = glCreateProgram();

	// bind shader
	glAttachShader(p, f);
	glAttachShader(p, v);

	// link program
	glLinkProgram(p);

	iLocPosition = glGetAttribLocation (p, "av4position");
	iLocColor    = glGetAttribLocation (p, "av3color");
	iLocMVP		 = glGetUniformLocation(p, "mvp");

	glUseProgram(p);
}
