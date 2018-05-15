#pragma once

#include "../camera.h"
#include "imgui.h"
#include "../Timelines/Data.h"


class PreviewWindow
{
public:
	PreviewWindow(Data* data);
	~PreviewWindow();

	void render();

	ImTextureID getWindowTex();
	const unsigned int display_w = 1920, display_h = 1080;
private:

	void CreateShaders();
	void CreateTriangleData();

	Data* _data;


	GLuint frameBuffer;
	GLuint gVertexBuffer, gVertexAttribute;
	GLuint gShaderProgram;


	ImVec4 clear_color;
	GLint mvpMatrixID;
	size_t gridVertCount;

	Camera camera;
	GLuint texture, depthTex;
};

