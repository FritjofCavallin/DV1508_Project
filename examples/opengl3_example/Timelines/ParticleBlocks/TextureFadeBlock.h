#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"
#include "GL/gl3w.h"

/* Fade factor value for a texture
*/
class TextureFadeBlock :
	public Block
{
public:

	unsigned int _texSlot;

	TextureFadeBlock(TimeInterval t, unsigned int texSlot);
	virtual ~TextureFadeBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);

	virtual void DrawProperties(ImVec2 pos, ImVec2 size);
};

