#include "Previewer.h"

#include <string>
#include "stb_image.h"
#include "Other/GLFuncs.h"
#include "Particles/ParticleManager.h"

#define STB_IMAGE_IMPLEMENTATION

Previewer::Previewer(Data * data)
{
	this->data = data;
	creationoftexture();
	CreateShaders();
	CreateTriangleData();
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	const unsigned int width = 1920, height = 1080;
		
	//Gen. and bind color tex
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);


	//Gen. and bind depth tex
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	//Bind it to frame buffer.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//Clamp to edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTex, 0);


	clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	mvpMatrixID = glGetUniformLocation(gShaderProgram, "MVP");
	

}

Previewer::~Previewer()
{
	glDeleteTextures(1, &depthTex);
	glDeleteTextures(1, &texture);
	glDeleteFramebuffers(1, &frameBuffer);
}
void Previewer::creationoftexture()
{
	glGenTextures(1, &texturen);
	glBindTexture(GL_TEXTURE_2D, texturen);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("Imagetoreadfire.jpg", &width, &height, &nrChannels, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{

	}
	stbi_image_free(data);
	checkGLError();

}
void Previewer::CreateShaders()
{
	gShaderProgram = loadShader("Shaders/VertexShader.glsl", "Shaders/Fragment.glsl");
}
void Previewer::CreateTriangleData()
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
		gridVerts.push_back({ i,0,square+1,0,0,0 });
		gridVerts.push_back({ i,0,-square-1,0,0,0 });
		gridVerts.push_back({ square+1,0,i,0,0,0 });
		gridVerts.push_back({ -square-1,0,i,0,0,0 });
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



void Previewer::draw(ImVec2 pos, ImVec2 size)
{

	//Draw 3D
	glm::mat4 VP = camera.getVPMat();
	
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(gShaderProgram);
	glUniformMatrix4fv(mvpMatrixID, 1, GL_FALSE, &VP[0][0]);
	glBindVertexArray(gVertexAttribute);
	glLineWidth(1);
	glDrawArrays(GL_LINES, 0, gridVertCount);

	data->getPlayer()->update();

	glEnablei(GL_BLEND, 0);
	glBlendFunci(0, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	data->getPlayer()->render(&camera);
	glDisablei(GL_BLEND, 0);

	checkGLError();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Draw 2D
	ImGui::Begin("Previewer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	glBindTexture(GL_TEXTURE_2D, texture);
	ImGui::Image(reinterpret_cast<ImTextureID>(texture), ImGui::GetContentRegionAvail(), ImVec2(0, 0), ImVec2(1, -1));

	ImGui::End();
	checkGLError();
}
