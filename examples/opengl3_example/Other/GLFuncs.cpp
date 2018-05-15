#include "GLFuncs.h"
#include "../Other/Constants.h"
#include <exception>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

void checkGLError()
{
#ifdef _DEBUG
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "GL Error Occured: " << err << "\n";
#endif
}
void checkGLError(const char * msg)
{
#ifdef _DEBUG
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "GL Error Occured: " << err << "\nMsg: " << msg << "\n";
#endif
}

void checkCompileError(GLuint program, const char* msg)
{
	checkGLError();
	static GLchar text[400];
	GLsizei len = 0;
	glGetProgramInfoLog(program, 200, &len, text);
	if(len > 0)
		std::cout << msg << "\n" << text << "\n";
}

void checkCompileStatus(GLuint shaderProg)
{

	GLint val = GL_FALSE;
	glGetShaderiv(shaderProg, GL_COMPILE_STATUS, &val);
	if (val != GL_TRUE)
	{
		// compilation failed
		std::cout << "GL Compilation failed: " << val << "\n";
	}
}

GLuint loadShaderFile(const char* vertexShader, GLenum  type)
{
	GLuint shader = glCreateShader(type);
	// open glsl file and put it in a string
	std::ifstream shaderFile(vertexShader);
	if (!shaderFile.is_open())
	{
		std::string err = "Shader file not found: ";
		err += vertexShader;
		std::cout << err.c_str() << std::endl;
		throw std::exception("Shader file not found...");
	}
	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();
	// make a double pointer (only valid here)
	const char* shaderTextPtr = shaderText.c_str();
	// ask GL to load this
	glShaderSource(shader, 1, &shaderTextPtr, nullptr);
	// ask GL to compile it
	glCompileShader(shader);
	std::string err = "Shader failed compilation: ";
	err += vertexShader;
	checkGLError(err.c_str());
	return shader;
}

GLuint loadShader(const char* vertexShader, const char* fragmentShader)
{
	//create vertex shader

	GLuint vs = loadShaderFile(vertexShader, GL_VERTEX_SHADER);
	GLuint fs = loadShaderFile(fragmentShader, GL_FRAGMENT_SHADER);
	
	//link shader program (connect vs and ps)
	GLuint gShaderProgram = glCreateProgram();
	glAttachShader(gShaderProgram, fs);
	checkCompileError(gShaderProgram, "Fragment error.");
	glAttachShader(gShaderProgram, vs);
	checkCompileError(gShaderProgram, "Vertex shader error.");
	glLinkProgram(gShaderProgram);
	checkCompileError(gShaderProgram, "Shader link error.");
	//checkCompileStatus(gShaderProgram);

	return gShaderProgram;
}

GLuint loadShader(const char* vertexShader, const char* geomShader, const char* fragmentShader)
{
	//create vertex shader

	GLuint vs = loadShaderFile(vertexShader, GL_VERTEX_SHADER);
	GLuint gs = loadShaderFile(geomShader, GL_GEOMETRY_SHADER);
	GLuint fs = loadShaderFile(fragmentShader, GL_FRAGMENT_SHADER);

	//link shader program (connect vs and ps)
	GLuint gShaderProgram = glCreateProgram();
	glAttachShader(gShaderProgram, vs);
	checkCompileError(gShaderProgram, "Vertex shader error.");
	glAttachShader(gShaderProgram, gs);
	checkCompileError(gShaderProgram, "Geometry shader error.");
	glAttachShader(gShaderProgram, fs);
	checkCompileError(gShaderProgram, "Fragment error.");
	glLinkProgram(gShaderProgram);
	checkCompileError(gShaderProgram, "Shader link error.");

	return gShaderProgram;
}

bool loadTexture(const char* texFile, GLuint &tex)
{
	std::string filePath(TEX_PATH);
	filePath += texFile;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_uc *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4);
	GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
	switch (nrChannels)
	{
	case 3:
		format = GL_RGB;
	case 4:
	default:
		format = GL_RGBA;
	}
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else // Failed texture load
		return false;
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	checkGLError();
	return true;
}