#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"
#include "GL/gl3w.h"

/* Block setting a specific texture slot for the particles (emitter block)
*/
class TextureBlock :
	public Block
{
public:

	unsigned int _texSlot;
	GLuint gTextureID;

	TextureBlock(TimeInterval t, const char* texFile, unsigned int texSlot);
	virtual ~TextureBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart) {}
};

