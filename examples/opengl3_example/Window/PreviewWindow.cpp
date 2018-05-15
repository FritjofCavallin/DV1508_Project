#include "PreviewWindow.h"
#include "../Other/GLFuncs.h"
#include "../Particles/ParticleManager.h"



PreviewWindow::PreviewWindow(Data* data)
	: _data(data), camera()
{
	CreateShaders();
	CreateTriangleData();
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	
	//Gen. and bind color tex
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, display_w, display_h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);


	//Gen. and bind depth tex
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	//Bind it to frame buffer.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, display_w, display_h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Clamp to edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTex, 0);


	clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	mvpMatrixID = glGetUniformLocation(gShaderProgram, "MVP");
}


ImTextureID PreviewWindow::getWindowTex() { return reinterpret_cast<ImTextureID> (texture); }

PreviewWindow::~PreviewWindow()
{
	glDeleteTextures(1, &depthTex);
	glDeleteTextures(1, &texture);
	glDeleteFramebuffers(1, &frameBuffer);
}


void PreviewWindow::render()
{
	checkGLError();

	//Draw 3D
	glm::mat4 VP = camera.getVPMat();
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(gShaderProgram);
	glUniformMatrix4fv(mvpMatrixID, 1, GL_FALSE, &VP[0][0]);
	glBindVertexArray(gVertexAttribute);
	glLineWidth(1);
	glDrawArrays(GL_LINES, 0, gridVertCount);
	
	glEnablei(GL_BLEND, 0);
	glBlendFunci(0, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_data->getPlayer()->render(&camera);
	glDisablei(GL_BLEND, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkGLError();
}


void PreviewWindow::CreateShaders()
{
	gShaderProgram = loadShader("Shaders/VertexShader.glsl", "Shaders/Fragment.glsl");
}
void PreviewWindow::CreateTriangleData()
{
	// this is how we will structure the input data for the vertex shader
	// every six floats, is one vertex.
	struct TriangleVertex
	{
		float x, y, z;
		float r, g, b;
	};
	// create the actual data in plane Z = 0

	std::vector<TriangleVertex> gridVerts;

	float square = 5.f;

	for (float i = -square; i <= square; i++)
	{
		gridVerts.push_back({ i,0,square + 1,0,0,0 });
		gridVerts.push_back({ i,0,-square - 1,0,0,0 });
		gridVerts.push_back({ square + 1,0,i,0,0,0 });
		gridVerts.push_back({ -square - 1,0,i,0,0,0 });
	}
	gridVertCount = gridVerts.size();

	// Vertex Array Object (VAO) 
	glGenVertexArrays(1, &gVertexAttribute);
	// bind == enable
	glBindVertexArray(gVertexAttribute);
	// this activates the first and second attributes of this VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//96
	// create a vertex buffer object (VBO) id
	glGenBuffers(1, &gVertexBuffer);
	// Bind the buffer ID as an ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	// This "could" imply copying to the GPU, depending on what the driver wants to do...
	glBufferData(GL_ARRAY_BUFFER, gridVerts.size() * 4 * 6, gridVerts.data(), GL_STATIC_DRAW);

	// query where which slot corresponds to the input vertex_position in the Vertex Shader 
	GLuint vertexPos = glGetAttribLocation(gShaderProgram, "vertex_position");
	// specify that: the vertex attribute "vertexPos", of 3 elements of type FLOAT, not normalized, with STRIDE != 0,
	//               starts at offset 0 of the gVertexBuffer (it is implicitly bound!)
	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), BUFFER_OFFSET(0));

	// query where which slot corresponds to the input vertex_color in the Vertex Shader 
	GLuint vertexColor = glGetAttribLocation(gShaderProgram, "vertex_color");
	// specify that: the vertex attribute "vertex_color", of 3 elements of type FLOAT, not normalized, with STRIDE != 0,
	//               starts at offset (12 bytes) of the gVertexBuffer 
	glVertexAttribPointer(vertexColor, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), BUFFER_OFFSET(sizeof(float) * 3));
	checkGLError();
}
