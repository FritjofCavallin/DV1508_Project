#include "Particle2DShader.h"
#include <exception>
#include "../Other/Constants.h"
#include <iostream>
const GLuint SHADE_DEF = 1000000;

Particle2DShader::Particle2DShader()
{
	gShaderProgram = SHADE_DEF;
	bgColor = glm::vec4(0.40f, 0.5f, 0.55f, 1.00f);
	borderColor = glm::vec4(0, 0, 0, 1.f);
}



Particle2DShader::~Particle2DShader()
{
	glDeleteTextures(1, &defaultTex);
	glDeleteShader(gShaderProgram);
}

void Particle2DShader::render(GPUParticle &part, GLint x, GLint y, GLuint w, GLuint h)
{
	glViewport(x, y, w, h);
	
	// Render border
	glUseProgram(gShaderClear);
	glBindVertexArray(quadVAO);
	glUniform4f(gClearColor, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// Render background
	glViewport(x+3, y, w-3, h-3);
	glUniform4f(gClearColor, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Render 2D part
	glUseProgram(gShaderProgram);


	glUniform2f(gSize, part._size.x, part._size.y);
	glUniform1f(gRot, part._rotation);
	glUniform4f(gColor, part._color.r, part._color.g, part._color.b, part._color.a);
	glUniform4f(gTex_Blend, part._texBlend.r, part._texBlend.g, part._texBlend.b, part._texBlend.a);
	glUniform4ui(gTex_Area, part._texArea[0], part._texArea[1], part._texArea[2], part._texArea[3]);


	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	checkGLError();
}

void Particle2DShader::load()
{
	checkGLError();
	if (gShaderProgram != SHADE_DEF)
		glDeleteShader(gShaderProgram);
	gShaderProgram = loadShader("Shaders/Particle2DVertex.glsl", "Shaders/Particle2DFragment.glsl");
	gShaderClear = loadShader("Shaders/Vertex.glsl", "Shaders/ColorFragment.glsl");

	glUseProgram(gShaderClear);
	gClearColor = glGetUniformLocation(gShaderClear, "Color");

	glUseProgram(gShaderProgram);
	checkGLError();
	gRot = glGetUniformLocation(gShaderProgram, "Rotation");
	gSize = glGetUniformLocation(gShaderProgram, "Size");
	gSizeMax = glGetUniformLocation(gShaderProgram, "SizeMax");
	gColor = glGetUniformLocation(gShaderProgram, "Color");
	gTex_Blend = glGetUniformLocation(gShaderProgram, "Tex_Blend");
	gTex_Area = glGetUniformLocation(gShaderProgram, "Tex_Area"); 
	gArea = glGetUniformLocation(gShaderProgram, "Area");
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
	glUniform2f(gSizeMax, 2, 2);
	checkGLError();

	if (!loadTexture(DEFAULT_TEX, defaultTex))
	{
		std::cout << "No default tex could be loaded: " << DEFAULT_TEX << "\n";
		throw std::exception();
	}
	checkGLError();

	genBuffer();
}

void Particle2DShader::genBuffer()
{
	// Vertex Array Object (VAO) 
	
	glGenVertexArrays(1, &quadVAO);
	// bind == enable
	glBindVertexArray(quadVAO);
	// this activates the first and second attributes of this VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//96
	// create a vertex buffer object (VBO) id
	glGenBuffers(1, &quadVBO);
	// Bind the buffer ID as an ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	struct Vert { glm::vec3 P; glm::vec2 UV; };
	Vert quadData[6] = 
	{
		{glm::vec3(-1, -1, 0), glm::vec2(0,0)},
		{ glm::vec3(1, -1, 0), glm::vec2(1,0) },
		{ glm::vec3(-1, 1, 0), glm::vec2(0, 1) },
		{ glm::vec3(1, -1, 0), glm::vec2(1, 0) },
		{ glm::vec3(-1, 1, 0), glm::vec2(0, 1) },
		{ glm::vec3(1, 1, 0), glm::vec2(1,1) }
	};
	
	// This "could" imply copying to the GPU, depending on what the driver wants to do...
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vert), quadData, GL_STATIC_DRAW);

	GLuint vertexPos = glGetAttribLocation(gShaderProgram, "Position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(0));

	GLuint vertexUV = glGetAttribLocation(gShaderProgram, "UV");
	glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(12));


	vertexPos = glGetAttribLocation(gShaderClear, "Position");
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), BUFFER_OFFSET(0));


	checkGLError();
}


