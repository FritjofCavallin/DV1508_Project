#include "GLFuncs.h"
#include <exception>
#include <fstream>
#include <iostream>

void checkGLError()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "GL Error Occured: " << err << "\n";
}
void checkGLError(const char * msg)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "GL Error Occured: " << err << "\nMsg: " << msg << "\n";
}

GLuint loadShaderFile(const char* vertexShader, GLuint type)
{
	GLuint vs = glCreateShader(type);
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
	glShaderSource(vs, 1, &shaderTextPtr, nullptr);
	// ask GL to compile it
	glCompileShader(vs);
	std::string err = "Shader failed compilation: ";
	err += vertexShader;
	checkGLError(err.c_str());
	return vs;
}

GLuint loadShader(const char* vertexShader, const char* fragmentShader)
{
	//create vertex shader

	GLuint vs = loadShaderFile(vertexShader, GL_VERTEX_SHADER);
	GLuint fs = loadShaderFile(fragmentShader, GL_FRAGMENT_SHADER);
	
	//link shader program (connect vs and ps)
	GLuint gShaderProgram = glCreateProgram();
	glAttachShader(gShaderProgram, fs);
	glAttachShader(gShaderProgram, vs);
	glLinkProgram(gShaderProgram);
	checkGLError();

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
	glAttachShader(gShaderProgram, fs);
	glAttachShader(gShaderProgram, gs);
	glAttachShader(gShaderProgram, vs);
	glLinkProgram(gShaderProgram);
	checkGLError();

	return gShaderProgram;
}