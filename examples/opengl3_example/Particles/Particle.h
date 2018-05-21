#pragma once

#include "glm/vec4.hpp"
#include "glm/geometric.hpp"
#include "GL/gl3w.h"
#include "../Other/Constants.h"

class Timeline; struct InitialEmissionParams;

/* Data sent to the GPU
*/
struct GPUParticle
{
	glm::vec3 _position;
	glm::vec4 _color;
	glm::vec2 _size;
	float _rotation;
	glm::vec4 _texBlend;
	/* Indices to area arrays:
	*/
	unsigned char _texArea[4];

	GPUParticle();
};

/* Container for particle info
*/
class Particle
{
public:
	float _spawnTime;
	glm::vec2 _initSize;
	glm::vec3 _initDir;
	glm::vec3 _velocity;

	Particle();
	~Particle() {}
	
	//float texBlend[];

	bool dead(float particleTime, Timeline *particle);
	bool update(GPUParticle &data, float particleTime, Timeline *particle);
	void init(InitialEmissionParams &param, float spawnTime);
};