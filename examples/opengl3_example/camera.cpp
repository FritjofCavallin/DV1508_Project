#include "camera.h"
#include <windows.h>
#include <iostream>
Camera::Camera()
{
	projMat = glm::perspective(
		(glm::mediump_float)glm::radians(45.f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		(glm::mediump_float)	4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f             // Far clipping plane. Keep as little as possible.
	);

	cameraPos = glm::vec3(-9.6,   4.7 ,  10.3);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	

}

glm::mat4 Camera::getViewMat()
{
	
	float radius = 10.0f;
	float rotSpeed = 0.15f;
	
	SHORT A = GetAsyncKeyState('A');
	SHORT D = GetAsyncKeyState('D');
	SHORT W = GetAsyncKeyState('W');
	SHORT S = GetAsyncKeyState('S');
	SHORT Space = GetAsyncKeyState(VK_SPACE);
	SHORT LShift = GetAsyncKeyState(VK_LSHIFT);
	POINT NewMouseposition;
	GetCursorPos(&NewMouseposition);
//	std::cout << NewMouseposition.x << " " << NewMouseposition.y << std::endl;
	if(NewMouseposition.x <861 && NewMouseposition.y <674 && NewMouseposition.x >5 && NewMouseposition.y >40)
	{
		if (A)
		{
			 yaw += (rotSpeed * spinvalue); //-17.6
		}
		if (D)
		{
			yaw -= (rotSpeed *spinvalue);
		}
		if (W)
		{
			pitch += (rotSpeed * spinvalue);
		}
		if (S)
		{
			pitch -= (rotSpeed * spinvalue);
		}
		if (Space)
		{
			camY += -rotSpeed * radius*0.1;
		}
		if (LShift)
		{
			camY += rotSpeed * radius*0.1;
		}
	}
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cameraPos.x = 0 + cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraPos.y =  sin(glm::radians(pitch));
	cameraPos.z = 0 + cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	cameraPos += glm::normalize(cameraPos) * camY;

	return  glm::lookAt(cameraPos, glm::vec3(0, 0, 0), cameraUp);;
}

glm::mat4 Camera::getProjMat()
{
	return projMat;
}

glm::mat4 Camera::getVPMat()
{
	return projMat * getViewMat();
}