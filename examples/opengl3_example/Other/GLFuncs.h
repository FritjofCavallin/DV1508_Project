#pragma once
#include "GL/gl3w.h"


void checkGLError();


GLuint loadShader(const char* vertexShader, const char* fragmentShader);