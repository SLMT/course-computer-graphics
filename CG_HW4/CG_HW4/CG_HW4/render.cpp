#include <stdio.h>
#include <stdlib.h>

// Our libraries
#include "main.h"

// Shader pointers
ShaderPointers pointers;

// Model, View and projection
World *world = NULL;
const Camara DEFAULT_CAMARA = Camara(0, 0, 3, 0, 0, 0, 0, 1, 0);
Camara camara = DEFAULT_CAMARA;
Projection project = Projection(false, -1.5, 1.5, -1.5, 1.5, 1, 10);
bool isVertexLighting = false;

void onIdle()
{
	glutPostRedisplay();
}

void onRender()
{
	// clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Eanble arraies
	glEnableVertexAttribArray(pointers.vertexPos);
	glEnableVertexAttribArray(pointers.vertexNor);
	glEnableVertexAttribArray(pointers.texCoord);

	// Vertex lighting vs. Fragment lighting
	if (isVertexLighting)
		glUniform1i(pointers.isVertexLighting, 1);
	else
		glUniform1i(pointers.isVertexLighting, 0);

	// Texture 

	// Load an indentity matrix
	Matrix mvp = Matrix();

	// Multiply projection transform
	mvp.postmultiply(project.getProjectTransfrom());

	// Multiply view transform
	mvp.postmultiply(camara.getViewTransform());

	// Render world
	world->draw(mvp, pointers);

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

void initShaders()
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

	// link shader attributes and unifroms
	pointers.vertexPos = glGetAttribLocation(p, "av4position");
	pointers.vertexNor = glGetAttribLocation(p, "av3normal");
	pointers.texCoord = glGetAttribLocation(p, "av2texCoord");
	pointers.mvp = glGetUniformLocation(p, "mvp");

	pointers.matAmb = glGetUniformLocation(p, "material.ambient");
	pointers.matDiff = glGetUniformLocation(p, "material.diffuse");
	pointers.matSpec = glGetUniformLocation(p, "material.specular");
	pointers.matShin = glGetUniformLocation(p, "material.shininess");
	
	pointers.dirEnabled = glGetUniformLocation(p, "lights.dirEnabled");
	pointers.dirDirection = glGetUniformLocation(p, "lights.dirDirection");
	pointers.dirAmbient = glGetUniformLocation(p, "lights.dirAmbient");
	pointers.dirColor = glGetUniformLocation(p, "lights.dirColor");

	pointers.posEnabled = glGetUniformLocation(p, "lights.posEnabled");
	pointers.posPosition = glGetUniformLocation(p, "lights.posPosition");
	pointers.posAmbient = glGetUniformLocation(p, "lights.posAmbient");
	pointers.posColor = glGetUniformLocation(p, "lights.posColor");

	pointers.spotEnabled = glGetUniformLocation(p, "lights.spotEnabled");
	pointers.spotPosition = glGetUniformLocation(p, "lights.spotPosition");
	pointers.spotAmbient = glGetUniformLocation(p, "lights.spotAmbient");
	pointers.spotColor = glGetUniformLocation(p, "lights.spotColor");
	pointers.spotDirection = glGetUniformLocation(p, "lights.spotDirection");
	pointers.spotExponent = glGetUniformLocation(p, "lights.spotExponent");
	pointers.spotCosCutoff = glGetUniformLocation(p, "lights.spotCosCutoff");

	pointers.havingTexture = glGetUniformLocation(p, "havingTexture");
	pointers.isVertexLighting = glGetUniformLocation(p, "isVertexLighting");

	glUseProgram(p);
}
