#pragma once
#include "../Other/GLFuncs.h"
#include "Particle.h"
#include "../camera.h"


class Particle2DShader
{
public:
	
	Particle2DShader();
	~Particle2DShader();

	void render(GPUParticle &part, GLint x, GLint y, GLuint w, GLuint h);
	void load();

private:
	GLuint gShaderProgram;
	GLuint gShaderClear;
	GLint gClearColor;

	GLint  gRot, gSize, gSizeMax;
	GLint gColor, gTex_Blend, gTex_Area, gArea;


	/* Loaded texture for default behavior
	*/
	GLuint defaultTex, quadVAO, quadVBO;

	glm::vec4 bgColor, borderColor;
	void genBuffer();
};

