#include "ParticleShader.h"
#include <exception>
#include "../Other/Constants.h"
#include <iostream>
const GLuint SHADE_DEF = 1000000;

ParticleShader::ParticleShader()
{
	gShaderProgram = SHADE_DEF;
}



ParticleShader::~ParticleShader()
{
	glDeleteTextures(1, &defaultTex);
	glDeleteShader(gShaderProgram);
}

void ParticleShader::assignGlobalUniforms(Camera *cam)
{
	glUseProgram(gShaderProgram);
	glm::mat4 view = cam->getViewMat();
	glUniformMatrix4fv(gProjMat, 1, GL_FALSE, &cam->projMat[0][0]);
	glUniformMatrix4fv(gViewMat, 1, GL_FALSE, &view[0][0]);
	

	checkGLError();
}

void ParticleShader::load()
{
	checkGLError();
	if (gShaderProgram != SHADE_DEF)
		glDeleteShader(gShaderProgram);
	gShaderProgram = loadShader("Shaders/ParticleVertex.glsl", "Shaders/ParticleGeom.glsl", "Shaders/ParticleFragment.glsl");
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
		glm::vec4(0,0,1,1), glm::vec4(0,0,1,1),
		glm::vec4(0,0,1,1), glm::vec4(0,0,1,1),
		glm::vec4(0,0,1,1), glm::vec4(0,0,1,1),
		glm::vec4(0,0,1,1), glm::vec4(0,0,1,1) };
	glUniform4fv(gArea, 8, (GLfloat*)areas);
	checkGLError();

	if (!loadTexture(DEFAULT_TEX, defaultTex))
	{
		std::cout << "No default tex could be loaded: " << DEFAULT_TEX << "\n";
		throw std::exception();
	}
	checkGLError();
}


ParticleBuffer ParticleShader::genBuffer(size_t nVerts)
{
	// Vertex Array Object (VAO) 
	ParticleBuffer buff;
	glGenVertexArrays(1, &buff.gVAO);
	// bind == enable
	glBindVertexArray(buff.gVAO);
	// this activates the first and second attributes of this VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	//96
	// create a vertex buffer object (VBO) id
	glGenBuffers(1, &buff.gVertBuf);
	// Bind the buffer ID as an ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, buff.gVertBuf);
	
	glBufferData(GL_ARRAY_BUFFER, nVerts * sizeof(GPUParticle), NULL, GL_STATIC_DRAW);

	GLuint vertexPos = glGetAttribLocation(gShaderProgram, "Position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(GPUParticle), BUFFER_OFFSET(0));

	GLuint vertexColor = glGetAttribLocation(gShaderProgram, "Color");
	glVertexAttribPointer(vertexColor, 4, GL_FLOAT, GL_FALSE, sizeof(GPUParticle), BUFFER_OFFSET(12));

	GLuint vertexSize = glGetAttribLocation(gShaderProgram, "Size");
	glVertexAttribPointer(vertexSize, 2, GL_FLOAT, GL_FALSE, sizeof(GPUParticle), BUFFER_OFFSET(28));

	GLuint vertexRotation = glGetAttribLocation(gShaderProgram, "Rotation");
	glVertexAttribPointer(vertexRotation, 1, GL_FLOAT, GL_FALSE, sizeof(GPUParticle), BUFFER_OFFSET(36));

	GLuint vertexBlendTex = glGetAttribLocation(gShaderProgram, "TexBlend");
	glVertexAttribPointer(vertexBlendTex, 4, GL_FLOAT, GL_FALSE, sizeof(GPUParticle), BUFFER_OFFSET(40));

	GLuint vertexAreaTex = glGetAttribLocation(gShaderProgram, "TexArea");
	glVertexAttribPointer(vertexAreaTex, 4, GL_INT, GL_FALSE, sizeof(GPUParticle), BUFFER_OFFSET(56));

	checkGLError();
	return buff;
}



ParticleBuffer::ParticleBuffer()
	: _bufCount(0)
{

}
ParticleBuffer::~ParticleBuffer()
{
}

void ParticleBuffer::destroy()
{
	glDeleteVertexArrays(1, &gVAO);
	glDeleteBuffers(1, &gVertBuf);
	checkGLError();
}

void ParticleBuffer::buffer(size_t nVerts, const void *data, size_t offsetN)
{
	glBindBuffer(GL_ARRAY_BUFFER, gVertBuf);
	unsigned int size = sizeof(GPUParticle);
	glBufferSubData(GL_ARRAY_BUFFER, offsetN * sizeof(GPUParticle), nVerts * sizeof(GPUParticle), data);
	_bufCount = offsetN + nVerts;
}


void ParticleBuffer::draw()
{
	glBindVertexArray(gVAO);
	glDrawArrays(GL_POINTS, 0, _bufCount);
}
