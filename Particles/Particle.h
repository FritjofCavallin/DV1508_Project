#pragma once

#include "glm/vec4.hpp"
#include "glm/geometric.hpp"


struct Particle
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 size;
	float rotation;
	
	//texture []
	float texBlend[];
};