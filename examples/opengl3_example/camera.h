#pragma once
#include <GL\/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm\matrix.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#define STB_IMAGE_IMPLEMENTATION

class Camera
{
private:
	glm::vec3 camera;

	glm::vec3 cameraPos; //-9.6   4.7   10.3
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float spinvalue = 4;
	float camX = 0;
	float camZ = 10;
	float camY = 10;
	glm::vec3 cameraPospos = glm::vec3(0,0,0);
	float pitch = -17.6;
	float yaw = -48;

public:
	Camera();
	~Camera(){}

	glm::mat4 projMat;

	glm::mat4 getViewMat();
	glm::mat4 getProjMat();
	glm::mat4 getVPMat();
};