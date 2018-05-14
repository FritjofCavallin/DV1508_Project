#pragma once

#include "UIContainer.h"
#include "camera.h"

class Previewer : public UIContainer
{
public:
	GLuint frameBuffer;
	GLuint gVertexBuffer, gVertexAttribute;
	GLuint gShaderProgram;


	ImVec4 clear_color;
	GLuint worldMatrixID;
	size_t gridVertCount;

	Camera camera;
	GLuint texture, texturen, depthTex;
	Previewer(Data* data);
	virtual ~Previewer();
	virtual void draw(ImVec2 pos, ImVec2 size);
	void creationoftexture();
	void CreateShaders();
	void CreateTriangleData();
};

