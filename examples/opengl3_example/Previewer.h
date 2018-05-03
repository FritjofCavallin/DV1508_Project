#pragma once

#include "UIContainer.h"
#include <GL\/gl3w.h>
#include <GLFW/glfw3.h>
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))
#define STB_IMAGE_IMPLEMENTATION
class Previewer : public UIContainer
{
public:
	GLuint frameBuffer;
	GLuint gVertexBuffer;
	GLuint gVertexAttribute;
	GLuint gShaderProgram;
	ImVec4 clear_color;
	unsigned int texture;
	unsigned int texturen;
	Previewer(Data* data);
	virtual ~Previewer();
	virtual void draw(ImVec2 pos, ImVec2 size);
	void creationoftexture();
	void CreateShaders();
	void CreateTriangleData();
};

