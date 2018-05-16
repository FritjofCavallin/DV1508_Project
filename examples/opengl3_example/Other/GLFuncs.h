#pragma once
#include "GL/gl3w.h"


#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

void checkGLError();
void checkGLError(const char * msg);


GLuint loadShader(const char* vertexShader, const char* fragmentShader);
GLuint loadShader(const char* vertexShader, const char* geomShader, const char* fragmentShader);


bool loadTexture(const char* texFile, GLuint &tex);