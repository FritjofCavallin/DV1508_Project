#pragma once
#include "../Other/GLFuncs.h"
#include "Particle.h"
#include "../camera.h"


class ParticleBuffer
{
public:
	GLuint gVAO, gVertBuf;

	unsigned int _bufCount;

	ParticleBuffer();
	~ParticleBuffer();

	void draw();
	void buffer(size_t nVerts, const void *data, size_t offsetN);
	void destroy();
};

class ParticleShader
{
public:

	GLuint gShaderProgram;

	GLint  gViewMat, gProjMat;

	ParticleShader();
	~ParticleShader();

	void assignGlobalUniforms(Camera *cam);
	void load();
	ParticleBuffer genBuffer(size_t nVerts);
};

