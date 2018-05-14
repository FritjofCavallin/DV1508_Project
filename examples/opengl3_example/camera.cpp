#include "camera.h"


Camera::Camera()
{
	projMat = glm::perspective(
		(glm::mediump_float)glm::radians(45.f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		(glm::mediump_float)	4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f             // Far clipping plane. Keep as little as possible.
	);
}

glm::mat4 Camera::getViewMat()
{
	float radius = 10.0f;
	float rotSpeed = 0.15f;
	float camX = sin(glfwGetTime() * rotSpeed) * radius;
	float camZ = cos(glfwGetTime() * rotSpeed) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 1.f, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	return view;
}

glm::mat4 Camera::getProjMat()
{
	return projMat;
}

glm::mat4 Camera::getVPMat()
{
	return projMat * getViewMat();
}