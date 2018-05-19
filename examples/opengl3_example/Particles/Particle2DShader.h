#pragma once
#include "../Other/GLFuncs.h"
#include "Particle.h"
#include "../camera.h"


class Particle2DShader
{
public:

	GLuint gShaderProgram;

	GLint  gViewMat, gProjMat, gArea;


	/* Loaded texture for default behavior
	*/
	GLuint defaultTex;

	Particle2DShader();
	~Particle2DShader();

	void assignGlobalUniforms(GPUParticle &part);
	void load();
};

