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
LightSource light = LightSource(1.0f, 1.0f, 1.0f);

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

	// Load an indentity matrix
	Matrix mvp = Matrix();

	// Multiply projection transform
	mvp.postmultiply(project.getProjectTransfrom());

	// Multiply view transform
	mvp.postmultiply(camara.getViewTransform());

	// Set up the light source
	light.linkShader(pointers);

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
	pointers.mvp = glGetUniformLocation(p, "mvp");

	pointers.matAmb = glGetUniformLocation(p, "Material.ambient");
	pointers.matDiff = glGetUniformLocation(p, "Material.diffuse");
	pointers.matSpec = glGetUniformLocation(p, "Material.specular");
	pointers.matShin = glGetUniformLocation(p, "Material.shininess");
	
	pointers.lightAmb = glGetUniformLocation(p, "LightSource.ambient");
	pointers.lightDiff = glGetUniformLocation(p, "LightSource.diffuse");
	pointers.lightSpec = glGetUniformLocation(p, "LightSource.specular");
	pointers.lightPos = glGetUniformLocation(p, "LightSource.position");
	pointers.lightHalfVec = glGetUniformLocation(p, "LightSource.halfVector");
	pointers.lightSpotDir = glGetUniformLocation(p, "LightSource.spotDirection");
	pointers.lightSpotExp = glGetUniformLocation(p, "LightSource.spotExponent");
	pointers.lightSpotCut = glGetUniformLocation(p, "LightSource.spotCutoff");
	pointers.lightSpotCos = glGetUniformLocation(p, "LightSource.spotCosCutoff");
	pointers.lightConsAtt = glGetUniformLocation(p, "LightSource.constantAttenuation");
	pointers.lightLinAtt = glGetUniformLocation(p, "LightSource.linearAttenuation");
	pointers.lightQuadAtt = glGetUniformLocation(p, "LightSource.quadraticAttenuation");

	glUseProgram(p);
}
