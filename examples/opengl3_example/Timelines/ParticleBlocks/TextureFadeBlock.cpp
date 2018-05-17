#include "TextureFadeBlock.h"
#include "../../Other/GLFuncs.h"



TextureFadeBlock::TextureFadeBlock(TimeInterval t, unsigned int texSlot)
	: Block(t, type::Particle), _texSlot(texSlot)
{
	visualName = "Fade\n Factor";
	desc = "Fade factor value for a texture";
}

TextureFadeBlock::~TextureFadeBlock()
{
}

void TextureFadeBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._texBlend[_texSlot] = 1.f;
}

void TextureFadeBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	DrawPropertiesHeader(pos, size);

}