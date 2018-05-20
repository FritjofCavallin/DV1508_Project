#include "camera.h"
#include <windows.h>

Camera::Camera()
{
	projMat = glm::perspective(
		(glm::mediump_float)glm::radians(45.f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		(glm::mediump_float)	4.0f / 3.0f,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f             // Far clipping plane. Keep as little as possible.
	);
<<<<<<< HEAD
	cameraPos = glm::vec3(-9.6,   4.7 ,  10.3);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
=======
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
>>>>>>> master
}

glm::mat4 Camera::getViewMat()
{
	
	float radius = 10.0f;
	float rotSpeed = 0.15f;
	
	SHORT A = GetAsyncKeyState('A');
	SHORT D = GetAsyncKeyState('D');
	SHORT W = GetAsyncKeyState('W');
	SHORT S = GetAsyncKeyState('S');
	SHORT O = GetAsyncKeyState('O');
	SHORT L = GetAsyncKeyState('L');
	SHORT P = GetAsyncKeyState('P');
	SHORT I = GetAsyncKeyState('I');
<<<<<<< HEAD
//	float length = glm::vec3(cameraPos - glm::vec3(0, 0, -2)).length();
	float length = cameraPos.length();
	
=======

>>>>>>> master
	SHORT Space = GetAsyncKeyState(VK_SPACE);
	SHORT LShift = GetAsyncKeyState(VK_LSHIFT);
	if (A)
	{
<<<<<<< HEAD
		
	//	 camX +=(-rotSpeed * radius);
	//	 cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * -rotSpeed;
		 yaw += (rotSpeed * spinvalue); //-17.6
	}
	if (D)
	{
		
	//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * rotSpeed;
		yaw -= (rotSpeed *spinvalue);
	//	camX += rotSpeed * 4;
	}
	if (W)
	{
	//	spinvalue += rotSpeed;
	//	cameraPos += rotSpeed * cameraFront;
	//	camZ += rotSpeed * radius;
		pitch += (rotSpeed * spinvalue);
	}
	if (S)
	{
	//
		pitch -= (rotSpeed * spinvalue);
		//spinvalue -= rotSpeed;
		//cameraPos += -rotSpeed * cameraFront;
	//	camZ += -rotSpeed * radius;
	}
	if (Space)
	{
	//	cameraPos += rotSpeed * cameraFront.y;
		camY += -rotSpeed * radius*0.1;
	}
	if (LShift)
	{
	//	cameraPos += -rotSpeed * cameraFront.y;
		
		camY += rotSpeed * radius*0.1;
=======
		 camX +=-rotSpeed * radius;
		 cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * -rotSpeed;
	}
	if (D)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * rotSpeed;
		camX += rotSpeed * radius;
	}
	if (W)
	{
		cameraPos += rotSpeed * cameraFront;
		camZ += rotSpeed * radius;
	}
	if (S)
	{
		cameraPos += -rotSpeed * cameraFront;
		camZ += -rotSpeed * radius;
	}
	if (Space)
	{
		camY += rotSpeed * radius;
	}
	if (LShift)
	{
		camY += -rotSpeed * radius;
>>>>>>> master
	}
	
	if (O)
	{
<<<<<<< HEAD
		pitch += 0.1; //-17.6
=======
		pitch += 0.1;
>>>>>>> master
	}
	if (L)
	{
		pitch -= 0.1;
	}
	if (I)
	{
<<<<<<< HEAD
		yaw += 0.1; //-48
=======
		yaw += 0.1;
>>>>>>> master
	}
	if (P)
	{
		yaw -= 0.1;
	}



	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

<<<<<<< HEAD

	//testing some new stuff
	


	cameraPos.x = 0 + cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraPos.y =  sin(glm::radians(pitch));
	cameraPos.z = 0 + cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	cameraPos += glm::normalize(cameraPos) * camY;

	
	glm::mat4 view;
//	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	view = glm::lookAt(cameraPos, glm::vec3(0,0,0), cameraUp);
=======
	
	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
>>>>>>> master
	//	view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
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