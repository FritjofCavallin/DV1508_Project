#pragma once
#include <GL\/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm\matrix.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))
#define STB_IMAGE_IMPLEMENTATION

class Camera
{
private:
	glm::vec3 camera;
public:

};