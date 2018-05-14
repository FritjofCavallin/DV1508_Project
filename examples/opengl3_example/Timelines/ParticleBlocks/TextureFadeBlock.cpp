#include "TextureFadeBlock.h"
#include "../../Other/GLFuncs.h"



TextureFadeBlock::TextureFadeBlock(TimeInterval t, unsigned int texSlot)
	: Block(t, type::Particle), _texSlot(texSlot)
{
}

TextureFadeBlock::~TextureFadeBlock()
{
}

void TextureFadeBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._texBlend[_texSlot] = 1.f;
}