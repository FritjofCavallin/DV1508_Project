#include "GLFuncs.h"
#include <exception>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

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
	glAttachShader(gShaderProgram, vs);
	glLinkProgram(gShaderProgram);
	//checkCompileStatus(gShaderProgram);
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
	glAttachShader(gShaderProgram, vs);
	glAttachShader(gShaderProgram, gs);
	glAttachShader(gShaderProgram, fs);
	glLinkProgram(gShaderProgram);
	checkGLError();
	//checkCompileStatus(gShaderProgram);
	checkGLError();

	return gShaderProgram;
}

bool loadTexture(const char* texFile, GLuint &tex)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(texFile, &width, &height, &nrChannels, 4);
	GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else // Failed texture load
		return false;
	stbi_image_free(data);
	checkGLError();
	return true;
}