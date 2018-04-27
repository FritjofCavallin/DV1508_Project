#pragma once
#define GLM
#ifdef GLM

#include "glm/vec4.hpp"
#include "glm/geometric.hpp"

/* Data sent to the GPU
*/
struct GPUParticle
{
	glm::vec3 _position;
	glm::vec4 _color;
	glm::vec2 _size;
	float _rotation;
};

/* Container for particle info
*/
class Particle
{
	float _time;
	glm::vec2 _initSize;
	
	//texture []
	float texBlend[];
};

#endif