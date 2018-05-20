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
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float camX = 0;
	float camZ = 10;
	float camY = 1;
	
	float pitch = 0;
	float yaw = 0;
public:
	Camera();
	~Camera(){}

	glm::mat4 projMat;

	glm::mat4 getViewMat();
	glm::mat4 getProjMat();
	glm::mat4 getVPMat();
};