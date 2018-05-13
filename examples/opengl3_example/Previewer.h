#pragma once

#include "UIContainer.h"
#include "camera.h"

class Previewer : public UIContainer
{
public:
	GLuint frameBuffer;
	GLuint gVertexBuffer;
	GLuint gVertexAttribute;
	GLuint gShaderProgram;
	ImVec4 clear_color;
	GLuint worldMatrixID;
	glm::mat4 Identitymatrix;
	glm::mat4 scaling;
	glm::mat4 rotate;
	glm::mat4 translate;
	glm::mat4 Projectionmatrix;
	Camera camera;
	glm::mat4 worldmatrix;
	unsigned int texture;
	unsigned int texturen;
	Previewer(Data* data);
	virtual ~Previewer();
	virtual void draw(ImVec2 pos, ImVec2 size);
	void creationoftexture();
	void CreateShaders();
	void CreateTriangleData();
};

