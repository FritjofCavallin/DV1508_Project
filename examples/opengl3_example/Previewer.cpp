#include "Previewer.h"

#include <string>
#include <fstream>
#include "stb_image.h"
#include <iostream>
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))
#define STB_IMAGE_IMPLEMENTATION

void checkError()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "GL Error Occured: " << err << "\n";
}

Previewer::Previewer(Data * data)
{
	this->data = data;
	creationoftexture();
		CreateShaders();
		CreateTriangleData();
		glGenFramebuffers(1, &frameBuffer);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		scaling = glm::scale(glm::vec3(1,1,1));

		translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.2,0,0));
			
		rotate = glm::rotate((glm::mediump_float)0,glm::vec3(1,0,0));

		worldmatrix =  translate * rotate * scaling;
		worldMatrixID = glGetUniformLocation(gShaderProgram, "MVP");
}

Previewer::~Previewer()
{

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
	checkError();

}
void Previewer::CreateShaders()
{
	//create vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	// open glsl file and put it in a string
	std::ifstream shaderFile("VertexShader.glsl");
	if (!shaderFile.is_open())
		throw std::exception("File not found...");
	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();
	// make a double pointer (only valid here)
	const char* shaderTextPtr = shaderText.c_str();
	// ask GL to load this
	glShaderSource(vs, 1, &shaderTextPtr, nullptr);
	// ask GL to compile it
	glCompileShader(vs);

	//create fragment shader | same process.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	shaderFile.open("Fragment.glsl");
	shaderText.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();
	shaderTextPtr = shaderText.c_str();
	glShaderSource(fs, 1, &shaderTextPtr, nullptr);
	glCompileShader(fs);

	//link shader program (connect vs and ps)
	gShaderProgram = glCreateProgram();
	glAttachShader(gShaderProgram, fs);
	glAttachShader(gShaderProgram, vs);
	glLinkProgram(gShaderProgram);
	checkError();

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
	TriangleVertex triangleVertices[4] =
	{

		//Triangle strip
		{ -0.50f, 1.0f,  0,	0.0f, 0.0f, 1.0f },
		{ -0.50f, -1.0f, 0,	1.0f, 1.0f, 0.0f },
		{ 0.50f, 1.0f,  0,	0.0f, 0.0f, 1.0f },
		{ 0.50f, -1.0f, 0,	1.0f, 1.0f, 0.0f }
		// pos and color for each vertex
	/*{ -1.0f, 1.0f,  0,	0.0f, 0.0f, 1.0f },
	{ 1.0f, -1.0f, 0,	1.0f, 1.0f, 0.0f },
	{ -1.0f, -1.0f, 0,   0.0f, 1.0f, 0.0f },
	{ -1.0f, 1.0f,  0,	0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f,  0,	1.0f, 0.0f, 0.0f },
	{ 1.0f, -1.0f, 0,	1.0f, 1.0f, 0.0f }*/
	};

//	std::vector<TriangleVertex> triangleVertices;
//	TriangleVertex pushbackdata;
//	for (float i = -0.5; i < 1.6; i++)
//	{
//	pushbackdata = { i,1,0,0,0,1 };	
//	triangleVertices.push_back(pushbackdata);
//	pushbackdata = { i,-1,0,0,0,1 };
//	triangleVertices.push_back(pushbackdata);
//	}

	// Vertex Array Object (VAO) 
	glGenVertexArrays(1, &gVertexAttribute);
	// bind == enable
	glBindVertexArray(gVertexAttribute);
	// this activates the first and second attributes of this VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// create a vertex buffer object (VBO) id
	glGenBuffers(1, &gVertexBuffer);
	// Bind the buffer ID as an ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	// This "could" imply copying to the GPU, depending on what the driver wants to do...
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

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
	checkError();
}



void Previewer::draw(ImVec2 pos, ImVec2 size)
{

	

	glUniformMatrix4fv(worldMatrixID, 1, GL_FALSE, &worldmatrix[0][0]);
	// Common stuff
	ImGui::Begin("Previewer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(gShaderProgram);
	glBindVertexArray(gVertexAttribute);
	glBindTexture(GL_TEXTURE_2D, texturen);
	glLineWidth(10);
	glDrawArrays(GL_LINES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, texture);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	ImGui::Image(reinterpret_cast<ImTextureID>(texture), ImGui::GetContentRegionAvail(), ImVec2(0, 0), ImVec2(1, -1));
	glBindFramebuffer(GL_FRAMEBUFFER, 0);




	ImGui::End();
}
