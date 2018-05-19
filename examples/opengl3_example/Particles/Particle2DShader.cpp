#include "Particle2DShader.h"
#include <exception>
#include "../Other/Constants.h"
#include <iostream>
const GLuint SHADE_DEF = 1000000;

Particle2DShader::Particle2DShader()
{
	gShaderProgram = SHADE_DEF;
}



Particle2DShader::~Particle2DShader()
{
	glDeleteTextures(1, &defaultTex);
	glDeleteShader(gShaderProgram);
}

void Particle2DShader::assignGlobalUniforms(GPUParticle &part)
{
	glUseProgram(gShaderProgram);
	

	checkGLError();
}

void Particle2DShader::load()
{
	checkGLError();
	if (gShaderProgram != SHADE_DEF)
		glDeleteShader(gShaderProgram);
	gShaderProgram = loadShader("Shaders/Particle2DVertex.glsl", "Shaders/Particle2DFragment.glsl");
	glUseProgram(gShaderProgram);
	checkGLError();
	gViewMat = glGetUniformLocation(gShaderProgram, "viewMat");
	gProjMat = glGetUniformLocation(gShaderProgram, "projMat");
	gArea = glGetUniformLocation(gShaderProgram, "area");
	checkGLError();

	GLint loc[4] = { 
		glGetUniformLocation(gShaderProgram, "textures0"),
		glGetUniformLocation(gShaderProgram, "textures1"),
		glGetUniformLocation(gShaderProgram, "textures2"),
		glGetUniformLocation(gShaderProgram, "textures3") };
	for (int i = 0; i < 4; i++)
	{
		if (loc[i] != -1) 
			glUniform1i(loc[i], i); //Assigns sampling slots
	}


	const glm::vec4 areas[8] = {
		glm::vec4(0,0,1,1), 
		glm::vec4(0,0,0.5f,0.5f), glm::vec4(0.5f,0.f,0.5f,0.5f), glm::vec4(0,0.5f,0.5f,0.5f), glm::vec4(0.5f,0.5f,0.5f,0.5f), 
		glm::vec4(0,0,1,1), glm::vec4(0,0,1,1), glm::vec4(0,0,1,1) };
	glUniform4fv(gArea, 8, (GLfloat*)areas);
	checkGLError();

	if (!loadTexture(DEFAULT_TEX, defaultTex))
	{
		std::cout << "No default tex could be loaded: " << DEFAULT_TEX << "\n";
		throw std::exception();
	}
	checkGLError();
}



